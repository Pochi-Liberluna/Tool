#include<iostream>
#include<windows.h>
#include<gdiplus.h>
#include<cmath>
#include<tchar.h>
using namespace Gdiplus;

#pragma comment(lib,"Gdiplus.lib")

//ウィンドウ名、プロパティ、著作権情報を設定する関数を記述(<windows.h>をインクルード)

void SetWindowTitle(HWND hWnd, const wchar_t* newTitle){
    SetWindowText(hWnd, newTitle);
    //ウィンドウ名を設定する関数
}
void SetWindowProperty(HWND hWnd, const wchar_t* propertyKey, const wchar_t* propertyValue){
    SetProp(hWnd, propertyKey, (HANDLE)propertyValue);
    //プロパティを設定する関数
}
void SetWindowCopyright(HWND hWnd, consg wchar_t* copyrightInfo){
    SendMessage(hWnd, WM_SECTION, ICON_BIG, (LPARAM)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(1))); //仮アイコンの設定
        SetWindowProperty(hWnd, L"Copyright", copyrightInfo);
}

const int TIMER_ID = 1;
const int IMAGE_WIDTH = 100; //画像の幅(px)
const int IMAGE_HEIGHT = 100; //画像の高さ(px)
const float SPEED = 50.0f; //移動速度(px/s)

LRESULT CALLBACK ScreenSaverProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
    static Bitmap* pLogoBitmap = nullptr; //ロゴ画像のポインタ
    float posX = 0.0f; //画像のX座標

    switch (message) {
        case WM_CREATE:{
          
                // GDI+ 初期化
                GdiplusStartupInput gdiplusStartupInput;
                ULONG_PTR gdiplusToken;
                GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

                //ロゴ画像(パス未設定)
                pLogoBitmap = new Bitmap(L"path_to_logo.png");

                if(pLogoBitmap->GetLastStatus() != Ok){
                    MessageBox(hWnd, L"Failed to load logo image!", L"Error", MB_ICONERROR);
                    return -1; //エラーで終了
                }

                //スクリーンセーバー待機時間を設定
                SystemParametersInfo(SPI_SETSCREENSAVETIMEOUT, 5 * 60, NULL, 0);

                //タイマーを設定
                SetTimer(hWnd, TIMER_ID, 1000 / 30, NULL); //30fps

                //タイトル設定
                SetWindowTitle(hWnd, L"MyScreenSaver");
                //プロパティ設定
                SetWindowProperty(hWnd, L"Property", L"Custom Value");
                //著作権情報設定
                SetWindowCopyright(hWnd, L"©︎ ");
            
            }
            break;

        case WM_DESTROY:
            //タイマーを破棄
            KillTimer(hWnd, TIMER_ID);

            //GDI+ 終了
            GdiplusShutdown(pLogoBitmap);
            delete pLogoBitmap;
            PostQuitMessage(0);
            break;

        case WM_PAINT:{
          
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);

                //背景を黒に設定
                RECT rect;
                GetClientRect(hWnd, &rect);
                FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));

                //ロゴ画像を描画
                if(pLogoBitmap != nullptr){
                    Graphics graphics(hdc);
                    graphics.DrawImage(pLogoBitmap, posX, 0);
                }

                EndPaint(hWnd, &ps);
            }
            break;

        case WM_TIMER:
          
            //タイマーイベントが発生したら画像の位置を更新
            posX += SPEED / 30.0f; //移動速度をフレームレートで割って位置を更新
            if (posX > rect.right) {
                posX = 0; //画面外に出たら初期位置に戻す
            }
            InvalidateRect(hWnd, NULL, FALSE); //再描画をトリガー
            break;

        case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
          
            // マウスイベントがあった場合、最終操作時間を更新
            SystemParametersInfo(SPI_SETSCREENSAVETIMEOUT, 5 * 60, NULL, 0);
            break;

        default:
            return DefScreenSaverProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
  
    MSG msg;
    WNDCLASS wc;

    //スクリーンセーバーのウィンドウクラスを設定
    wc.style = CS_DBLCLKS;
    wc.lpfnWndProc = ScreenSaverProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"ScreenSaverClassName";

    if(!RegisterClass(&wc))
        return 0;

    //スクリーンセーバーのメインウィンドウを作成
    HWND hWnd = CreateWindow(
        L"ScreenSaverClassName", L"Screen Saver",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL
    );

    if(!hWnd)
        return 0;

    //スクリーンセーバーのメインループ
    while(GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

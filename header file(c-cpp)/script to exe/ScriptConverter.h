#include<windows.h>
#pragma comment(linker, "/nodefaultlib:\"libc.lib\"")
#pragma comment(linker, "/entry:\"PreWinMain\"")

int WinAPI Winmain(HINSTANCE hInst, HINSTANCE hPrevInst, LRSTR IpCmdLine, int intShowCmd);
int PreWinMain();

BOOL CALLBACK EnumWindowsProc(HWND hwnd, DWORD dwThreadId);
void Events();
void Memory(void* pointer, int size);
int Error(LPSTR message);

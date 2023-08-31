#include"ScriptConverter.h"

int WinAPI Winmain( HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int intShowCmd){
  HANDLE Handle1, Handle2;
  UINT fSize;
  int x, y;
  char c = 0;
  char *ANSI;
  char VBS[MAX_PATH], TMP[MAX_PATH], TMPFILE[MAX_PATH];
  char* VBSorJS;
  char szModulePath[MAX_PATH];
  char buff[1024]

  BOOL CONSOLE = FALSE;
    if(GetConsoleTitle(TMP, MAX_PATH)) CONSOLE = TRUE;
    GetModuleFileName(hInst,szModulePath,MAX_PATH);
  Handle1 = CreateFile(szModulePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    if(Handle1 == INVALID_HANDLE_VALUE) return Error("Can't open myself.");

  while(true){
    if(!ReadFile(Handle1, &c, 1, (DWORD*)&fSize, NULL)) break;
    if(fSize == 0) break;
    if(c == '\' || c == '/' || c == '<'){
      ReadFile(Handle1, ANSI, 21, (DWORD*)&fSize, NULL);
      if(lstrcmp(ANSI, "*****Begin VBS*****\x0D\x0A") == 0 && fSize == 21) VBSorJS = ".vbs";
      else if(lstrcmp(ANSI, "*****Begin VBE*****\x0D\x0A") == 0 && fSize == 21) VBSorJS = ".vbe";
			else if(lstrcmp(ANSI, "/*****Begin JS*****\x0D\x0A") == 0 && fSize == 21) VBSorJS = ".js";
			else if(lstrcmp(ANSI, "/*****Begin JSE****\x0D\x0A") == 0 && fSize == 21) VBSorJS = ".jse";
			else if(lstrcmp(ANSI, "!--**Begin WSF**-->\x0D\x0A") == 0 && fSize == 21) VBSorJS = ".wsf";
			else VBSorJS = 0;
    }
  }
}

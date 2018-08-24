#include <windows.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <fcntl.h>
#include <io.h>

#define _O_U8TEXT 0x00040000
#define _O_U16TEXT 0x00020000

using namespace std;

size_t GetFileSize(const std::wstring& path) {
  struct _stat fileinfo;
  _wstat(path.c_str(), &fileinfo);
  return fileinfo.st_size;
}

std::wstring LoadUtf8File(const std::wstring& fname) {
  wstring buffer;
  FILE* file = _wfopen(fname.c_str(), L"rtS, ccs=UTF-8");
  if (file != NULL) {
    size_t fsize = GetFileSize(fname);
    if (fsize > 0) {
      buffer.resize(fsize);
      size_t wchars_read = fread((void*)(buffer.c_str()), sizeof(wchar_t), fsize, file);
      buffer.resize(wchars_read);
    }
    fclose(file);
  }
  return buffer;
}

int WINAPI
WinMain (HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpCmdLine, int nShowCmd) {
  _setmode(_fileno(stdout), _O_U8TEXT);
  LPWSTR cli = GetCommandLineW();
  int argc;
  LPWSTR *argv = CommandLineToArgvW(cli, &argc);
  if (argc >= 2) {
    wstring wstr = LoadUtf8File(argv[1]);
    wcout << wstr;
  }
  return 0;
}
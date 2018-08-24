#include <stdio.h>
#include <iostream>
#include <string>
#include <windows.h>

#include <fcntl.h>
#include <io.h>

#define _O_U8TEXT 0x00040000
#define _O_U16TEXT 0x00020000

using namespace std;

void replaceAll(wstring &s, const wstring &search, const wstring &replace) {
  for(size_t pos = 0; ; pos += replace.length()) {
    pos = s.find(search, pos);
    if(pos == wstring::npos) break;
    s.erase(pos, search.length());
    s.insert(pos, replace);
  }
}

int main() {
  _setmode(_fileno(stdin), _O_U8TEXT);
  wchar_t buffer[16384];
  wstring wstr;
  int count = 0;
  while ((count = fread(buffer, 1, sizeof(buffer), stdin)) != 0) {
    wstr += buffer;
  }
  replaceAll(wstr, L"\n", L"\r\n");
  if (OpenClipboard(NULL)) {
    EmptyClipboard();
    size_t size = (wstr.size() + 1) * sizeof(wchar_t);
    HGLOBAL hClipboardData = GlobalAlloc(0, size);
    if (hClipboardData != NULL) {
      wchar_t* pchData = (wchar_t*) GlobalLock(hClipboardData);
      if (pchData != NULL) {
        memcpy(pchData, wstr.c_str(), size);
        GlobalUnlock(hClipboardData);
        SetClipboardData(CF_UNICODETEXT, hClipboardData);
      }
    }
    CloseClipboard();
  }
  return 0;
}
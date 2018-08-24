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
  _setmode(_fileno(stdout), _O_U8TEXT);
  if(OpenClipboard(NULL)) {
    HANDLE clip = GetClipboardData(CF_UNICODETEXT); 
    if(clip != NULL) {
      wchar_t *c = reinterpret_cast<wchar_t*>(GlobalLock(clip));
      wstring ws(c);
      replaceAll(ws, L"\r\n", L"\n");
      wcout << ws;
      GlobalUnlock(clip);
    }
    CloseClipboard();
  }
  return 0;
}
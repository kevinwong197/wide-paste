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
  wchar_t buffer[16384];
  wstring wstr;
  _setmode(_fileno(stdout), _O_U8TEXT);
  _setmode(_fileno(stdin), _O_U16TEXT);
  while (fgetws(buffer, sizeof(buffer), stdin) != NULL) {
    wstr += buffer;
  }
  replaceAll(wstr, L"\n\n", L"\n");
  wcout << wstr;
  return 0;
}
#include <stdio.h>
#include <iostream>
#include <string>
#include <windows.h>

#include <fcntl.h>
#include <io.h>

#define _O_U8TEXT 0x00040000
#define _O_U16TEXT 0x00020000

using namespace std;

int main() {
  wchar_t buffer[16384];
  _setmode(_fileno(stdin), _O_U8TEXT);
  _setmode(_fileno(stdout), _O_U8TEXT);
  while (fgetws(buffer, sizeof(buffer), stdin) != NULL) {
    wstring wstr(buffer);
    wcout << wstr;
  }
  return 0;
}
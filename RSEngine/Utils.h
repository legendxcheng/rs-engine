#pragma once

#include <tchar.h>
#include <windows.h>

void c2w(wchar_t *pwstr,size_t len,const char *str);
char *w2c(char *pcstr,const wchar_t *pwstr, size_t len);
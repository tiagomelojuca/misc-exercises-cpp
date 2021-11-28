#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "");

    wchar_t name[] = L"Tiago Melo Jucá";
    wprintf(L"Meu nome é %s", name);
    
    return 0;
}

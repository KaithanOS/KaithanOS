#include "stdio.h"
#include "x86.h"
void putc(char c) {
    x86_VideoWriteCharTeletype(c, 0);
}

void puts(const char* str) {
    while (*str) {
        putc(*str);
        str++;
    }
}

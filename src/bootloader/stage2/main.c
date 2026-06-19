#include "stdint.h"
#include "stdio.h"

void _cdecl cstart_(uint16_t bootDrive) {
  const char *greeting = "Hello World from C!";
  puts(greeting);
  for (;;)
    ;
}

#include "stdint.h"
#include "stdio.h"

void _cdecl cstart_(uint16_t bootDrive) {
  const char *greeting = "Hello World from C!\r\n";
  puts(greeting);
  printf("Formatted %% %c %s\r\n", 'a', "string");
  printf("Formatted %d %i %x %p %o %hd %hi %hhu\r\n", 1234, -5678, 0xdead,
         0xfade, 012345, (short)27, (short)-42, (unsigned char)20,
         (unsigned char)10);
  printf("Formatted %ld %lx %lld %llx\r\n", -100000000l, 0xdeadfadeul,
         10200300400ll, 0xdeadfadeaaaabbbbull);
  for (;;)
    ;
}

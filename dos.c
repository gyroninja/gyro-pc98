#include "dos.h"

uint8_t dos_read_keyboard_without_echo() {
  uint8_t result;
  asm volatile(
      "mov $0x08, %%ah\n"
      "int $0x21\n"
      : "=al"(result)
      : /* no input */
      : /* no clobber */);
  return result;
}

void dos_display_string(char* string) {
  asm volatile(
      "mov $0x09, %%ah\n"
      "int $0x21\n"
      : /* no output */
      : "d"(string)
      : "ah");
}

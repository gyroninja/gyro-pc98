#include "dos.h"
#include "gdc.h"

int main() {
  gdc_init_graphics();
  set_palette(0x08, 0x0f, 0x00, 0x00);
  gdc_rectangle(GDC_PLANE1_ADDRESS, 10, 10, 630, 390);
  gdc_set_blank(GDC_TEXT, false);
  gdc_set_blank(GDC_GRAPHICS, true);
  while (dos_read_keyboard_without_echo() != '\r')
    ;
  gdc_set_blank(GDC_TEXT, true);
  gdc_set_blank(GDC_GRAPHICS, false);

  return 0;
}

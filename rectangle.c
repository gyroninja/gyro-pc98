#include "dos.h"
#include "graphics.h"

/**
 * main() - Draws a rectangle to the screen.
 */
int main() {
  graphics_start();
  graphics_set_mode(GRAPHICS_MODE_VRAM_REGION_ALL |
                    GRAPHICS_MODE_CRT_DISPLAY_COLOR |
                    GRAPHICS_MODE_DISPLAY_BANK0);
  struct graphics_ucw ucw = {0};
  graphics_ucw_init_line_rectangle(
      &ucw, DRAW_MODE_PLANE1_SET, DRAW_OPERATION_SET,
      DRAW_DIRECTION_RECTANGLE_TOP_LEFT_BOTTOM_RIGHT, 10, 10, 629, 389, 0xffff,
      DRAW_TYPE_RECTANGLE);
  graphics_draw_line_rectangle(TARGET_SCREENS_HIGH_RESOLUTION |
                                   TARGET_SCREENS_LOWER_ALL |
                                   TARGET_SCREENS_PLANE123,
                               &ucw);
  dos_display_string("Press enter to quit\r\n$");
  while (dos_read_keyboard_without_echo() != '\r')
    ;
  graphics_finish();
  return 0;
}

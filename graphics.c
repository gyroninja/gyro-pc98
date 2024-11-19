#include "graphics.h"

void graphics_start() {
  asm volatile(
      "mov $0x40, %%ah\n"
      "int $0x18\n"
      : /* no output */
      : /* no input */
      : "ah");
}

void graphics_finish() {
  asm volatile(
      "mov $0x41, %%ah\n"
      "int $0x18\n"
      : /* no output */
      : /* no input */
      : "ah");
}

void graphics_set_mode(graphics_mode mode) {
  asm volatile(
      "mov $0x42, %%ah\n"
      "mov %0, %%ch\n"
      "int $0x18\n"
      : /* no output */
      : "r"(mode)
      : "ah");
}

void graphics_set_palette(struct graphics_ucw* ucw) {
  asm volatile(
      "mov $0x43, %%ah\n"
      "int $0x18\n"
      : /* no output */
      : "b"(ucw)
      : "ah");
}

void graphics_ucw_init_palette(struct graphics_ucw* ucw,
                               uint8_t color0,
                               uint8_t color1,
                               uint8_t color2,
                               uint8_t color3,
                               uint8_t color4,
                               uint8_t color5,
                               uint8_t color6,
                               uint8_t color7) {
  ucw->gbcpc[0] = ((color6 & 0xf0) << 4) | (color7 & 0x0f);
  ucw->gbcpc[1] = ((color4 & 0xf0) << 4) | (color5 & 0x0f);
  ucw->gbcpc[2] = ((color2 & 0xf0) << 4) | (color3 & 0x0f);
  ucw->gbcpc[3] = ((color0 & 0xf0) << 4) | (color1 & 0x0f);
}

void graphics_draw_line_rectangle(target_screens target_screens,
                                  struct graphics_ucw* ucw) {
  asm volatile(
      "mov $0x47, %%ah\n"
      "mov %0, %%ch\n"
      "int $0x18\n"
      : /* no output */
      : "r"(target_screens), "b"(ucw)
      : "ah");
}

void graphics_ucw_init_draw_line_rectangle(struct graphics_ucw* ucw,
                                           draw_mode modes,
                                           draw_operation operations,
                                           draw_direction direction,
                                           uint16_t x1,
                                           uint16_t y1,
                                           uint16_t x2,
                                           uint16_t y2,
                                           uint16_t line_pattern,
                                           draw_type type) {
  ucw->gbon_ptn = modes;
  ucw->gbdotu = operations;
  ucw->gbdsp = direction;
  ucw->gbsx1 = x1;
  ucw->gbsy1 = y1;
  ucw->gbsx2 = x2;
  ucw->gbsy2 = y2;
  ucw->gblptn_or_gbdoti.gblptn = line_pattern;
  ucw->gbdtyp = type;
}

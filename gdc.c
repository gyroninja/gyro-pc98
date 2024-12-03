#include "gdc.h"

#include <sys/io.h>

static void gdc_send_command(struct gdc gdc, uint8_t command) {
  while (inb(gdc.status_register_or_parameter_info_fifo) & GDC_STATUS_FIFO_FULL)
    ;
  outb(command, gdc.fifo_read_or_command_info_fifo);
}

static void gdc_send_paramter(struct gdc gdc, uint8_t parameter) {
  outb(parameter, gdc.status_register_or_parameter_info_fifo);
}

static void enable_16_colors() {
  outb(0x01, mode_ff_register2);
}

static void enable_full_resolution() {
  // Otherwise odd raster lines are skipped for 640x200
  outb(0x08, light_mode_register1);
}

void gdc_set_blank(struct gdc gdc, bool blank) {
  gdc_send_command(gdc, GDC_CONTROL_BLANK | blank);
}

static void gdc_set_sync(struct gdc gdc, bool master) {
  gdc_send_command(gdc, GDC_SYNC | master);
}

static void gdc_write_data(struct gdc gdc, uint8_t operation) {
  gdc_send_command(gdc, GDC_WRITE_DATA | operation);
}

static void gdc_set_cursor(struct gdc gdc, uint16_t x, uint16_t y, int i) {
  uint16_t offset = y * 40 + (x >> 4) + i;
  uint8_t bit_offset = x & 0x0f;
  gdc_send_command(gdc, GDC_SET_CURSOR);
  gdc_send_paramter(gdc, offset & 0xff);
  gdc_send_paramter(gdc, offset >> 8);
  gdc_send_paramter(gdc, bit_offset << 4);
}

static void gdc_set_cursor_and_character_characteristic(
    struct gdc gdc,
    uint8_t lines_per_character_row) {
  gdc_send_command(gdc, GDC_SET_CURSOR_AND_CHARACTER_CHARACTERISTIC);
  gdc_send_paramter(gdc, lines_per_character_row - 1);
}

static void gdc_set_line_pattern(struct gdc gdc, uint16_t pattern) {
  gdc_send_command(gdc, GDC_LOAD_PARAMETER_RAM | 0x08);
  gdc_send_paramter(gdc, pattern & 0xff);
  gdc_send_paramter(gdc, pattern >> 8);
}

static void gdc_set_master_slave(struct gdc master, struct gdc slave) {
  gdc_set_sync(slave, false);
  gdc_set_sync(master, true);
  // Wait for the gdcs to syncrhonize
  while ((inb(master.status_register_or_parameter_info_fifo) &
          GDC_STATUS_VERTICAL_SYNC_ACTIVE))
    ;
  while (!(inb(master.status_register_or_parameter_info_fifo) &
           GDC_STATUS_VERTICAL_SYNC_ACTIVE))
    ;
}

void gdc_init_graphics() {
  gdc_set_master_slave(GDC_GRAPHICS, GDC_TEXT);
  gdc_set_cursor_and_character_characteristic(GDC_GRAPHICS, 1);
  gdc_write_data(GDC_GRAPHICS, GDC_OPERATION_REPLACE);
  gdc_set_line_pattern(GDC_GRAPHICS, 0xffff);
  enable_16_colors();
  enable_full_resolution();
}

void gdc_rectangle(uint16_t plane,
                          uint16_t x1,
                          uint16_t y1,
                          uint16_t x2,
                          uint16_t y2) {
  uint16_t height = y2 - y1;
  uint16_t width = x2 - x1;
  gdc_set_cursor(GDC_GRAPHICS, x1, y1, plane);
  gdc_send_command(GDC_GRAPHICS, GDC_SET_FIGURE);
  gdc_send_paramter(GDC_GRAPHICS, 0x40 | 0x0);  // dir
  gdc_send_paramter(GDC_GRAPHICS, 0x03); // rectangle
  gdc_send_paramter(GDC_GRAPHICS, 0x00);
  gdc_send_paramter(GDC_GRAPHICS, (height - 1) & 0xff);  // height - 1
  gdc_send_paramter(GDC_GRAPHICS, (height - 1) >> 8);
  gdc_send_paramter(GDC_GRAPHICS, (width - 1) & 0xff);  // width - 1
  gdc_send_paramter(GDC_GRAPHICS, (width - 1) >> 8);
  gdc_send_paramter(GDC_GRAPHICS, 0xff);
  gdc_send_paramter(GDC_GRAPHICS, 0xff);
  gdc_send_paramter(GDC_GRAPHICS, (height - 1) & 0xff);  // height - 1
  gdc_send_paramter(GDC_GRAPHICS, (height - 1) >> 8);
  gdc_send_command(GDC_GRAPHICS, GDC_DRAW_FIGURE);
}

void set_palette(uint8_t palette, uint8_t red, uint8_t green, uint8_t blue) {
  outb(palette, palette_number_register);
  outb(green, green_level_register);
  outb(red, red_level_register);
  outb(blue, blue_level_register);
}

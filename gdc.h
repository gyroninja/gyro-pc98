#ifndef GDC_H
#define GDC_H

#include <stdbool.h>
#include <stdint.h>

struct gdc {
  uint8_t status_register_or_parameter_info_fifo;
  uint8_t fifo_read_or_command_info_fifo;
};

static const struct gdc GDC_TEXT = {0x60, 0x62};
static const struct gdc GDC_GRAPHICS = {0xa0, 0xa2};

static const uint8_t GDC_STATUS_LIGHT_PEN_DETECT = 0x80;
static const uint8_t GDC_STATUS_HORIZONTAL_BLANK_ACTIVE = 0x40;
static const uint8_t GDC_STATUS_VERTICAL_SYNC_ACTIVE = 0x20;
static const uint8_t GDC_STATUS_DMA_EXECUTE = 0x10;
static const uint8_t GDC_STATUS_DRAWING_IN_PROGRESS = 0x08;
static const uint8_t GDC_STATUS_FIFO_EMPTY = 0x04;
static const uint8_t GDC_STATUS_FIFO_FULL = 0x02;
static const uint8_t GDC_STATUS_FIFO_DATA_READY = 0x01;

static const uint8_t GDC_CONTROL_BLANK = 0x0c;
static const uint8_t GDC_SYNC = 0x0e;
static const uint8_t GDC_WRITE_DATA = 0x20;
static const uint8_t GDC_SET_CURSOR = 0x49;
static const uint8_t GDC_SET_CURSOR_AND_CHARACTER_CHARACTERISTIC = 0x4b;
static const uint8_t GDC_SET_FIGURE = 0x4c;
static const uint8_t GDC_DRAW_FIGURE = 0x6c;
static const uint8_t GDC_LOAD_PARAMETER_RAM = 0x70;

static const uint8_t GDC_OPERATION_REPLACE = 0x00;
static const uint8_t GDC_OPERATION_COMPLIMENT = 0x01;
static const uint8_t GDC_OPERATION_CLEAR = 0x10;
static const uint8_t GDC_OPERATION_SET = 0x11;

static const uint16_t GDC_PLANE1_ADDRESS = 0x0000;
static const uint16_t GDC_PLANE2_ADDRESS = 0x4000;
static const uint16_t GDC_PLANE3_ADDRESS = 0x8000;
static const uint16_t GDC_PLANE4_ADDRESS = 0xc000;

static const uint8_t mode_ff_register2 = 0x6a;
static const uint8_t light_mode_register1 = 0x68;
static const uint8_t palette_number_register = 0xa8;
static const uint8_t green_level_register = 0xaa;
static const uint8_t red_level_register = 0xac;
static const uint8_t blue_level_register = 0xae;

static void gdc_send_command(struct gdc gdc, uint8_t command);

static void gdc_send_paramter(struct gdc gdc, uint8_t parameter);

static void enable_16_colors();

static void enable_full_resolution();

void gdc_set_blank(struct gdc gdc, bool blank);

static void gdc_set_sync(struct gdc gdc, bool master);

static void gdc_write_data(struct gdc gdc, uint8_t operation);

static void gdc_set_cursor(struct gdc gdc, uint16_t x, uint16_t y, int i);

static void gdc_set_cursor_and_character_characteristic(
    struct gdc gdc,
    uint8_t lines_per_character_row);

static void gdc_set_line_pattern(struct gdc gdc, uint16_t pattern);

static void gdc_set_master_slave(struct gdc master, struct gdc slave);

void gdc_init_graphics();

void gdc_rectangle(uint16_t plane,
                          uint16_t x1,
                          uint16_t y1,
                          uint16_t x2,
                          uint16_t y2);

void set_palette(uint8_t palette, uint8_t red, uint8_t green, uint8_t blue);

#endif

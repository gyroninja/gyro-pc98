#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>

union __attribute__((packed)) gblptn_or_gbdoti {
  uint16_t gblptn;
  uint8_t gbdoti[8];
};

struct __attribute__((packed)) graphics_ucw {
  uint8_t gbon_ptn;
  uint8_t gbbcc;
  uint8_t gbdotu;
  uint8_t gbdsp;
  uint8_t gbcpc[4];
  uint16_t gbsx1;
  uint16_t gbsy1;
  uint16_t gblng1;
  uint16_t gbwdpa;
  uint16_t gbrbuf[3];
  uint16_t gbsx2;
  uint16_t gbsy2;
  uint16_t gbmdot;
  uint16_t gbcir;
  uint16_t gblng2;
  union gblptn_or_gbdoti gblptn_or_gbdoti;
  uint8_t gbdtyp;
  uint8_t gbfill;
  uint16_t gbgwk1;
  uint16_t gbgwk2;
  uint16_t gbgwk3;
  uint16_t gbgwk4;
  uint16_t gbgwk5;
  uint16_t gbgwk6;
  uint16_t gbgwk7;
  uint16_t gbgwk8;
  uint16_t gbgp12;
  uint16_t gbgp34;
  uint16_t gbgp56;
  uint16_t gbgp78;
  uint16_t gbgp910;
  uint16_t gbgp1112;
  uint16_t gbgp1314;
  uint16_t gbgp1516;
};

/**
 * graphics_mode The graphics mode to use.
 * 0bvvcm0000
 * v: The VRAM region to use.
 * c: The CRT display mode to use.
 * m: The memory bank to use.
 */
typedef uint8_t graphics_mode;
static const graphics_mode GRAPHICS_MODE_VRAM_REGION_UPPER = 0x40;
static const graphics_mode GRAPHICS_MODE_VRAM_REGION_LOWER = 0x80;
static const graphics_mode GRAPHICS_MODE_VRAM_REGION_ALL = 0xc0;
static const graphics_mode GRAPHICS_MODE_CRT_DISPLAY_COLOR = 0x00;
static const graphics_mode GRAPHICS_MODE_CRT_DISPLAY_MONOCHROME = 0x20;
static const graphics_mode GRAPHICS_MODE_DISPLAY_BANK0 = 0x00;
static const graphics_mode GRAPHICS_MODE_DISPLAY_BANK1 = 0x10;

/**
 * target_screens The screens that should be drawn to.
 * 0brspp0000
 * r: The resolution to draw at.
 * s: The screen region to draw to.
 * p: The planes to draw to.
 */
typedef uint8_t target_screens;
static const target_screens TARGET_SCREENS_STANDARD_RESOLUTION = 0x00;
static const target_screens TARGET_SCREENS_HIGH_RESOLUTION = 0x80;
static const target_screens TARGET_SCREENS_LOWER_ALL = 0x80;
static const target_screens TARGET_SCREENS_UPPER = 0x40;
static const target_screens TARGET_SCREENS_PLANE1 = 0x00;
static const target_screens TARGET_SCREENS_PLANE2 = 0x10;
static const target_screens TARGET_SCREENS_PLANE3 = 0x20;
static const target_screens TARGET_SCREENS_PLANE123 = 0x30;

typedef uint8_t draw_mode;
/**
 * draw_mode Whether 0 or 1 should be drawn.
 * 0b00000ppp
 * p: If the plane should be cleared or set to.
 */
static const draw_mode DRAW_MODE_PLANE1_CLEAR = 0x00;
static const draw_mode DRAW_MODE_PLANE1_SET = 0x01;
static const draw_mode DRAW_MODE_PLANE2_CLEAR = 0x00;
static const draw_mode DRAW_MODE_PLANE2_SET = 0x02;
static const draw_mode DRAW_MODE_PLANE3_CLEAR = 0x00;
static const draw_mode DRAW_MODE_PLANE3_SET = 0x04;

typedef uint8_t draw_operation;
static const draw_operation DRAW_OPERATION_REPLACE = 0x00;
static const draw_operation DRAW_OPERATION_COMPLIMENT = 0x01;
static const draw_operation DRAW_OPERATION_CLEAR = 0x02;
static const draw_operation DRAW_OPERATION_SET = 0x03;

typedef uint8_t draw_direction;
static const draw_direction DRAW_DIRECTION_LINE_DOWN = 0;
static const draw_direction DRAW_DIRECTION_LINE_DOWN_RIGHT = 1;
static const draw_direction DRAW_DIRECTION_LINE_RIGHT = 2;
static const draw_direction DRAW_DIRECTION_LINE_UP_RIGHT = 3;
static const draw_direction DRAW_DIRECTION_LINE_UP = 4;
static const draw_direction DRAW_DIRECTION_LINE_UP_LEFT = 5;
static const draw_direction DRAW_DIRECTION_LINE_LEFT = 6;
static const draw_direction DRAW_DIRECTION_LINE_DOWN_LEFT = 7;
static const draw_direction DRAW_DIRECTION_RECTANGLE_TOP_LEFT_BOTTOM_RIGHT = 0;
static const draw_direction DRAW_DIRECTION_DIAMOND_LEFT_RIGHT = 1;
static const draw_direction DRAW_DIRECTION_RECTANGLE_BOTTOM_LEFT_TOP_RIGHT = 2;
static const draw_direction DRAW_DIRECTION_DIAMOND_BOTTOM_TOP = 3;
static const draw_direction DRAW_DIRECTION_RECTANGLE_BOTTOM_RIGHT_TOP_LEFT = 4;
static const draw_direction DRAW_DIRECTION_DIAMOND_RIGHT_LEFT = 5;
static const draw_direction DRAW_DIRECTION_RECTANGLE_TOP_RIGHT_BOTTOM_LEFT = 6;
static const draw_direction DRAW_DIRECTION_DIAMOND_TOP_BOTTOM = 7;

typedef uint8_t draw_type;
static const draw_type DRAW_TYPE_LINE = 0x01;
static const draw_type DRAW_TYPE_RECTANGLE = 0x02;

/**
 * graphics_start() - Starts showing the graphics screen.
 */
void graphics_start();

/**
 * graphics_finish() - Finishes showing the graphics screen.
 *
 * Any graphics that were previously showing will be cleared.
 */
void graphics_finish();

/**
 * graphics_set_mode() - Set the display mode settings
 * @param mode The VRAM region, CRT display mode, and memory bank
 */
void graphics_set_mode(graphics_mode mode);

/**
 * graphics_draw_line_rectangle - Draws a straight line or rectangle.
 * @param target_screens Defines the screens that will be drawn to.
 * @param ucw The unit control word containing data about what to draw.
 *
 * Before calling this function ucw should be initialized by calling
 * graphics_ucw_draw_init_line_rectangle().
 */
void graphics_draw_line_rectangle(target_screens target_screens,
                                  struct graphics_ucw* ucw);

/**
 * graphics_ucw_init_line_rectangle - Initialize UCW for a line or rectangle.
 * @param ucw The UCW that should be initialized.
 * @param drawing_modes The drawing mode that should be used for each plane.
 * @param drawing_operations The operation that should be used for drawing.
 * @param direction The direction for drawing betwen (x1, y1) and (x2, y2)
 * @param x1 The x coordinate of the first point.
 * @param y1 The y coordinate of the first point.
 * @param x2 The x coordinate of the second point.
 * @param y2 The y coordinate of the second point.
 * @param line_pattern The 16 bit long line pattern that should be drawn in.
 * @param type Whether a line or a rectangle should be drawn.
 */
void graphics_ucw_init_line_rectangle(struct graphics_ucw* ucw,
                                      draw_mode modes,
                                      draw_operation operations,
                                      draw_direction direction,
                                      uint16_t x1,
                                      uint16_t y1,
                                      uint16_t x2,
                                      uint16_t y2,
                                      uint16_t line_pattern,
                                      draw_type type);

#endif
#ifndef RASTERIZER_H
#define RASTERIZER_H
#include <stdint.h>

#include "settings.h"

#define COLOR(r, g, b)                                                         \
  (struct Color) { r, g, b }

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

struct Pixel {
  struct Color color;
  float z_depth;
};

static struct Color WHITE = COLOR(255, 255, 255);
static struct Color BLACK = COLOR(0, 0, 0);
static struct Color RED = COLOR(255, 0, 0);
static struct Color GREEN = COLOR(0, 255, 0);
static struct Color BLUE = COLOR(0, 0, 255);

extern struct Pixel raster_buffer[DISPLAY_HEIGHT][DISPLAY_WIDTH];

void raster_render();
void draw_pixel(int x, int y, struct Color color);
void draw_line(int x1, int y1, int x2, int y2, struct Color color);
void draw_triangle(int *vertices, struct Color color, int fill);
#endif

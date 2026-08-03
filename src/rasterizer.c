#include <glad/gl.h>

#include "rasterizer.h"
#include "settings.h"

struct Pixel raster_buffer[DISPLAY_HEIGHT][DISPLAY_WIDTH];
int buffer_initialized = 0;

void try_init_buffer() {
  if (!buffer_initialized) {
    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
      for (int x = 0; x < DISPLAY_WIDTH; x++) {
        raster_buffer[y][x].color = BLACK;
      }
    }
    buffer_initialized = 1;
  }
}

void raster_render() {
  try_init_buffer();
  // I need some clarity on what these lines are doing
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glBegin(GL_POINTS);
  for (int y = 0; y < DISPLAY_HEIGHT; y++) {
    for (int x = 0; x < DISPLAY_WIDTH; x++) {
      struct Pixel px = raster_buffer[y][x];
      glColor3ub(px.color.r, px.color.g, px.color.b);
      glVertex2f(x, y);
    }
  }
  glEnd();
}

void draw_pixel(int x, int y, struct Color color) {
  if ((x >= DISPLAY_WIDTH || x < 0) || (y >= DISPLAY_HEIGHT || y < 0)) {
    return;
  }
  raster_buffer[y][x].color = color;
}

// This is an extremely simple line calculation
// There are better algorithms
void draw_line(int x1, int y1, int x2, int y2, struct Color color) {
  int dX = x2 - x1;
  int dY = y2 - y1;
  float m = (float)dY / dX;
  for (int x = x1; x <= x2; x++) {
    int y = (int)(m * (x - x1) + y1);
    draw_pixel(x, y, color);
  }
}

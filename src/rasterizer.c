#include <glad/gl.h>

#include "rasterizer.h"
#include "settings.h"
struct Pixel raster_buffer[DISPLAY_WIDTH][DISPLAY_HEIGHT];
int buffer_initialized = 0;

void init_buffer() {
  for (int y = 0; y < DISPLAY_HEIGHT; y++) {
    for (int x = 0; x < DISPLAY_WIDTH; x++) {
      raster_buffer[x][y].color = BLACK;
    }
  }
  buffer_initialized = 1;
}

void raster_render() {
  if (!buffer_initialized) {
    init_buffer();
  }
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
      struct Pixel px = raster_buffer[x][y];
      glColor3ub(px.color.r, px.color.g, px.color.b);
      glVertex2f(x, y);
    }
  }
  glEnd();
}

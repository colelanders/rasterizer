#include <glad/gl.h>
#include <limits.h>
#include <stdlib.h>

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
  try_init_buffer();
  if ((x >= DISPLAY_WIDTH || x < 0) || (y >= DISPLAY_HEIGHT || y < 0)) {
    return;
  }
  raster_buffer[y][x].color = color;
}

// This is an extremely simple line calculation
// There are better algorithms

void draw_line(int x1, int y1, int x2, int y2, struct Color color) {
  try_init_buffer();
  int dX = x2 - x1;
  int dY = y2 - y1;

  if (abs(dX) >= abs(dY)) {
    float m = (float)dY / dX;
    int step = (dX >= 0) ? 1 : -1;
    for (int x = x1; x != x2 + step; x += step) {
      int y = (int)(m * (x - x1) + y1);
      draw_pixel(x, y, color);
    }
  } else {
    float m = (float)dX / dY;
    int step = (dY >= 0) ? 1 : -1;
    for (int y = y1; y != y2 + step; y += step) {
      int x = (int)(m * (y - y1) + x1);
      draw_pixel(x, y, color);
    }
  }
}

void draw_triangle(int *vertices, struct Color color, int fill) {
  try_init_buffer();
  int *vertex1 = vertices;
  int *vertex2 = vertices + 2;
  int *vertex3 = vertices + 4;

  if (fill) {
    int minY = INT_MAX;
    int maxY = INT_MIN;
    for (int i = 1; i < 6; i += 2) {
      int value = *(vertices + i);
      if (value < minY) {
        minY = value;
      }
      if (value > maxY) {
        maxY = value;
      }
    }

    for (int y = minY; y <= maxY; y++) {
      int xStart, xEnd;
      for (int x = xStart; x <= xEnd; x++) {
        draw_pixel(x, y, color);
      }
    }
  } else {
    draw_line(*vertex1, *(vertex1 + 1), *vertex2, *(vertex2 + 1), color);
    draw_line(*vertex2, *(vertex2 + 1), *vertex3, *(vertex3 + 1), color);
    draw_line(*vertex1, *(vertex1 + 1), *vertex3, *(vertex3 + 1), color);
  }
}

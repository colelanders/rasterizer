#include "rasterizer.h"
#include "settings.h"
struct Pixel raster_buffer[DISPLAY_WIDTH][DISPLAY_HEIGHT];
void init_raster_renderer();

void init_raster_renderer() {
  for (int y = 0; y < DISPLAY_HEIGHT; y++) {
    for (int x = 0; x < DISPLAY_WIDTH; x++) {
      raster_buffer[x][y].color = BLUE;
    }
  }
}

#include <GLFW/glfw3.h>
#include <stdio.h>

#include "fps_counter.h"

int enabled = 0;
int framecount = 0;

void enable_fps_logging(int enable) { enabled = enable; }

void fps_tick() {
  if (glfwGetTime() >= 1.0) {
    printf("\rFPS: %d", framecount);
    fflush(stdout);
    glfwSetTime(0.0);
    framecount = 0;
  }
  framecount++;
}

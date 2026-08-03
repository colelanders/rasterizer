#include "glad/gl.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "rasterizer.h"
#include "settings.h"
static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods);

int main(int argc, char **argv) {
  if (!glfwInit()) {
    printf("Error initializing GLFW");
    exit(EXIT_FAILURE);
  }

  GLFWwindow *window =
      glfwCreateWindow(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Rasterizer", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);
  gladLoadGL(glfwGetProcAddress);
  glfwSwapInterval(0);

  glfwSetKeyCallback(window, key_callback);

  init_raster_renderer();

  int framecount = 0;

  while (!glfwWindowShouldClose(window)) {
    if (glfwGetTime() >= 1.0) {
      printf("\rFPS: %d", framecount);
      fflush(stdout);
      glfwSetTime(0.0);
      framecount = 0;
    }
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

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

    glfwSwapBuffers(window);
    glfwPollEvents();
    framecount++;
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

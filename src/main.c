#include "glad/gl.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

const int HEIGHT = 480;
const int WIDTH = 640;

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods);

int main(int argc, char **argv) {
  if (!glfwInit()) {
    printf("Error initializing GLFW");
    exit(EXIT_FAILURE);
  }

  GLFWwindow *window =
      glfwCreateWindow(WIDTH, HEIGHT, "Rasterizer", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);
  gladLoadGL(glfwGetProcAddress);

  glfwSetKeyCallback(window, key_callback);

  int framecount = 0;

  while (!glfwWindowShouldClose(window)) {
    if (glfwGetTime() >= 1.0) {
      printf("\rFPS: %d", framecount);
      fflush(stdout);
      glfwSetTime(0.0);
      framecount = 0;
    }
    // do stuff!
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

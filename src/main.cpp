#include "glad/gl.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <stdio.h>

const int HEIGHT = 480;
const int WIDTH = 640;

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

  while (!glfwWindowShouldClose(window)) {
    // run
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}

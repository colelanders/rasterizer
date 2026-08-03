#include "glad/gl.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "fps_counter.h"
#include "rasterizer.h"
#include "settings.h"
static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods);

int main(int argc, char **argv) {
  // Initialize GLFW
  if (!glfwInit()) {
    exit(EXIT_FAILURE);
  }

  // Create window and assign OpenGL context
  GLFWwindow *window =
      glfwCreateWindow(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Rasterizer", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);

  // Initialize GLAD
  int version = gladLoadGL(glfwGetProcAddress);
  if (version == 0) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // Adjust GLFW settings
  glfwSwapInterval(0); // v-sync
  glfwSetKeyCallback(window, key_callback);

  // Adjust internal settings
  enable_fps_logging(1);

  while (!glfwWindowShouldClose(window)) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // rasterizer
    raster_render();

    glfwSwapBuffers(window);
    glfwPollEvents();
    fps_tick();
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

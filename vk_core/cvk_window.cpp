#include "cvk_window.hpp"

// std
#include <stdexcept>

namespace cvk {

CvkWindow::CvkWindow(int w, int h, std::string name) : width{w}, height{h}, windowName{name} {
  initWindow();
}

CvkWindow::~CvkWindow() {
  glfwDestroyWindow(window);
  glfwTerminate();
}

void CvkWindow::initWindow() {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
  glfwSetWindowUserPointer(window, this);
  glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

void CvkWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
  if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
    throw std::runtime_error("failed to craete window surface");
  }
}

void CvkWindow::framebufferResizeCallback(GLFWwindow *window, int width, int height) {
  auto cvkWindow = reinterpret_cast<CvkWindow *>(glfwGetWindowUserPointer(window));
  cvkWindow->framebufferResized = true;
  cvkWindow->width = width;
  cvkWindow->height = height;
}

}  // namespace cvk

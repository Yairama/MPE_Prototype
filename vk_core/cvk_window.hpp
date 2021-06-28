#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>
namespace cvk {

    class CvkWindow {
    public:
        CvkWindow(int w, int h, std::string name);
        ~CvkWindow();

        CvkWindow(const CvkWindow &) = delete;
        CvkWindow &operator=(const CvkWindow &) = delete;

        bool shouldClose() { return glfwWindowShouldClose(window); }
        VkExtent2D getExtent() { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }
        bool wasWindowResized() { return framebufferResized; }
        void resetWindowResizedFlag() { framebufferResized = false; }

        void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);
        GLFWwindow *getGLFWWindow() { return window; }

    private:
        static void framebufferResizeCallback(GLFWwindow *window, int width, int height);
        void initWindow();

        int width;
        int height;
        bool framebufferResized = false;

        std::string windowName;
        GLFWwindow *window;
    };
}  // namespace cvk

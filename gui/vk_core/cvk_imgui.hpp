//
// Created by yair0 on 27/06/2021.
//


#pragma once

#include "../../vk_core/cvk_device.hpp"
#include "../../vk_core/cvk_window.hpp"

// libs
#include "../../lib/imgui/imgui.h"
#include "../../lib/imgui/imgui_impl_glfw.h"
#include "../../lib/imgui/imgui_impl_vulkan.h"

// std
#include <stdexcept>

// This whole class is only necessary right now because it needs to manage the descriptor pool
// because we haven't set one up anywhere else in the application, and we manage the
// example state, otherwise all the functions could just be static helper functions if you prefered
namespace cvk {

    static void check_vk_result(VkResult err) {
        if (err == 0) return;
        fprintf(stderr, "[vulkan] Error: VkResult = %d\n", err);
        if (err < 0) abort();
    }

    class CvkImgui {
    public:
        CvkImgui(CvkWindow &window, CvkDevice &device, VkRenderPass renderPass, uint32_t imageCount);
        ~CvkImgui();

        void newFrame();

        void render(VkCommandBuffer commandBuffer);

        // Example state
        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        ImVec2 projectNodesSize = ImVec2(300,300);
        ImVec2 filesChooserSize = ImVec2(300,300);
        void runExample();

    private:
        CvkDevice &cvkDevice;

        // We haven't yet covered descriptor pools in the tutorial series
        // so I'm just going to create one for just imgui and store it here for now.
        // maybe its preferred to have a separate descriptor pool for imgui anyway,
        // I haven't looked into imgui best practices at all.
        VkDescriptorPool descriptorPool;
    };
}  // namespace cvk

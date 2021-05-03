#pragma once

#include "cvk_device.hpp"
#include "cvk_game_object.hpp"
#include "cvk_pipeline.hpp"

// std
#include <memory>
#include <vector>

namespace cvk {
    class SimpleRenderSystem {
    public:

        SimpleRenderSystem(CvkDevice& device, VkRenderPass renderPass);
        ~SimpleRenderSystem();

        SimpleRenderSystem(const SimpleRenderSystem &) = delete;
        SimpleRenderSystem &operator=(const SimpleRenderSystem &) = delete;

        void renderGameObjects(VkCommandBuffer commandBuffer, std::vector<CvkGameObject> &gameObjects);

    private:
        void createPipelineLayout();
        void createPipeline(VkRenderPass renderPass);


        CvkDevice &cvkDevice;
        std::unique_ptr<CvkPipeline> cvkPipeline;
        VkPipelineLayout pipelineLayout;
    };
}  // namespace cvk

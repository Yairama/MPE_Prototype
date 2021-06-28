#pragma once

#include "cvk_device.hpp"
#include "cvk_model.hpp"
#include "cvk_swap_chain.hpp"
#include "cvk_window.hpp"

// std
#include <memory>
#include <vector>

namespace cvk {
    class CvkRenderer {
    public:

        CvkRenderer(CvkWindow &window, CvkDevice &device);
        ~CvkRenderer();

        CvkRenderer(const CvkRenderer &) = delete;
        CvkRenderer &operator=(const CvkRenderer &) = delete;

        VkRenderPass getSwapChainRenderPass() const {return  cvkSwapChain->getRenderPass();}
        uint32_t getImageCount() const { return cvkSwapChain->imageCount(); }
        float getAspectRatio() const {return cvkSwapChain->extentAspectRatio();}
        bool isFrameInProgress() const {return isFrameStarted;}

        VkCommandBuffer getCurrentCommandBuffer() const {
            assert(isFrameStarted && "Cannot get command buffer when frame is not in progress");
            return commandBuffers[currentFrameIndex];
        }

        int getFrameIndex() const {
            assert(isFrameStarted && "Cannot get frame index when frame not in progress");
            return currentFrameIndex;
        }

        VkCommandBuffer beginFrame();
        void endFrame();
        void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
        void endSwapChainRenderPass(VkCommandBuffer commandBuffer);


    private:
        void createCommandBuffers();
        void freeCommandBuffers();
        void recreateSwapChain();


        CvkWindow& cvkWindow;
        CvkDevice& cvkDevice;
        std::unique_ptr<CvkSwapChain> cvkSwapChain;
        std::vector<VkCommandBuffer> commandBuffers;

        uint32_t currentImageIndex;
        int currentFrameIndex{0};
        bool isFrameStarted{false};
    };
}  // namespace cvk

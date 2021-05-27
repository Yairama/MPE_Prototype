#include "simple_render_system.hpp"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

// std
#include <array>
#include <cassert>
#include <stdexcept>

namespace cvk {

    struct SimplePushConstantData{
        glm::mat2 transform{1.f};
        glm::vec2 offset;
        alignas(16) glm::vec3 color;
    };

    SimpleRenderSystem::SimpleRenderSystem(CvkDevice& device, VkRenderPass renderPass) : cvkDevice{device} {
        createPipelineLayout();
        createPipeline(renderPass);
    }

    SimpleRenderSystem::~SimpleRenderSystem() { vkDestroyPipelineLayout(cvkDevice.device(), pipelineLayout, nullptr); }




    void SimpleRenderSystem::createPipelineLayout() {

        VkPushConstantRange pushConstantRange{};
        pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
        pushConstantRange.offset = 0;
        pushConstantRange.size = sizeof(SimplePushConstantData);

        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pSetLayouts = nullptr;
        pipelineLayoutInfo.pushConstantRangeCount = 1;
        pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;
        if (vkCreatePipelineLayout(cvkDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) !=
            VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline layout!");
        }
    }



    void SimpleRenderSystem::createPipeline(VkRenderPass renderPass) {
        assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

        PipelineConfigInfo pipelineConfig{};
        CvkPipeline::defaultPipelineConfigInfo(pipelineConfig);
        pipelineConfig.renderPass = renderPass;
        pipelineConfig.pipelineLayout = pipelineLayout;
        cvkPipeline = std::make_unique<CvkPipeline>(
                cvkDevice,
                R"(C:\Users\Yairama\Desktop\WeCandoIt\MPE_Prototype\vk_core\shaders\simple_shader.vert.spv)",
                R"(C:\Users\Yairama\Desktop\WeCandoIt\MPE_Prototype\vk_core\shaders\simple_shader.frag.spv)",
                pipelineConfig);
    }



    void SimpleRenderSystem::renderGameObjects(VkCommandBuffer commandBuffer,
                                                 std::vector<CvkGameObject> &gameObjects) {
        cvkPipeline->bind(commandBuffer);

        for(auto &obj : gameObjects){
            obj.transform2D.rotation = glm::mod(obj.transform2D.rotation+0.01f, glm::two_pi<float>());

            SimplePushConstantData push{};
            push.offset = obj.transform2D.translation;
            push.color = obj.color;
            push.transform = obj.transform2D.mat2();

            vkCmdPushConstants(commandBuffer, pipelineLayout,
                               VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
                               0, sizeof(SimplePushConstantData), &push);


            obj.model->bind(commandBuffer);
            obj.model->draw(commandBuffer);
        }

    }


}  // namespace cvk

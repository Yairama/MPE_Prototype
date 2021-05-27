#include "first_app.hpp"
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

    FirstApp::FirstApp() {
        loadGameObjects();
    }

    FirstApp::~FirstApp() {}

    void FirstApp::run() {
        SimpleRenderSystem simpleRenderSystem{cvkDevice, cvkRenderer.getSwapChainRenderPass()};
        while (!cvkWindow.shouldClose()) {
            glfwPollEvents();
            if(auto commandBuffer = cvkRenderer.beginFrame()){

                // begin offscreen shadow pass
                // render shadow casting objects
                // end offscreen shadow pass

                cvkRenderer.beginSwapChainRenderPass(commandBuffer);
                simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects);
                cvkRenderer.endSwapChainRenderPass(commandBuffer);
                cvkRenderer.endFrame();
            }
        }

        vkDeviceWaitIdle(cvkDevice.device());
    }

    void FirstApp::loadGameObjects() {
        std::vector<CvkModel::Vertex> vertices{
                {{0.0f,  -0.5f}, {1.0f, 0.0f, 0.0f}},
                {{0.5f,  0.5f},  {0.0f, 1.0f, 0.0f}},
                {{-0.5f, 0.5f},  {0.0f, 0.0f, 1.0f}}};
        auto cvkModel = std::make_shared<CvkModel>(cvkDevice, vertices);
        auto triangle = CvkGameObject::createGameObject();
        triangle.model = cvkModel;
        triangle.color = {0.1f, 0.8f, 0.1f};
        triangle.transform2D.translation.x = 0.2f;
        triangle.transform2D.scale = {2.0f,0.5f};
        triangle.transform2D.rotation = 0.25f * glm::two_pi<float>();

        gameObjects.push_back(std::move(triangle));
    }


}  // namespace cvk

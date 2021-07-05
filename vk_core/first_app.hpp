#pragma once

#include "cvk_device.hpp"
#include "cvk_game_object.hpp"
#include "cvk_renderer.hpp"
#include "cvk_window.hpp"


// std
#include <memory>
#include <vector>

namespace cvk {
    class FirstApp {
    public:
        static constexpr int WIDTH = 1366;
        static constexpr int HEIGHT = 768;

        FirstApp();
        ~FirstApp();

        FirstApp(const FirstApp &) = delete;
        FirstApp &operator=(const FirstApp &) = delete;

    void run();

    private:
        void loadGameObjects();

        CvkWindow cvkWindow{WIDTH, HEIGHT, "Mining Planning Engine"};
        CvkDevice cvkDevice{cvkWindow};
        CvkRenderer cvkRenderer{cvkWindow,cvkDevice};
        std::vector<CvkGameObject> gameObjects;
    };
}  // namespace cvk

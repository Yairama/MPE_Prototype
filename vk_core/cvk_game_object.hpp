#pragma once

#include "cvk_model.hpp"
#include <memory>

namespace cvk{

    struct Transform2dComponent{
        glm::vec2 translation{}; //position offset
        glm::vec2 scale {1.f,1.f};
        float rotation;

        glm::mat2 mat2() {
            const float s = glm::sin(rotation);
            const float c = glm::cos(rotation);
            glm::mat2 rotMatrix{{c,s},{-s,c}};

            glm::mat2 scaleMat({scale.x,0.0f},{0.0f, scale.y});
            return rotMatrix * scaleMat;
        }
    };

    class CvkGameObject{
    public:
        using id_t = unsigned int;

        static CvkGameObject createGameObject(){
            static id_t currentId = 0;
            return CvkGameObject(currentId++);
        }

        CvkGameObject(const CvkGameObject &) = delete;
        CvkGameObject &operator = (const CvkGameObject &) = delete;
        CvkGameObject(CvkGameObject &&) = default;
        CvkGameObject &operator = (CvkGameObject &&) = default;

        id_t getId() {return id;}

        std::shared_ptr<CvkModel> model{};
        glm::vec3 color{};
        Transform2dComponent transform2D{};

    private:
        CvkGameObject(id_t objId) : id{objId}{}

        id_t id;
    };

}
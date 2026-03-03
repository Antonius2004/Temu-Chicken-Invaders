//
// Created by patur on 11/8/2025.
//

#ifndef GFXFRAMEWORK_CHICKEN_H
#define GFXFRAMEWORK_CHICKEN_H

#include "constants.h"
#include "glm/glm.hpp"


namespace m1 {
    class Chicken {
    public:
        Chicken();
        Chicken(glm::vec3 corner1) {
            setCorner(corner1);
        }

        void setCorner(glm::vec3 c) {
            this->corner = c;
        }

        glm::vec3 getCorner() {
            return this->corner;
        }

        bool isAlive() {
            return this->alive;
        }

        void setAlive(bool alive1) {
            this->alive = alive1;
        }

        glm::vec3 getCenter() {
            return this->corner + glm::vec3(side / 2.f, side / 2.f, 0);
        }

        float getHitboxRadius() {
            return this->hitboxRadius;
        }

        void addMove(glm::vec3 move1);

    private:
        glm::vec3 corner{0, 0, 0};
        float side = EDIT_BLOCK_LEN;
        float hitboxRadius = EDIT_BLOCK_LEN * 1.5f;
        glm::vec2 move{0.f, 0.f};
        bool alive = true;
    };
} // m1

#endif //GFXFRAMEWORK_CHICKEN_H
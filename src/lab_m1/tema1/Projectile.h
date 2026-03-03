//
// Created by patur on 11/8/2025.
//

#ifndef GFXFRAMEWORK_PROJECTILE_H
#define GFXFRAMEWORK_PROJECTILE_H

#include <glm/glm.hpp>

namespace m1 {
    class Projectile {
    protected:
        glm::vec3 corner{0, 0, 0};
        float radius = 0;
        glm::vec3 center{0, 0, 0};
        float scale = 1.f;
        float moveFactor = 500.f;



    public:
        bool isInsideSquare(glm::vec3 corner, float width, float height);
        bool isInsideCircle(glm::vec3 center, float radius);
        void addMove(float deltaTime, int dir);

        glm::vec3 getCorner() {
            return this->corner;
        }

        float getRadius() {
            return this->radius;
        }

        glm::vec3 getCenter() {
            return this->corner + glm::vec3(radius, radius, 0);
        }

    };
} // m1

#endif //GFXFRAMEWORK_PROJECTILE_H
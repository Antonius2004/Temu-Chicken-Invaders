//
// Created by patur on 11/8/2025.
//

#include "Projectile.h"
#include "constants.h"

namespace m1 {
    bool Projectile::isInsideSquare(glm::vec3 corner, float width, float height) {
        // Checks if center of projectile is inside a square hitbox
        glm::vec3 projCenter = this->getCenter();

        if (projCenter.x < corner.x) return false;
        if (projCenter.x > corner.x + width) return false;
        if (projCenter.y < corner.y) return false;
        if (projCenter.y > corner.y + height) return false;

        return true;
    }

    bool Projectile::isInsideCircle(glm::vec3 center, float radius) {
        // Checks if center of projectile is inside a circle hitbox
        glm::vec3 projCenter = this->getCenter();

        float dx = projCenter.x - center.x;
        float dy = projCenter.y - center.y;

        return dx * dx + dy * dy <= radius * radius;
    }

    void Projectile::addMove(float deltaTime, int dir) {
        if (dir == UP_DIRECTION)
            this->corner += glm::vec3(0, deltaTime * moveFactor, 0);
        else if (dir == DOWN_DIRECTION)
            this->corner -= glm::vec3(0, deltaTime * moveFactor, 0);
    }
} // m1
//
// Created by patur on 12/8/2025.
//

#include "Rail.h"

namespace m1 {
    glm::vec3 Rail::GetClosestPosition(const glm::vec3 position) const {
        glm::vec3 P = position;
        glm::vec3 A = this->pos1();
        glm::vec3 B = this->pos2();

        float dA2 = glm::dot(P - A, P - A);
        float dB2 = glm::dot(P - B, P - B);

        glm::vec3 closest = (dA2 < dB2) ? A : B;

        return closest;
    }

} // m1
//
// Created by patur on 11/8/2025.
//

#ifndef GFXFRAMEWORK_CHICKENPROJECTILE_H
#define GFXFRAMEWORK_CHICKENPROJECTILE_H

#include "Projectile.h"
#include "constants.h"

namespace m1 {
    class ChickenProjectile : public Projectile {
    public:
        explicit ChickenProjectile(glm::vec3 corner) {
            this->corner = corner;
            this->radius = CHICKEN_PROJ_RAD;
            this->center = corner + glm::vec3(radius / 2.f, radius / 2.f, 0);
        }
    };
} // m1

#endif //GFXFRAMEWORK_CHICKENPROJECTILE_H
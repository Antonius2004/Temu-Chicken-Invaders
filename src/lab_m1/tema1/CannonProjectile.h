//
// Created by patur on 11/8/2025.
//

#ifndef GFXFRAMEWORK_CANNONPROJECTILE_H
#define GFXFRAMEWORK_CANNONPROJECTILE_H

#include "constants.h"
#include "Projectile.h"

namespace m1 {
    class CannonProjectile : public Projectile {
    public:
        explicit CannonProjectile(glm::vec3 corner) {
            this->corner = corner;
            this->radius = CANNON_PROJ_RAD;
            this->center = corner + glm::vec3(radius / 2.f, radius / 2.f, 0);
        }
    };

} // m1

#endif //GFXFRAMEWORK_CANNONPROJECTILE_H
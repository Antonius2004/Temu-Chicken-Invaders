//
// Created by patur on 11/6/2025.
//

#include "InteractableMesh.h"

namespace m1 {
    bool InteractableMesh::isInside(int mouseX, int mouseY) {
        glm::vec3 topRightCorner = this->corner + glm::vec3(this->width, this->height, 0);

        if (mouseX >= this->corner.x && mouseX <= topRightCorner.x && mouseY >= this->corner.y && mouseY <= topRightCorner.y)
            return true;

        return false;
    }

} // m1
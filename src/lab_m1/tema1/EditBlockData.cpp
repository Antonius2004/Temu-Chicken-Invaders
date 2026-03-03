//
// Created by patur on 11/6/2025.
//

#include "EditBlockData.h"
#include "InteractableMesh.h"

namespace m1 {
    bool EditBlockData::isInside(int mouseX, int mouseY) {
        // Checks if given coords are inside this square
        return mouseX >= corner.x && mouseX <= corner.x + side &&
               mouseY >= corner.y && mouseY <= corner.y + side;
    }

    bool EditBlockData::canPlace(InteractableMesh im, std::vector<std::vector<EditBlockData>> mat) {
        // Checks if there's enough space to place a block
        // Mostly for cannon and thruster
        if (im.getName() == "cannon") {
            if (this->getPos().x > EDIT_MATRIX_H - 3) return false;
            return true;
        }

        if (im.getName() == "thruster") {
            // If it's on last row
            if (this->getPos().x == 0) return false;

            // If it has a block taken below it
            if (mat[this->getPos().x - 1][this->getPos().y].taken1()) return false;

            return true;
        }

        return true;
    }

} // m1
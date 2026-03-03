//
// Created by patur on 12/11/2025.
//

#ifndef GFXFRAMEWORK_WAGON_H
#define GFXFRAMEWORK_WAGON_H

#include "Train.h"

namespace m1 {
    class Wagon : public Train {
    public:
        Wagon() = default;

        Wagon(Rail rail, glm::vec3 position, Block *current_block) {
            this->rail_ = rail;
            this->progress_ = 0.f;
            this->speed_ = TRAIN_SPEED;
            glm::vec3 offset = glm::vec3(SIZE_SEGMENT / 2.f, 0, 0);
            this->position_ = position + offset;
            this->heading_ = Headings::E;
            this->current_block_ = current_block;
        }
    };
} // m1

#endif //GFXFRAMEWORK_WAGON_H
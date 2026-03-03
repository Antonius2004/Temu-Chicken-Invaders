//
// Created by patur on 12/12/2025.
//

#ifndef GFXFRAMEWORK_DRAISIN_H
#define GFXFRAMEWORK_DRAISIN_H
#include "Train.h"

namespace m1 {
    class Draisine : public Train {
    public:
        Draisine() = default;

        Draisine(Rail rail, glm::vec3 position, Block *current_block) {
            this->rail_ = rail;
            this->progress_ = 0.f;
            this->speed_ = 0.f;
            glm::vec3 offset = glm::vec3(SIZE_SEGMENT / 2.f, 0, SIZE_SEGMENT / 2.f);
            this->position_ = position + offset;
            this->heading_ = Headings::E;
            this->current_block_ = current_block;

            this->corner_ = this->position() + glm::vec3(-base_width / 2.f, 0, -base_length / 2.f);
            this->handle_position_ = this->position_ + glm::vec3(0, 2, 0);
        }

        void Accelerate(float deltaTimeSeconds);
        void Deccelerate(float deltaTimeSeconds);
        void UpdatePosition();
        void SetPosition(glm::vec3 new_position);

        AABB get_hitbox() const;
        bool contains_point(const glm::vec3& p) const;

        glm::vec3 handle_position_;

    private:
        float hitbox_padding_ = 0.5f;
    };
} // m1

#endif //GFXFRAMEWORK_DRAISIN_H
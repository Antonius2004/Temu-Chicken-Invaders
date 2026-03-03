//
// Created by patur on 12/12/2025.
//
#include "Draisine.h"

namespace m1 {
    void Draisine::Accelerate(float deltaTimeSeconds) {
        float acceleration = 0.2f;
        this->speed_ += acceleration * deltaTimeSeconds;
    }

    void Draisine::Deccelerate(float deltaTimeSeconds) {
        float acceleration = 0.2f;
        this->speed_ -= acceleration * deltaTimeSeconds;
    }

    void Draisine::UpdatePosition() {
        glm::vec3 dist = glm::vec3(0);

        switch (this->heading_) {
        case Headings::N:
            dist = glm::vec3(this->speed_, 0, 0);
            break;
        case Headings::S:
            dist = glm::vec3(-this->speed_, 0, 0);
            break;
        case Headings::E:
            dist = glm::vec3(0, 0, this->speed_);
            break;
        case Headings::V:
            dist = glm::vec3(0, 0, -this->speed_);
            break;
        }

        this->position_ += dist;
        this->corner_ += dist;
        this->handle_position_ += dist;
    }

    void Draisine::SetPosition(glm::vec3 new_position) {
        this->position_ = new_position;
        this->corner_ = this->position() + glm::vec3(-base_width / 2.f, 0, -base_length / 2.f);
        this->handle_position_ = this->position_ + glm::vec3(0, 2, 0);
    }

    AABB Draisine::get_hitbox() const {
        AABB box;

        float x_size, z_size;
        if (heading_ == Headings::N || heading_ == Headings::S) {
            x_size = base_length + hitbox_padding_;
            z_size = base_width + hitbox_padding_;
        } else {
            x_size = base_width + hitbox_padding_;
            z_size = base_length + hitbox_padding_;
        }

        box.min = position_ - glm::vec3(x_size / 2.f, 0, z_size / 2.f);
        box.max = position_ + glm::vec3(x_size / 2.f, base_height, z_size / 2.f);

        return box;
    }

    bool Draisine::contains_point(const glm::vec3& p) const {
        AABB box = get_hitbox();

        return (p.x >= box.min.x && p.x <= box.max.x &&
            p.z >= box.min.z && p.z <= box.max.z);
    }
}

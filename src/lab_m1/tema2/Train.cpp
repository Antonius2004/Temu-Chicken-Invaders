//
// Created by patur on 12/10/2025.
//

#include "Train.h"

#include <utility>

namespace m1 {
    void Train::add_progress(float x) {
        this->progress_ += x;

        if (in_turn_ && !turned_mid_block_ && this->progress_ >= SIZE_SEGMENT / 2.0f) {
            if (current_turn_orientation_ == TurnOrientation::NE) {
                if (this->heading_ == Headings::S) { this->heading_ = Headings::E; }
                else if (this->heading_ == Headings::V) { this->heading_ = Headings::N; }
            }
            else if (current_turn_orientation_ == TurnOrientation::NV) {
                if (this->heading_ == Headings::E) { this->heading_ = Headings::N; }
                else if (this->heading_ == Headings::S) { this->heading_ = Headings::V; }
            }
            else if (current_turn_orientation_ == TurnOrientation::SE) {
                if (this->heading_ == Headings::N) { this->heading_ = Headings::E; }
                else if (this->heading_ == Headings::V) { this->heading_ = Headings::S; }
            }
            else if (current_turn_orientation_ == TurnOrientation::SV) {
                if (this->heading_ == Headings::E) { this->heading_ = Headings::S; }
                else if (this->heading_ == Headings::N) { this->heading_ = Headings::V; }
            }

            turned_mid_block_ = true;
        }

        switch (this->heading_) {
        case Headings::N:
            this->position_.x += x;
            this->corner_.x += x;
            break;
        case Headings::S:
            this->position_.x -= x;
            this->corner_.x -= x;
            break;
        case Headings::E:
            this->position_.z += x;
            this->corner_.z += x;
            break;
        case Headings::V:
            this->position_.z -= x;
            this->corner_.z -= x;
            break;
        }
    }

    void Train::ChangeRail(StraightRail straight_rail, Block* new_block) {
        this->rail_ = static_cast<Rail>(std::move(straight_rail));
        this->current_block_ = new_block;
        this->progress_ = 0;
        this->in_turn_ = false;
        this->turned_mid_block_ = false;
        this->position_ = straight_rail.GetClosestPosition(this->position());
    }

    void Train::ChangeRail(TurnRail turn_rail, Block* new_block) {
        this->rail_ = static_cast<Rail>(std::move(turn_rail));
        this->current_block_ = new_block;
        this->progress_ = 0;

        in_turn_ = true;
        turned_mid_block_ = false;
        current_turn_orientation_ = turn_rail.get_orientation();
    }

    AABB Train::get_hitbox() const {
        AABB box;

        float x_size, z_size;
        if (heading_ == Headings::N || heading_ == Headings::S) {
            x_size = base_length;
            z_size = base_width;
        } else {
            x_size = base_width;
            z_size = base_length;
        }

        box.min = position_ - glm::vec3(x_size / 2.f, 0, z_size / 2.f);
        box.max = position_ + glm::vec3(x_size / 2.f, base_height, z_size / 2.f);

        return box;
    }

    bool Train::contains_point(const glm::vec3& p) const {
        AABB box = get_hitbox();

        return (p.x >= box.min.x && p.x <= box.max.x &&
            p.z >= box.min.z && p.z <= box.max.z);
    }
} // m1

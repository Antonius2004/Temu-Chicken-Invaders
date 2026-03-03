//
// Created by patur on 12/10/2025.
//

#ifndef GFXFRAMEWORK_TRAIN_H
#define GFXFRAMEWORK_TRAIN_H

#include "Block.h"
#include "Constants.h"
#include "Rail.h"

namespace m1 {
    struct AABB {
        glm::vec3 min;
        glm::vec3 max;
    };

    class Train {
    public:
        Train() = default;

        Train(Rail rail, glm::vec3 position, Block *current_block) {
            this->rail_ = rail;
            this->progress_ = 0.f;
            this->speed_ = TRAIN_SPEED;
            glm::vec3 offset = glm::vec3(SIZE_SEGMENT / 2.f, 0, 0);
            this->position_ = position + offset;
            this->heading_ = Headings::E;
            this->current_block_ = current_block;

            this->corner_ = current_block->get_position() + glm::vec3(SIZE_SEGMENT / 4.f, 0, SIZE_SEGMENT / 2.f);
        }

        Rail rail() const { return rail_; }
        void set_rail(Rail rail) { rail_ = rail; }
        float progress() const { return progress_; }
        void set_progress(float progress) { progress_ = progress; }
        float speed() const { return speed_; }
        void set_speed(float speed) { speed_ = speed; }
        glm::vec3 position() const { return position_; }
        void set_position(const glm::vec3& position) { position_ = position; }
        void add_progress(float x);
        Headings get_heading() const { return heading_; }
        void set_heading(Headings heading) { heading_ = heading; }
        Block* get_current_block() { return current_block_; }
        void set_current_block(Block *current_block) { current_block_ = current_block; }

        void ChangeRail(StraightRail straight_rail, Block *new_block);
        void ChangeRail(TurnRail turn_rail, Block *new_block);

        AABB get_hitbox() const;
        bool contains_point(const glm::vec3& p) const;



    protected:
        Rail rail_;
        float progress_;
        float speed_;
        glm::vec3 position_;
        Headings heading_;
        Block *current_block_;

        glm::vec3 corner_;
        float base_length = SIZE_SEGMENT;
        float base_width = SIZE_SEGMENT / 2.f;
        float base_height = SIZE_SEGMENT / 20.f;


        bool in_turn_ = false;
        bool turned_mid_block_ = false;
        TurnOrientation current_turn_orientation_;



    };
} // m1

#endif //GFXFRAMEWORK_TRAIN_H
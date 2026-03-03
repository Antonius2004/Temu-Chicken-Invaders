//
// Created by patur on 12/8/2025.
//

#pragma once

#include "Rail.h"
#include "Constants.h"

namespace m1
{
    class StraightRail : public Rail {
    public:
        StraightRail(TerrainType ground, const std::string &mesh_name, StraightOrientation orientation, glm::vec3 block_pos) {
            this->orientation_ = orientation;
            this->type_ = Type::Straight;
            this->ground_ = ground;
            this->mesh_name_ = mesh_name;

            // Calc end and start pos based on block
            switch (orientation) {
            case StraightOrientation::NS:
                this->pos1_ = block_pos + glm::vec3(0, 0, SIZE_SEGMENT / 2.f);
                this->pos2_ = block_pos + glm::vec3(SIZE_SEGMENT, 0, SIZE_SEGMENT/ 2.f);
                break;

            case StraightOrientation::VE:
                this->pos1_ = block_pos + glm::vec3(SIZE_SEGMENT / 2.f, 0, 0);
                this->pos2_ = block_pos + glm::vec3(SIZE_SEGMENT / 2.f, 0, SIZE_SEGMENT);
                break;
            }
        }

        StraightOrientation get_orientation() {
            return this->orientation_;
        }

        glm::mat4 ComputeModelMatrix();

    private:
        StraightOrientation orientation_;
    };
}

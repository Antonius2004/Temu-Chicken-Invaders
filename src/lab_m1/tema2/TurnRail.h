//
// Created by patur on 12/8/2025.
//

#pragma once

#include "Rail.h"
#include "Constants.h"

namespace m1
{
    class TurnRail : public Rail {
    public:
        TurnRail(const std::string &mesh_name, TurnOrientation orientation, glm::vec3 block_pos) {
            this->orientation_ = orientation;
            this->type_ = Type::Turn;
            this->ground_ = TerrainType::None;
            this->mesh_name_ = mesh_name;

            // Calc end and start pos based on block
            switch (orientation) {
            case TurnOrientation::NE:
                this->pos1_ = block_pos + glm::vec3(SIZE_SEGMENT, 0, SIZE_SEGMENT / 2.f);
                this->pos2_ = block_pos + glm::vec3(SIZE_SEGMENT / 2.f, 0, SIZE_SEGMENT);
                break;

            case TurnOrientation::NV:
                this->pos1_ = block_pos + glm::vec3(SIZE_SEGMENT, 0, SIZE_SEGMENT / 2.f);
                this->pos2_ = block_pos + glm::vec3(SIZE_SEGMENT / 2.f, 0, 0);
                break;

            case TurnOrientation::SE:
                this->pos1_ = block_pos + glm::vec3(0, 0, SIZE_SEGMENT / 2.f);
                this->pos2_ = block_pos + glm::vec3(SIZE_SEGMENT / 2.f, 0, SIZE_SEGMENT);
                break;

            case TurnOrientation::SV:
                this->pos1_ = block_pos + glm::vec3(0, 0, SIZE_SEGMENT / 2.f);
                this->pos2_ = block_pos + glm::vec3(SIZE_SEGMENT / 2.f, 0, 0);
                break;
            }
        }

        TurnOrientation get_orientation() {
            return this->orientation_;
        }

    private:
        TurnOrientation orientation_;
    };
} // m1



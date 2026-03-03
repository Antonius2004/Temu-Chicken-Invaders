//
// Created by patur on 12/8/2025.
//

#include "Block.h"

namespace m1 {
    void Block::UpdateRail(const StraightRail &rail) {
        this->straight_rails_.push_back(rail);
        this->has_rail_ = true;
    }

    void Block::UpdateRail(const TurnRail &rail) {
        this->turn_rails_.push_back(rail);
        this->has_rail_ = true;
    }

    glm::mat4 Block::ComputeModelMatrix(StraightRail srail) {
        glm::mat4 model(1.0f);

        float angle = 0.f;
        switch (srail.get_orientation()) {
        case StraightOrientation::NS:
            angle = glm::radians(90.f);
            break;
        case StraightOrientation::VE:
            angle = 0.f;
            break;
        }

        glm::vec3 centerOffset(SIZE_SEGMENT / 2.f, 0.f, SIZE_SEGMENT / 2.f);

        model = glm::translate(model, position_);
        model = glm::translate(model, centerOffset);
        model = glm::rotate(model, angle, glm::vec3(0, 1, 0));
        model = glm::translate(model, -centerOffset);

        return model;
    }


    glm::mat4 Block::ComputeModelMatrix(TurnRail trail)
    {
        glm::mat4 modelMatrix(1.0f);

        float rotation_angle = 0.f;
        switch (trail.get_orientation()) {
        case TurnOrientation::SE:
            rotation_angle = glm::radians(0.f);
            break;
        case TurnOrientation::NE:
            rotation_angle = glm::radians(90.f);
            break;
        case TurnOrientation::NV:
            rotation_angle = glm::radians(180.f);
            break;
        case TurnOrientation::SV:
            rotation_angle = glm::radians(270.f);
            break;
        }

        glm::vec3 centerOffset(SIZE_SEGMENT / 2.f, 0.f, SIZE_SEGMENT / 2.f);

        modelMatrix = glm::translate(modelMatrix, position_);
        modelMatrix = glm::translate(modelMatrix, centerOffset);
        modelMatrix = glm::rotate(modelMatrix, rotation_angle, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, -centerOffset);

        return modelMatrix;
    }

    void Block::set_cracked(bool cracked) {
        this->cracked_ = cracked;

        // set for all rails
        for (auto & rail : straight_rails_) {
            rail.set_cracked(cracked);
        }

        for (auto & rail : turn_rails_) {
            rail.set_cracked(cracked);
        }
    }





} // m1
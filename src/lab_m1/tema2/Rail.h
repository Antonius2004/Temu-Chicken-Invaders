//
// Created by patur on 12/8/2025.
//

#pragma once

#include "utils/glm_utils.h"
#include "Enums.h"

namespace m1 {
    class Rail {
    public:
        Rail() = default;

        glm::vec3 pos1() const { return pos1_; }
        void set_pos1(const glm::vec3& pos1) { pos1_ = pos1; }
        glm::vec3 pos2() const { return pos2_; }
        void set_pos2(const glm::vec3& pos2) { pos2_ = pos2; }
        Type type() const { return type_; }
        void set_type(Type type) { type_ = type; }
        TerrainType ground() const { return ground_; }
        void set_ground(TerrainType ground) { ground_ = ground; }
        const std::string& mesh_name() { return mesh_name_; }
        void set_mesh_name(const std::string& mesh_name) { mesh_name_ = mesh_name; }
        bool get_cracked() const { return cracked; }
        void set_cracked(bool cracked) { this->cracked = cracked; }

        glm::vec3 GetClosestPosition(glm::vec3 position) const;

    protected:
        glm::vec3 pos1_, pos2_;
        Type type_;
        TerrainType ground_;
        std::string mesh_name_;
        bool cracked = false;
    };
} // m1
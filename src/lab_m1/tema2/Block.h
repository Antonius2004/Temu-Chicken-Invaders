//
// Created by patur on 12/8/2025.
//

#pragma once

#include <vector>

#include "utils/glm_utils.h"
#include "Station.h"
#include "StraightRail.h"
#include "TurnRail.h"

namespace m1 {
    class Block {
    public:
        Block() = default;

        // Constructor with no track
        Block (glm::vec3 position, TerrainType terrain_type, bool has_rail = false, bool has_station = false,
            int i = -1, int j = -1) {

            this->position_ = position;
            this->terrain_type_ = terrain_type;
            this->has_rail_ = has_rail;
            this->has_station_ = has_station;
            this->position_in_matrix_ = glm::vec2(i, j);
            this->cracked_ = 0;


            switch (terrain_type) {
                case TerrainType::Grass: {
                    this->mesh_name_ = "grass";
                    break;
                }
                case TerrainType::Mountain: {
                    this->mesh_name_ = "mountain";
                    break;
                }
                case TerrainType::Water: {
                    this->mesh_name_ = "water";
                    break;
                }
                case TerrainType::None: {
                    this->mesh_name_ = "none";
                    break;
                }
            }
        }

        glm::vec3 get_position() const {
            return position_;
        }

        void set_position(const glm::vec3 &position) {
            position_ = position;
        }

        TerrainType get_terrain_type() const {
            return terrain_type_;
        }

        void set_terrain_type(TerrainType terrain_type) {
            terrain_type_ = terrain_type;
        }

        std::string get_mesh_name() const {
            return mesh_name_;
        }

        void set_mesh_name(const std::string &mesh_name) {
            mesh_name_ = mesh_name;
        }

        bool is_has_track() const {
            return has_rail_;
        }

        void set_has_track(bool has_track) {
            has_rail_ = has_track;
        }

        bool is_has_station() const {
            return has_station_;
        }

        void set_has_station(bool has_station) {
            has_station_ = has_station;
        }

        Station get_station() const {
            return station_;
        }

        void set_station(const Station &station) {
            station_ = station;
        }

        std::vector<TurnRail>& turn_rails()
        {
            return turn_rails_;
        }

        void set_turn_rails(const std::vector<TurnRail>& turn_rails)
        {
            turn_rails_ = turn_rails;
        }

        std::vector<TurnRail>& get_turn_rails() {
            return turn_rails_;
        }

        std::vector<StraightRail>& straight_rails()
        {
            return straight_rails_;
        }

        void set_straight_rails(const std::vector<StraightRail>& straight_rails)
        {
            straight_rails_ = straight_rails;
        }

        std::vector<StraightRail>& get_straight_rails() {
            return straight_rails_;
        }

        glm::vec2 get_position_in_matrix() const {
            return position_in_matrix_;
        }

        int get_cracked() const { return cracked_; }
        void set_cracked(bool cracked);

        void UpdateRail(const StraightRail &rail);
        void UpdateRail(const TurnRail &rail);
        glm::mat4 ComputeModelMatrix(StraightRail srail);
        glm::mat4 ComputeModelMatrix(TurnRail trail);

        Block *neigh_N = nullptr;
        Block *neigh_S = nullptr;
        Block *neigh_E = nullptr;
        Block *neigh_V = nullptr;
        bool cracked_;

    private:
        glm::vec2 position_in_matrix_;
        glm::vec3 position_;
        TerrainType terrain_type_;
        std::string mesh_name_;
        bool has_rail_;
        bool has_station_;
        std::vector<TurnRail> turn_rails_;
        std::vector<StraightRail> straight_rails_;
        Station station_;

    };
} // m1

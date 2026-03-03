//
// Created by patur on 11/7/2025.
//

#include "PlayerShip.h"

namespace m1 {
    void PlayerShip::addBlock(const EditBlockData &block) {
        this->blocks.push_back(block);
    }

    void PlayerShip::MoveLeft(float deltaTime) {
        for (auto &eb : blocks) {
            glm::vec3 newCorner = eb.corner1() - glm::vec3(deltaTime * SHIP_MOVE_FACTOR, 0, 0) * this->speed;
            eb.set_corner(newCorner);
        }
        hitboxCorner -= glm::vec3(deltaTime * SHIP_MOVE_FACTOR, 0, 0) * this->speed;
    }

    void PlayerShip::MoveRight(float deltaTime) {
        for (auto &eb : blocks) {
            glm::vec3 newCorner = eb.corner1() + glm::vec3(deltaTime * SHIP_MOVE_FACTOR, 0, 0) * this->speed;
            eb.set_corner(newCorner);
        }
        hitboxCorner += glm::vec3(deltaTime * SHIP_MOVE_FACTOR, 0, 0) * this->speed;
    }

    void PlayerShip::MoveDown(float deltaTime) {
        for (auto &eb : blocks) {
            glm::vec3 newCorner = eb.corner1() - glm::vec3(0, deltaTime * SHIP_MOVE_FACTOR, 0) * this->speed;
            eb.set_corner(newCorner);
        }
        hitboxCorner -= glm::vec3(0, deltaTime * SHIP_MOVE_FACTOR, 0) * this->speed;
    }

    void PlayerShip::MoveUp(float deltaTime) {
        for (auto &eb : blocks) {
            glm::vec3 newCorner = eb.corner1() + glm::vec3(0, deltaTime * SHIP_MOVE_FACTOR, 0) * this->speed;
            eb.set_corner(newCorner);
        }
        hitboxCorner += glm::vec3(0, deltaTime * SHIP_MOVE_FACTOR, 0) * this->speed;
    }

    void PlayerShip::ComputeSpeed() {
        float thrusters = 0;
        int cannons = 0;
        int buildingTiles = 0;
        for (auto &eb : blocks) {
            if (eb.mesh_name() == "thruster") {
                thrusters++;
            } else if (eb.mesh_name() == "cannon") {
                cannons++;
            } else if (eb.mesh_name() == "buildingTile") {
                buildingTiles++;
            }
        }
        this->speed = thrusters * 0.7f;
        this->cannons = cannons;
        this->tiles = buildingTiles;
    }






} // m1
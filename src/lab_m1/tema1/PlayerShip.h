//
// Created by patur on 11/7/2025.
//

#ifndef GFXFRAMEWORK_PLAYERSHIP_H
#define GFXFRAMEWORK_PLAYERSHIP_H

#include <vector>
#include "EditBlockData.h"
#include "utils/glm_utils.h"

namespace m1 {
    class PlayerShip {
        // Mostly stores blocks of ship and other information
        public:
            PlayerShip()= default;

            void addBlock(const EditBlockData &block);

            // Getters and setters
            void setSize(const glm::vec2 size1) {
                this->size = size1;
            }

            void setCenter(const glm::vec2 center1) {
                this->center = center1;
            }

            glm::vec2 getCenter() const {
                return this->center;
            }

            void setMove(glm::vec2 move1) {
                this->move = move1;
            }

            glm::vec2 getMove() {
                return this->move;
            }

            std::vector<EditBlockData>& getBlocks() {
                return this->blocks;
            }

            void setHitboxCorner(glm::vec3 hb) {
                this->hitboxCorner = hb;
            }

            glm::vec3 getHitboxCorner() {
                return this->hitboxCorner;
            }

            void setHitboxSize(glm::vec2 hitboxSize1) {
                this->hitboxSize = hitboxSize1;
            }

            glm::vec2 getHitboxSize() {
                return this->hitboxSize;
            }

             glm::vec2 getSize() {
                return this->size;
            }

            void setSpeed(int speed1) {
                this->speed = speed1;
            }

            float getSpeed() {
                return this->speed;
            }

            int getCannons() {
                return this->cannons;
            }

            int getTiles() {
                return this->tiles;
            }

            void MoveLeft(float deltaTime);
            void MoveRight(float deltaTime);
            void MoveUp(float deltaTime);
            void MoveDown(float deltaTime);
            void ComputeSpeed();

        private:
            std::vector<EditBlockData> blocks;
            glm::vec2 size{};
            glm::vec2 center{};
            glm::vec3 hitboxCorner{};
            glm::vec2 hitboxSize{};

            glm::vec2 move{0.f, 0.f};
            float scale = 1.f;
            float speed = 0;
            int cannons = 0;
            int tiles = 0;
    };
}

#endif //GFXFRAMEWORK_PLAYERSHIP_H
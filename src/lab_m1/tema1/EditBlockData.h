//
// Created by patur on 11/6/2025.
//

#ifndef GFXFRAMEWORK_EDITBLOCKDATA_H
#define GFXFRAMEWORK_EDITBLOCKDATA_H

#include <string>
#include <vector>
#include "constants.h"
#include "utils/glm_utils.h"
#include "InteractableMesh.h"

namespace m1 {
    class EditBlockData {
        public:
            EditBlockData(glm::vec3 corner, float i, float j) {
                this->corner = corner;
                this->side = EDIT_BLOCK_LEN;
                this->taken = false;
                this->obstructed = false;
                this->posInMatrix.x = i;
                this->posInMatrix.y = j;
            }

            glm::vec3 corner1() const {
                return corner;
            }

            void set_corner(const glm::vec3 &corner) {
                this->corner = corner;
            }

            int side1() const {
                return side;
            }

            void set_side(int side) {
                this->side = side;
            }

            bool taken1() const {
                return taken;
            }

            void set_taken(bool taken) {
                this->taken = taken;
            }

            std::string mesh_name() const {
                return meshName;
            }

            void set_mesh_name(const std::string &mesh_name) {
                meshName = mesh_name;
            }

            glm::vec2 getPos() {
                return this->posInMatrix;
            }

            bool isObstructed() {
                return this->obstructed;
            }

            void setObstructed(bool o) {
                this->obstructed = o;
            }

            void setActualCorner(glm::vec3 actualCorner1) {
                this->actualCorner = actualCorner1;
            }

            glm::vec3 getActualCorner() {
                return this->actualCorner;
            }

            glm::mat3 model_matrix() const {
                return modelMatrix;
            }

            void set_model_matrix(const glm::mat3 &model_matrix) {
                modelMatrix = model_matrix;
            }

            bool isInside(int mouseX, int mouseY);
            bool canPlace(InteractableMesh im, std::vector<std::vector<EditBlockData>> mat);

            const glm::vec3 center = glm::vec3(EDIT_BLOCK_LEN, EDIT_BLOCK_LEN, 0) / 2.f;


        private:
            glm::vec2 posInMatrix;
            glm::vec3 corner;
            int side;
            bool taken;
            std::string meshName;
            bool obstructed;
            glm::mat3 modelMatrix;

            // Not used
            glm::vec3 actualCorner;

    };
} // m1

#endif //GFXFRAMEWORK_EDITBLOCKDATA_H
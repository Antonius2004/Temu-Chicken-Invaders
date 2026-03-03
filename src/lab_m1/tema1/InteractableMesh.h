//
// Created by patur on 11/6/2025.
//

#ifndef GFXFRAMEWORK_INTERACTABLEMESH_H
#define GFXFRAMEWORK_INTERACTABLEMESH_H

#include <string>
#include "constants.h"
#include "utils/glm_utils.h"

namespace m1 {
    class InteractableMesh {
        // Stores a mesh that can be interacted with in the editor using the mouse
        public:
            InteractableMesh(const std::string &name, const glm::vec3 &corner, float width, float height) {
                this->name = name;
                this->corner = corner;
                this->width = width;
                this->height = height;
                this->isClicked = false;
                modelMatrix = glm::mat3(1);
                this->center = corner + glm::vec3(EDIT_BLOCK_LEN / 2.f, EDIT_BLOCK_LEN / 2.f, 0);

            }

            bool is_clicked() const {
                return isClicked;
            }

            void set_is_clicked(bool is_clicked) {
                isClicked = is_clicked;
            }

            glm::vec3 getCenter() {
                return this->center;
            }

            std::string getName() {
                return this->name;
            }

            void setClickOffs(glm::vec2 co) {
                this->clickOffs = co;
            }

            glm::vec2 getClickOffs() {
                return this->clickOffs;
            }

            glm::vec3 getCorner() {
                return this->corner;
            }

            void setModelMatrix(glm::mat3 mm) {
                this->modelMatrix = mm;
            }

            glm::mat3 getModelMatrix() {
                return this->modelMatrix;
            }

            glm::vec2 getDimensions() {
                return glm::vec2(this->width, this->height);
            }

            bool isInside(int mouseX, int mouseY);

        private:
            std::string name;
            glm::vec3 corner;
            glm::vec3 center;
            float width;
            float height;
            bool isClicked;
            glm::vec2 clickOffs;
            glm::mat3 modelMatrix;
        };
}


#endif //GFXFRAMEWORK_INTERACTABLEMESH_H
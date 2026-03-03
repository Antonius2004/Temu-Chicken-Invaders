#pragma once

#include <string>
#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace objects2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

    // Create rectangle with given bottom left corner, length, width and color
    Mesh *CreateRectangle(const std::string &name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill = false);

    // Create start button
    Mesh *CreateStartButton(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = true);

    // Create building tile
    Mesh *CreateTile(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = true);

    // Create thruster
    Mesh *CreateThruster(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);

    // Create cannon
    Mesh *CreateCannon(const std::string &name, glm::vec3 leftBottomCorner);

    // Create chicken
    Mesh *CreateChicken(const std::string &name, glm::vec3 leftBottomCorner);

    // Create cannon proj
    Mesh *CreateCannonProjectile(const std::string &name, glm::vec3 leftBottomCorner);

    // Create chicken projectile
    Mesh *CreateChickenProjectile(const std::string &name, glm::vec3 leftBottomCorner);

    // Create life indicator tile
    Mesh *CreateLife(const std::string &name, glm::vec3 leftBottomCorner, glm::vec3 color);
}

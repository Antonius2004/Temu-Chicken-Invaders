//
// Created by patur on 12/8/2025.
//

#ifndef GFXFRAMEWORK_OBJECTS_H
#define GFXFRAMEWORK_OBJECTS_H

#include <string>
#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

namespace Objects {
    // Create default size square for building ground
    Mesh *CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, glm::vec3 color);

    Mesh *CreateGrassRail(const std::string &name, glm::vec3 leftBottomCorner);

    Mesh *CreateMountainRail(const std::string &name, glm::vec3 leftBottomCorner);

    Mesh *CreateWaterRail(const std::string &name, glm::vec3 leftBottomCorner);

    Mesh *CreateTurnRail(const std::string &name, glm::vec3 leftBottomCorner);

    Mesh *CreateTrain();

    Mesh *CreateWagon();

    Mesh *CreateDraisineBody();

    Mesh *CreateDraisinHandle();

    Mesh *CreateCube();

    Mesh *CreatePyramid();

    Mesh *CreateSpehere();

} // Objects

#endif //GFXFRAMEWORK_OBJECTS_H
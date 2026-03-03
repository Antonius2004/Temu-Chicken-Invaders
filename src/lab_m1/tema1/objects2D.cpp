#include "objects2D.h"
#include "constants.h"

namespace objects2D {
    Mesh* CreateSquare(
        const std::string &name,
        glm::vec3 leftBottomCorner,
        float length,
        glm::vec3 color,
        bool fill)
    {
        glm::vec3 corner = leftBottomCorner;

        std::vector<VertexFormat> vertices =
        {
            VertexFormat(corner, color),
            VertexFormat(corner + glm::vec3(length, 0, 0), color),
            VertexFormat(corner + glm::vec3(length, length, 0), color),
            VertexFormat(corner + glm::vec3(0, length, 0), color)
        };

        Mesh* square = new Mesh(name);
        std::vector<unsigned int> indices = { 0, 1, 2, 3 };

        if (!fill) {
            square->SetDrawMode(GL_LINE_LOOP);
        } else {
            // Draw 2 triangles. Add the remaining 2 indices
            indices.push_back(0);
            indices.push_back(2);
        }

        square->InitFromData(vertices, indices);
        return square;
    }

    Mesh *CreateRectangle(const std::string &name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill) {
        glm::vec3 corner = leftBottomCorner;

        std::vector<VertexFormat> vertices = {
            VertexFormat(corner, color),
            VertexFormat(corner + glm::vec3(width, 0, 0), color),
            VertexFormat(corner + glm::vec3(width, height, 0), color),
            VertexFormat(corner + glm::vec3(0, height, 0), color)
        };

        std::vector<unsigned int> indices = {
            0, 1, 2, 3
        };

        Mesh *rectangle = new Mesh(name);

        if (!fill) {
            rectangle->SetDrawMode(GL_LINE_LOOP);
        } else {
            rectangle->SetDrawMode(GL_TRIANGLES);
        }

        rectangle->InitFromData(vertices, indices);
        return rectangle;
    }

    Mesh *CreateStartButton(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill) {
        glm::vec3 corner = leftBottomCorner;

        std::vector<VertexFormat> vertices =
        {
            VertexFormat(corner, color),
            VertexFormat(corner + glm::vec3(length, 0, 0), color),
            VertexFormat(corner + glm::vec3(length / 2, length / 2, 0), color),
            VertexFormat(corner + glm::vec3(length, length, 0), color),
            VertexFormat(corner + glm::vec3(0, length, 0), color)
        };

        std::vector<unsigned int> indices = {
            0, 1, 2,
            2, 3, 4,
            0, 2, 4
        };

        Mesh* square = new Mesh(name);

        if (!fill) {
            square->SetDrawMode(GL_LINE_LOOP);
        } else {
            square->SetDrawMode(GL_TRIANGLES);
        }

        square->InitFromData(vertices, indices);
        return square;
    }

    Mesh *CreateTile(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill) {
        glm::vec3 corner = leftBottomCorner;
        glm::vec3 center = corner + glm::vec3(length / 2.f, length / 2.f, 0);

        std::vector<VertexFormat> vertices = {
            VertexFormat(corner, color),
            VertexFormat(corner + glm::vec3(length, 0, 0), color),
            VertexFormat(corner + glm::vec3(length, length, 0), color),
            VertexFormat(corner + glm::vec3(0, length, 0), color),
            VertexFormat(center, color + 0.2f)
        };

        std::vector<unsigned int> indices = {
            0, 1, 4,
            1, 2, 4,
            2, 3, 4,
            3, 0, 4
        };

        Mesh *tile = new Mesh(name);

        if (!fill) {
            tile->SetDrawMode(GL_LINE_LOOP);
        } else {
            tile->SetDrawMode(GL_TRIANGLES);
        }

        tile->InitFromData(vertices, indices);
        return tile;
    }

    Mesh *CreateThruster(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill) {
        glm::vec3 corner = leftBottomCorner;

        float fireOff = FIRE_OFF;
        glm::vec3 fireTopLeftCorner = corner + glm::vec3(fireOff, 0, 0);
        float fireLen = FIRE_LEN;
        glm::vec3 fireColor = glm::vec3(255, 111, 0) / 255.f;

        glm::vec3 thrustGradient = glm::vec3(128, 128,128) / 255.f;

        std::vector<VertexFormat> vertices = {
            // Tile vertices
            VertexFormat(corner, color),
            VertexFormat(corner + glm::vec3(length, 0, 0), color),
            VertexFormat(corner + glm::vec3(length, length, 0), thrustGradient),
            VertexFormat(corner + glm::vec3(0, length, 0), thrustGradient),

            // Triangle vertices for the fire
            VertexFormat(fireTopLeftCorner, fireColor),
            VertexFormat(fireTopLeftCorner + glm::vec3(0, -fireLen, 0), fireColor),
            VertexFormat(fireTopLeftCorner + glm::vec3(fireLen, 0, 0), fireColor),
            VertexFormat(fireTopLeftCorner + glm::vec3(20, -fireLen, 0), fireColor),
            VertexFormat(fireTopLeftCorner + glm::vec3(45, -fireLen + 5, 0), fireColor),
            VertexFormat(fireTopLeftCorner + glm::vec3(fireLen, -fireLen, 0), fireColor),
            VertexFormat(fireTopLeftCorner + glm::vec3(fireLen - 40, 0, 0), fireColor)
        };

        std::vector<unsigned int> indices = {
            // Tile indices
            0, 1, 2,
            0, 2, 3,

            // Fire indices
            4, 5, 6,
            4, 7, 6,
            4, 8, 6,
            10, 9, 6
        };

        Mesh *tile = new Mesh(name);

        if (!fill) {
            tile->SetDrawMode(GL_LINE_LOOP);
        } else {
            tile->SetDrawMode(GL_TRIANGLES);
        }

        tile->InitFromData(vertices, indices);
        return tile;
    }

    Mesh *CreateCannon(const std::string &name, glm::vec3 leftBottomCorner) {
        glm::vec3 corner = leftBottomCorner;

        glm::vec3 circleCenter = corner + glm::vec3(EDIT_BLOCK_LEN / 2, EDIT_BLOCK_LEN / 2, 0);
        glm::vec3 circleColor = glm::vec3(255.f, 204.f, 0.f) / 255.f;

        std::vector<VertexFormat> vertices;
        std::vector<unsigned int> indices;

        int index = vertices.size();

        // Make the barrel in plane 0
        int cannonBlockOff = 5;
        int cannonBlockW = EDIT_BLOCK_LEN - 2 * cannonBlockOff;
        glm::vec3 cannonBlockColor = glm::vec3(54, 54, 54) / 255.f;
        glm::vec3 cannonLeftBottomCorner = leftBottomCorner + glm::vec3(cannonBlockOff, 0, 0);

        for (float i = 0; i < 4; i++) {
            vertices.emplace_back(cannonLeftBottomCorner + glm::vec3(0, EDIT_BLOCK_LEN, 0) * i,
                cannonBlockColor);
            vertices.emplace_back(cannonLeftBottomCorner + glm::vec3(0, EDIT_BLOCK_LEN, 0) * i +
                glm::vec3(cannonBlockW, 0, 0), cannonBlockColor);
        }

        for (int i = 0; i < 3; i++) {
            unsigned int bl = index + 2 * i;
            unsigned int br = index + 2 * i + 1;
            unsigned int tl = index + 2 * (i + 1);
            unsigned int tr = index + 2 * (i + 1) + 1;

            indices.push_back(bl);
            indices.push_back(br);
            indices.push_back(tr);

            indices.push_back(bl);
            indices.push_back(tr);
            indices.push_back(tl);
        }

        index = vertices.size();

        // Add gradient at the top in first plane
        float gradient = 0.2f;
        glm::vec3 leftTopCorner = leftBottomCorner + glm::vec3(0, 3 * EDIT_BLOCK_LEN, 1);

        vertices.emplace_back(leftTopCorner, cannonBlockColor + gradient);
        vertices.emplace_back(leftTopCorner + glm::vec3(cannonBlockOff, 0, 0), cannonBlockColor + gradient);
        vertices.emplace_back(leftTopCorner + glm::vec3(cannonBlockOff, -EDIT_BLOCK_LEN / 4.f, 0), cannonBlockColor);

        vertices.emplace_back(leftTopCorner + glm::vec3(EDIT_BLOCK_LEN, 0, 0), cannonBlockColor + gradient);
        vertices.emplace_back(leftTopCorner + glm::vec3(EDIT_BLOCK_LEN - cannonBlockOff, 0, 0), cannonBlockColor + gradient);
        vertices.emplace_back(leftTopCorner + glm::vec3(EDIT_BLOCK_LEN - cannonBlockOff, -EDIT_BLOCK_LEN / 4.f, 0), cannonBlockColor);


        indices.push_back(index);
        indices.push_back(index + 1);
        indices.push_back(index + 2);

        indices.push_back(index + 1);
        indices.push_back(index + 2);
        indices.push_back(index + 4);

        indices.push_back(index + 4);
        indices.push_back(index + 2);
        indices.push_back(index + 5);

        indices.push_back(index + 3);
        indices.push_back(index + 4);
        indices.push_back(index + 5);

        index = vertices.size();

        // Make circle on first block in plane 1
        vertices.emplace_back(circleCenter, circleColor);

        int segments = 20;
        float startAngle = 0;
        float endAngle = 2 * M_PI;
        float radius = EDIT_BLOCK_LEN / 2;

        for (int i = 0; i <= segments; i++) {
            float angle = startAngle + i * (endAngle - startAngle) / segments;
            float x = circleCenter.x + radius * cos(angle);
            float y = circleCenter.y + radius * sin(angle);
            vertices.emplace_back(glm::vec3(x, y, 1), circleColor);
        }

        for (int i = 1; i <= segments; i++) {
            indices.push_back(index);
            indices.push_back(index + i);
            indices.push_back(index + i + 1);
        }

        index = static_cast<int>(vertices.size());

        // Make half a square that covers it on plane 2
        glm::vec3 squareColor = glm::vec3(107.f, 67.f, 0.f) / 255.f;
        vertices.emplace_back(leftBottomCorner + glm::vec3(0, 0, 2), squareColor);
        vertices.emplace_back(leftBottomCorner + glm::vec3(EDIT_BLOCK_LEN, 0, 2), squareColor);
        vertices.emplace_back(leftBottomCorner + glm::vec3(EDIT_BLOCK_LEN, EDIT_BLOCK_LEN / 2, 2), squareColor);
        vertices.emplace_back(leftBottomCorner + glm::vec3(0, EDIT_BLOCK_LEN / 2, 2), squareColor);

        indices.push_back(index);
        indices.push_back(index + 1);
        indices.push_back(index + 2);

        indices.push_back(index);
        indices.push_back(index + 2);
        indices.push_back(index + 3);

        Mesh* cannon = new Mesh(name);

        cannon->SetDrawMode(GL_TRIANGLES);

        cannon->InitFromData(vertices, indices);
        return cannon;

    }

    Mesh *CreateChicken(const std::string &name, glm::vec3 leftBottomCorner) {
        glm::vec3 corner = leftBottomCorner;

        // Mesh data
        std::vector<VertexFormat> vertices;
        std::vector<unsigned int> indices;
        int index = 0;

        // Colors
        glm::vec3 torsoColor{15 / 255.f, 135 / 255.f, 255 / 255.f};
        glm::vec3 legsAndBeakColor{255 / 255.f, 125 / 255.f, 27 / 255.f};
        glm::vec3 limbsColor{179 / 255.f, 179 / 255.f, 179 / 255.f};
        glm::vec3 hairColor{232 / 255.f, 16 / 255.f, 17 / 255.f};
        glm::vec3 eyesColor{0, 0, 0};

        // Torso
        vertices.emplace_back(corner, torsoColor);
        vertices.emplace_back(corner + glm::vec3(EDIT_BLOCK_LEN, 0, 0), torsoColor);
        vertices.emplace_back(corner + glm::vec3(EDIT_BLOCK_LEN, EDIT_BLOCK_LEN, 0), torsoColor);
        vertices.emplace_back(corner + glm::vec3(0, EDIT_BLOCK_LEN, 0), torsoColor);

        indices.push_back(index);
        indices.push_back(index + 1);
        indices.push_back(index + 2);

        indices.push_back(index);
        indices.push_back(index + 2);
        indices.push_back(index + 3);

        index = static_cast<int>(vertices.size());

        glm::vec3 rightWingOffs{10, 20, 0};

        // Left wing
        vertices.emplace_back(corner + rightWingOffs, limbsColor);
        vertices.emplace_back(corner + rightWingOffs + glm::vec3(-EDIT_BLOCK_LEN, 30, 0), limbsColor);
        vertices.emplace_back(corner + rightWingOffs + glm::vec3(-EDIT_BLOCK_LEN + 20, 90, 0), limbsColor);

        indices.push_back(index);
        indices.push_back(index + 1);
        indices.push_back(index + 2);

        index = static_cast<int>(vertices.size());

        glm::vec3 leftWingOffs{EDIT_BLOCK_LEN - 10, 30, 0};

        // Right wing
        vertices.emplace_back(corner + leftWingOffs, limbsColor);
        vertices.emplace_back(corner + leftWingOffs + glm::vec3(EDIT_BLOCK_LEN, 40, 0), limbsColor);
        vertices.emplace_back(corner + leftWingOffs + glm::vec3(EDIT_BLOCK_LEN - 30, 100, 0), limbsColor);

        indices.push_back(index);
        indices.push_back(index + 1);
        indices.push_back(index + 2);

        index = static_cast<int>(vertices.size());

        glm::vec3 leftLegOffs{EDIT_BLOCK_LEN / 5.f, 0, 0};

        // Left leg
        vertices.emplace_back(corner + leftLegOffs, legsAndBeakColor);
        vertices.emplace_back(corner  + leftLegOffs + glm::vec3(EDIT_BLOCK_LEN / 5.f, 0, 0), legsAndBeakColor);
        vertices.emplace_back(corner  + leftLegOffs + glm::vec3(EDIT_BLOCK_LEN / 5.f, -EDIT_BLOCK_LEN / 5.f, 0), legsAndBeakColor);
        vertices.emplace_back(corner  + leftLegOffs + glm::vec3(0, -EDIT_BLOCK_LEN / 5.f, 0), legsAndBeakColor);

        vertices.emplace_back(corner  + leftLegOffs + glm::vec3(-30, -EDIT_BLOCK_LEN / 5.f, 0), legsAndBeakColor);
        vertices.emplace_back(corner  + leftLegOffs + glm::vec3(-10, -EDIT_BLOCK_LEN / 5.f - 20, 0), legsAndBeakColor);

        indices.push_back(index);
        indices.push_back(index + 1);
        indices.push_back(index + 2);

        indices.push_back(index);
        indices.push_back(index + 2);
        indices.push_back(index + 3);

        indices.push_back(index + 2);
        indices.push_back(index + 4);
        indices.push_back(index + 5);

        index = static_cast<int>(vertices.size());

        glm::vec3 rightLegOffs{3 * EDIT_BLOCK_LEN / 5.f, 0, 0};

        // Right leg
        vertices.emplace_back(corner + rightLegOffs, legsAndBeakColor);
        vertices.emplace_back(corner  + rightLegOffs + glm::vec3(EDIT_BLOCK_LEN / 5.f, 0, 0), legsAndBeakColor);
        vertices.emplace_back(corner  + rightLegOffs + glm::vec3(EDIT_BLOCK_LEN / 5.f, -EDIT_BLOCK_LEN / 5.f, 0), legsAndBeakColor);
        vertices.emplace_back(corner  + rightLegOffs + glm::vec3(0, -EDIT_BLOCK_LEN / 5.f, 0), legsAndBeakColor);

        vertices.emplace_back(corner  + rightLegOffs + glm::vec3(30, -EDIT_BLOCK_LEN / 5.f, 0), legsAndBeakColor);
        vertices.emplace_back(corner  + rightLegOffs + glm::vec3(10, -EDIT_BLOCK_LEN / 5.f - 20, 0), legsAndBeakColor);

        indices.push_back(index);
        indices.push_back(index + 1);
        indices.push_back(index + 2);

        indices.push_back(index);
        indices.push_back(index + 2);
        indices.push_back(index + 3);

        indices.push_back(index + 3);
        indices.push_back(index + 4);
        indices.push_back(index + 5);

        index = static_cast<int>(vertices.size());

        // Head
        int segments = 60;
        float radius = EDIT_BLOCK_LEN / 2.f - 10;
        glm::vec3 headOffs{EDIT_BLOCK_LEN / 2.f, EDIT_BLOCK_LEN + radius, 0};

        vertices.emplace_back(corner + headOffs, limbsColor);

        for (int i = 0; i <= segments; i++) {
            float angle = 2 * M_PI * i / segments;
            float x = corner.x + headOffs.x + radius * cos(angle);
            float y = corner.y + headOffs.y + radius * sin(angle);
            vertices.emplace_back(glm::vec3(x, y, 0), limbsColor);
        }

        for (int i = 1; i <= segments; i++) {
            indices.push_back(index);
            indices.push_back(index + i);
            indices.push_back(index + i + 1);
        }

        index = static_cast<int>(vertices.size());

        // Left eye
        glm::vec3 leftEyeOffs{-15, 5, 0};
        glm::vec3 headCenter = corner + headOffs;

        radius = 4.f;
        vertices.emplace_back(headCenter + leftEyeOffs, eyesColor);

        for (int i = 0; i <= segments; i++) {
            float angle = 2 * M_PI * i / segments;
            float x = headCenter.x + leftEyeOffs.x + radius * cos(angle);
            float y = headCenter.y + leftEyeOffs.y + radius * sin(angle);
            vertices.emplace_back(glm::vec3(x, y, 0), eyesColor);
        }

        for (int i = 1; i <= segments; i++) {
            indices.push_back(index);
            indices.push_back(index + i);
            indices.push_back(index + i + 1);
        }

        index = static_cast<int>(vertices.size());

        // Right eye
        glm::vec3 rightEyeOffs{10, 9, 0};

        vertices.emplace_back(headCenter + rightEyeOffs, eyesColor);

        for (int i = 0; i <= segments; i++) {
            float angle = 2 * M_PI * i / segments;
            float x = headCenter.x + rightEyeOffs.x + radius * cos(angle);
            float y = headCenter.y + rightEyeOffs.y + radius * sin(angle);
            vertices.emplace_back(glm::vec3(x, y, 0), eyesColor);
        }

        for (int i = 1; i <= segments; i++) {
            indices.push_back(index);
            indices.push_back(index + i);
            indices.push_back(index + i + 1);
        }

        index = static_cast<int>(vertices.size());

        // Beak
        glm::vec3 beakOffs{0, 0, 0};

        vertices.emplace_back(headCenter + beakOffs, legsAndBeakColor);
        vertices.emplace_back(headCenter + beakOffs + glm::vec3(-5, -10, 0), legsAndBeakColor);
        vertices.emplace_back(headCenter + beakOffs + glm::vec3(13, -12, 0), legsAndBeakColor);

        indices.push_back(index);
        indices.push_back(index + 1);
        indices.push_back(index + 2);

        index = static_cast<int>(vertices.size());

        // Hair
        glm::vec3 hairOffs{-18, 23, 0};

        vertices.emplace_back(headCenter + hairOffs, hairColor);
        vertices.emplace_back(headCenter + hairOffs + glm::vec3(20, 0, 0), hairColor);
        vertices.emplace_back(headCenter + hairOffs + glm::vec3(15, 20, 0), hairColor);
        vertices.emplace_back(headCenter + hairOffs + glm::vec3(30, 0, 0), hairColor);
        vertices.emplace_back(headCenter + hairOffs + glm::vec3(35, 25, 0), hairColor);

        indices.push_back(index);
        indices.push_back(index + 1);
        indices.push_back(index + 2);

        indices.push_back(index);
        indices.push_back(index + 3);
        indices.push_back(index + 4);

        Mesh *chicken = new Mesh(name);
        chicken->SetDrawMode(GL_TRIANGLES);
        chicken->InitFromData(vertices, indices);
        return chicken;
    }

    Mesh *CreateCannonProjectile(const std::string &name, glm::vec3 leftBottomCorner) {
        glm::vec3 corner = leftBottomCorner;
        glm::vec3 center = leftBottomCorner + glm::vec3(CANNON_PROJ_RAD, CANNON_PROJ_RAD, 0);

        glm::vec3 color{170 / 255.f, 254 / 255.f, 113 / 255.f};

        // Mesh data
        std::vector<VertexFormat> vertices;
        std::vector<unsigned int> indices;

        int segments = 60;
        float radius = CANNON_PROJ_RAD;
        vertices.emplace_back(center, color);

        for (int i = 0; i <= segments; i++) {
            float angle = 2 * M_PI * i / segments;
            float x = center.x + radius * cos(angle);
            float y = center.y + radius * sin(angle);
            vertices.emplace_back(glm::vec3(x, y, 0), color);
        }

        for (int i = 1; i <= segments; i++) {
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back(i + 1);
        }

        Mesh *proj = new Mesh(name);
        proj->SetDrawMode(GL_TRIANGLES);
        proj->InitFromData(vertices, indices);
        return proj;

    }

    Mesh *CreateChickenProjectile(const std::string &name, glm::vec3 leftBottomCorner) {
        glm::vec3 center = leftBottomCorner + glm::vec3(CHICKEN_PROJ_RAD, CHICKEN_PROJ_RAD, 0);

        glm::vec3 color{208 / 255.f, 183 / 255.f, 160 / 255.f};

        std::vector<VertexFormat> vertices;
        std::vector<unsigned int> indices;

        int segments = 60;
        float radius = CHICKEN_PROJ_RAD;
        vertices.emplace_back(center, color);

        for (int i = 0; i <= segments; i++) {
            float angle = i * 2.0f * M_PI / segments;
            float x = center.x + radius * cos(angle);
            float y = center.y + radius * sin(angle);
            vertices.emplace_back(glm::vec3(x, y, center.z), color);

            if (i > 0) {
                indices.push_back(0);
                indices.push_back(i);
                indices.push_back(i + 1);
            }
        }

        Mesh *circle = new Mesh(name);
        circle->InitFromData(vertices, indices);
        return circle;
    }

    Mesh *CreateLife(const std::string &name, glm::vec3 leftBottomCorner, glm::vec3 color) {
        glm::vec3 corner = leftBottomCorner;

        std::vector<VertexFormat> vertices = {
            VertexFormat(corner, color),
            VertexFormat(corner + glm::vec3(LIFE_W, 0, 0), color),
            VertexFormat(corner + glm::vec3(LIFE_W, LIFE_H, 0), color),
            VertexFormat(corner + glm::vec3(2 * LIFE_W, LIFE_H, 0), color)
        };

        std::vector<unsigned int> indices = {
            0, 1, 2,
            1, 2, 3
        };

        Mesh *life = new Mesh(name);
        life->SetDrawMode(GL_TRIANGLES);
        life->InitFromData(vertices, indices);

        return life;
    }

}

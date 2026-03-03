//
// Created by patur on 12/8/2025.
//

#include <vector>
#include "Objects.h"
#include "Constants.h"

namespace Objects {
    Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, glm::vec3 color) {
        const glm::vec3 corner = leftBottomCorner;

        // Create vertexes
        std::vector<VertexFormat> vertices = {
            VertexFormat(corner, color),
            VertexFormat(corner + glm::vec3(SIZE_SEGMENT, 0, 0), color),
            VertexFormat(corner + glm::vec3(SIZE_SEGMENT, 0, SIZE_SEGMENT), color),
            VertexFormat(corner + glm::vec3(0, 0, SIZE_SEGMENT), color)
        };

        // Create indices
        std::vector<unsigned int> indices = {
            0, 1, 2,
            0, 2, 3
        };

        Mesh* mesh = new Mesh(name);
        mesh->InitFromData(vertices, indices);

        return mesh;
    }

    Mesh* CreateGrassRail(const std::string& name, glm::vec3 leftBottomCorner) {
        float y_offs = 0.01f;
        glm::vec3 corner = leftBottomCorner + glm::vec3(0, y_offs, 0);

        glm::vec3 offset{SIZE_SEGMENT / 4.f, 0, 0};

        std::vector<VertexFormat> vertices = {
            VertexFormat(corner + offset, COLOR_RAIL),
            VertexFormat(corner + glm::vec3(SIZE_SEGMENT, 0, 0) - offset, COLOR_RAIL),
            VertexFormat(corner + glm::vec3(SIZE_SEGMENT, 0, SIZE_SEGMENT) - offset, COLOR_RAIL),
            VertexFormat(corner + glm::vec3(0, 0, SIZE_SEGMENT) + offset, COLOR_RAIL)
        };

        // Create indices
        std::vector<unsigned int> indices = {
            0, 1, 2,
            0, 2, 3
        };

        Mesh* mesh = new Mesh(name);
        mesh->InitFromData(vertices, indices);

        return mesh;
    }

    Mesh* CreateMountainRail(const std::string& name, glm::vec3 leftBottomCorner) {
        float y_offs = 0.01f;
        glm::vec3 corner = leftBottomCorner + glm::vec3(0, y_offs, 0);

        glm::vec3 offset{SIZE_SEGMENT / 4.f, 0, 0};

        glm::vec3 segment_z_offset = glm::vec3(0, 0, SIZE_SEGMENT / 4.f);
        glm::vec3 initial_seg_z_offset = glm::vec3(0, 0, SIZE_SEGMENT / 8.f);
        glm::vec3 segment_x_offset = glm::vec3((SIZE_SEGMENT - 2.f * offset.x) / 3, 0, 0);
        glm::vec3 stripe_corner = corner + offset + initial_seg_z_offset + segment_x_offset + glm::vec3(0, 0.03f, 0);

        glm::vec3 stripe_2_corner = stripe_corner + 2.f * segment_z_offset;

        std::vector<VertexFormat> vertices = {
            // Base
            VertexFormat(corner + offset, COLOR_RAIL),
            VertexFormat(corner + glm::vec3(SIZE_SEGMENT, 0, 0) - offset, COLOR_RAIL),
            VertexFormat(corner + glm::vec3(SIZE_SEGMENT, 0, SIZE_SEGMENT) - offset, COLOR_RAIL),
            VertexFormat(corner + glm::vec3(0, 0, SIZE_SEGMENT) + offset, COLOR_RAIL),

            // Stripes
            VertexFormat(stripe_corner, COLOR_WHITE),
            VertexFormat(stripe_corner + segment_z_offset, COLOR_WHITE),
            VertexFormat(stripe_corner + segment_z_offset + segment_x_offset, COLOR_WHITE),
            VertexFormat(stripe_corner + segment_x_offset, COLOR_WHITE),

            VertexFormat(stripe_2_corner, COLOR_WHITE),
            VertexFormat(stripe_2_corner + segment_z_offset, COLOR_WHITE),
            VertexFormat(stripe_2_corner + segment_z_offset + segment_x_offset, COLOR_WHITE),
            VertexFormat(stripe_2_corner + segment_x_offset, COLOR_WHITE),
        };

        // Create indices
        std::vector<unsigned int> indices = {
            // Base
            0, 1, 2,
            0, 2, 3,

            // 1st stripe
            4, 5, 6,
            4, 6, 7,

            // 2nd stripe
            8, 9, 10,
            8, 10, 11,
        };

        Mesh* mesh = new Mesh(name);
        mesh->InitFromData(vertices, indices);

        return mesh;
    }

    Mesh* CreateWaterRail(const std::string& name, glm::vec3 leftBottomCorner) {
        float y_offs = 0.01f;
        glm::vec3 corner = leftBottomCorner + glm::vec3(0, y_offs, 0);

        glm::vec3 offset{SIZE_SEGMENT / 4.f, 0, 0};

        glm::vec3 segment_x_offset = glm::vec3((SIZE_SEGMENT - 2.f * offset.x) / 5, 0, 0);
        glm::vec3 stripe_corner = corner + offset + segment_x_offset + glm::vec3(0, 0.03f, 0);

        glm::vec3 stripe_2_corner = corner + offset + segment_x_offset * 3.f + glm::vec3(0, 0.03f, 0);


        std::vector<VertexFormat> vertices = {
            // Base
            VertexFormat(corner + offset, COLOR_RAIL),
            VertexFormat(corner + glm::vec3(SIZE_SEGMENT, 0, 0) - offset, COLOR_RAIL),
            VertexFormat(corner + glm::vec3(SIZE_SEGMENT, 0, SIZE_SEGMENT) - offset, COLOR_RAIL),
            VertexFormat(corner + glm::vec3(0, 0, SIZE_SEGMENT) + offset, COLOR_RAIL),

            // White stripes
            VertexFormat(stripe_corner, COLOR_WHITE),
            VertexFormat(stripe_corner + glm::vec3(0, 0, SIZE_SEGMENT), COLOR_WHITE),
            VertexFormat(stripe_corner + glm::vec3(0, 0, SIZE_SEGMENT) + segment_x_offset, COLOR_WHITE),
            VertexFormat(stripe_corner + segment_x_offset, COLOR_WHITE),

            // 2nd stripe
            VertexFormat(stripe_2_corner, COLOR_WHITE),
            VertexFormat(stripe_2_corner + glm::vec3(0, 0, SIZE_SEGMENT), COLOR_WHITE),
            VertexFormat(stripe_2_corner + glm::vec3(0, 0, SIZE_SEGMENT) + segment_x_offset, COLOR_WHITE),
            VertexFormat(stripe_2_corner + segment_x_offset, COLOR_WHITE)
        };

        // Create indices
        std::vector<unsigned int> indices = {
            0, 1, 2,
            0, 2, 3,

            4, 5, 6,
            4, 6, 7,

            8, 9, 10,
            8, 10, 11
        };

        Mesh* mesh = new Mesh(name);
        mesh->InitFromData(vertices, indices);

        return mesh;
    }

    Mesh* CreateTurnRail(const std::string& name, glm::vec3 leftBottomCorner) {
        glm::vec3 corner = leftBottomCorner + glm::vec3(0, 0.01f, 0);
        glm::vec3 x_offset{SIZE_SEGMENT / 4.f, 0, 0};
        glm::vec3 z_offset{0, 0, SIZE_SEGMENT / 4.f};


        std::vector<VertexFormat> vertices = {
            VertexFormat(corner + z_offset, COLOR_RAIL),
            VertexFormat(corner + 3.f * z_offset, COLOR_RAIL),
            VertexFormat(corner + 3.f * z_offset + x_offset, COLOR_RAIL),
            VertexFormat(corner + z_offset + x_offset, COLOR_RAIL),
            VertexFormat(corner + 4.f * z_offset + x_offset, COLOR_RAIL),
            VertexFormat(corner + 4.f * z_offset + 3.f * x_offset, COLOR_RAIL),
            VertexFormat(corner + z_offset + 3.f * x_offset, COLOR_RAIL)
        };

        std::vector<unsigned int> indices{
            0, 1, 2,
            0, 2, 3,
            3, 4, 5,
            3, 5, 6
        };

        Mesh* mesh = new Mesh(name);
        mesh->InitFromData(vertices, indices);

        return mesh;
    }

    Mesh* CreateTrain() {
        glm::vec3 center = glm::vec3(0, 0, 0);

        float base_length = SIZE_SEGMENT;
        float base_width = SIZE_SEGMENT / 2.f;
        float base_height = SIZE_SEGMENT / 20.f;

        float cabin_length = SIZE_SEGMENT / 3.f;
        float cabin_width = SIZE_SEGMENT / 2.f;
        float cabin_height = SIZE_SEGMENT / 3.f;

        float barrel_length = base_length - cabin_length - 0.3f;
        float barrel_radius = cabin_width / 5.f;

        float little_barrel_length = 0.2f;
        float little_barrel_radius = barrel_radius / 3.f;

        float wheel_radius = base_length / 16.f;
        float wheel_width = base_height;

        glm::vec3 base_corner = center + glm::vec3(-base_width / 2.f, 2 * wheel_radius, -base_length / 2.f);

        std::vector<VertexFormat> vertices;

        unsigned int index = 0;

        vertices.emplace_back(base_corner, COLOR_YELLOW); // 0
        vertices.emplace_back(base_corner + glm::vec3(base_width, 0, 0), COLOR_YELLOW); // 1
        vertices.emplace_back(base_corner + glm::vec3(base_width, 0, base_length), COLOR_YELLOW); // 2
        vertices.emplace_back(base_corner + glm::vec3(0, 0, base_length), COLOR_YELLOW); // 3
        vertices.emplace_back(base_corner + glm::vec3(0, base_height, 0), COLOR_YELLOW); // 4
        vertices.emplace_back(base_corner + glm::vec3(base_width, base_height, 0), COLOR_YELLOW); // 5
        vertices.emplace_back(base_corner + glm::vec3(base_width, base_height, base_length), COLOR_YELLOW); // 6
        vertices.emplace_back(base_corner + glm::vec3(0, base_height, base_length), COLOR_YELLOW); // 7

        std::vector<unsigned int> indices = {
            0, 1, 2,
            0, 2, 3,

            4, 5, 6,
            4, 6, 7,

            0, 1, 5,
            0, 5, 4,

            2, 3, 7,
            2, 7, 6,

            1, 2, 6,
            1, 5, 6,

            0, 3, 7,
            0, 7, 4
        };

        index = indices.size();

        glm::vec3 cabin_corner = base_corner + glm::vec3(0, base_height, 0);

        vertices.emplace_back(cabin_corner + glm::vec3(0, 0, cabin_length), COLOR_GREEN); // 8
        vertices.emplace_back(cabin_corner + glm::vec3(cabin_width, 0, cabin_length), COLOR_GREEN); // 9
        vertices.emplace_back(cabin_corner + glm::vec3(cabin_width, cabin_height, cabin_length), COLOR_GREEN); // 10
        vertices.emplace_back(cabin_corner + glm::vec3(0, cabin_height, cabin_length), COLOR_GREEN); // 11
        vertices.emplace_back(cabin_corner + glm::vec3(0, cabin_height, 0), COLOR_GREEN); // 12
        vertices.emplace_back(cabin_corner + glm::vec3(cabin_width, cabin_height, 0), COLOR_GREEN); // 13
        vertices.emplace_back(cabin_corner, COLOR_GREEN); // 14
        vertices.emplace_back(cabin_corner + glm::vec3(cabin_width, 0, 0), COLOR_GREEN); // 15

        indices.push_back(14);
        indices.push_back(15);
        indices.push_back(13);

        indices.push_back(14);
        indices.push_back(13);
        indices.push_back(12);


        indices.push_back(15);
        indices.push_back(9);
        indices.push_back(10);

        indices.push_back(15);
        indices.push_back(10);
        indices.push_back(13);


        indices.push_back(9);
        indices.push_back(8);
        indices.push_back(11);

        indices.push_back(9);
        indices.push_back(11);
        indices.push_back(10);


        indices.push_back(8);
        indices.push_back(14);
        indices.push_back(12);

        indices.push_back(8);
        indices.push_back(12);
        indices.push_back(11);


        indices.push_back(11);
        indices.push_back(12);
        indices.push_back(13);

        indices.push_back(11);
        indices.push_back(13);
        indices.push_back(10);

        index = indices.size();

        // Cilinder
        glm::vec3 cil_base_center = base_corner + glm::vec3(base_width / 2.f, base_height, cabin_length)
            + glm::vec3(0, barrel_radius, 0);

        const int slices = 32;
        const float two_pi = 6.28318530718f;

        int startIndex = static_cast<int>(vertices.size());
        index = startIndex;

        for (int i = 0; i < slices; i++) {
            float angle = two_pi * i / slices;
            float c = cosf(angle);
            float s = sinf(angle);

            glm::vec3 p0 = cil_base_center + glm::vec3(barrel_radius * c, barrel_radius * s, 0.0f);
            glm::vec3 p1 = p0 + glm::vec3(0.0f, 0.0f, barrel_length);

            vertices.push_back(VertexFormat(p0, COLOR_BLUE));
            vertices.push_back(VertexFormat(p1, COLOR_BLUE));
        }

        for (int i = 0; i < slices; i++) {
            int next = (i + 1) % slices;

            int v0 = startIndex + i * 2;
            int v1 = startIndex + next * 2;
            int v2 = startIndex + i * 2 + 1;
            int v3 = startIndex + next * 2 + 1;

            indices.push_back(v0);
            indices.push_back(v1);
            indices.push_back(v3);

            indices.push_back(v0);
            indices.push_back(v3);
            indices.push_back(v2);
        }

        int capCenterIndex = static_cast<int>(vertices.size());
        glm::vec3 capCenter = cil_base_center + glm::vec3(0.0f, 0.0f, barrel_length);
        vertices.push_back(VertexFormat(capCenter, COLOR_BLUE));

        for (int i = 0; i < slices; i++) {
            int next = (i + 1) % slices;

            int v_curr = startIndex + i * 2 + 1;
            int v_next = startIndex + next * 2 + 1;

            indices.push_back(capCenterIndex);
            indices.push_back(v_curr);
            indices.push_back(v_next);
        }

        glm::vec3 little_cil_base_center = cil_base_center + glm::vec3(0.0f, 0.0f, barrel_length);

        startIndex = static_cast<int>(vertices.size());
        index = startIndex;

        for (int i = 0; i < slices; i++) {
            float angle = two_pi * i / slices;
            float c = cosf(angle);
            float s = sinf(angle);

            glm::vec3 p0 = little_cil_base_center + glm::vec3(little_barrel_length * c, little_barrel_radius * s, 0.0f);
            glm::vec3 p1 = p0 + glm::vec3(0.0f, 0.0f, little_barrel_length);

            vertices.push_back(VertexFormat(p0, COLOR_MAGENTA));
            vertices.push_back(VertexFormat(p1, COLOR_MAGENTA));
        }

        for (int i = 0; i < slices; i++) {
            int next = (i + 1) % slices;

            int v0 = startIndex + i * 2;
            int v1 = startIndex + next * 2;
            int v2 = startIndex + i * 2 + 1;
            int v3 = startIndex + next * 2 + 1;

            indices.push_back(v0);
            indices.push_back(v1);
            indices.push_back(v3);

            indices.push_back(v0);
            indices.push_back(v3);
            indices.push_back(v2);
        }

        capCenterIndex = static_cast<int>(vertices.size());
        capCenter = little_cil_base_center + glm::vec3(0.0f, 0.0f, little_barrel_length);
        vertices.push_back(VertexFormat(capCenter, COLOR_MAGENTA));

        for (int i = 0; i < slices; i++) {
            int next = (i + 1) % slices;

            int v_curr = startIndex + i * 2 + 1;
            int v_next = startIndex + next * 2 + 1;

            indices.push_back(capCenterIndex);
            indices.push_back(v_curr);
            indices.push_back(v_next);
        }

        // Wheels
        glm::vec3 center_wheel_3 = base_corner + glm::vec3(0, -wheel_radius, base_length / 2.f);

        glm::vec3 wheel_centers_right[7];
        float wheel_spacing = 2.f * wheel_radius;

        wheel_centers_right[3] = center_wheel_3;
        for (int offset = 1; offset <= 3; ++offset) {
            float dz = offset * wheel_spacing;
            wheel_centers_right[3 + offset] = center_wheel_3 + glm::vec3(0.f, 0.f, dz);
            wheel_centers_right[3 - offset] = center_wheel_3 - glm::vec3(0.f, 0.f, dz);
        }

        for (int k = 0; k < 7; ++k) {
            glm::vec3 c = wheel_centers_right[k];

            startIndex = static_cast<int>(vertices.size());

            for (int i = 0; i < slices; ++i) {
                float angle = two_pi * i / slices;
                float cs = cosf(angle);
                float sn = sinf(angle);

                glm::vec3 p0 = c + glm::vec3(0.f, wheel_radius * cs, wheel_radius * sn);
                glm::vec3 p1 = p0 + glm::vec3(wheel_width, 0.f, 0.f);

                vertices.push_back(VertexFormat(p0, COLOR_RED));
                vertices.push_back(VertexFormat(p1, COLOR_RED));
            }

            for (int i = 0; i < slices; ++i) {
                int next = (i + 1) % slices;

                int v0 = startIndex + i * 2;
                int v1 = startIndex + next * 2;
                int v2 = startIndex + i * 2 + 1;
                int v3 = startIndex + next * 2 + 1;

                indices.push_back(v0);
                indices.push_back(v2);
                indices.push_back(v3);

                indices.push_back(v0);
                indices.push_back(v3);
                indices.push_back(v1);
            }

            capCenterIndex = static_cast<int>(vertices.size());
            vertices.push_back(VertexFormat(c, COLOR_RED));

            for (int i = 0; i < slices; ++i) {
                int next = (i + 1) % slices;

                int v_curr = startIndex + i * 2;
                int v_next = startIndex + next * 2;

                indices.push_back(capCenterIndex);
                indices.push_back(v_next);
                indices.push_back(v_curr);
            }
        }

        glm::vec3 center_wheel_3_left = base_corner + glm::vec3(base_width, -wheel_radius, base_length / 2.f);

        glm::vec3 wheel_centers_left[7];
        wheel_spacing = 2.f * wheel_radius;

        wheel_centers_left[3] = center_wheel_3_left;
        for (int offset = 1; offset <= 3; ++offset) {
            float dz = offset * wheel_spacing;
            wheel_centers_left[3 + offset] = center_wheel_3_left + glm::vec3(0.f, 0.f, dz);
            wheel_centers_left[3 - offset] = center_wheel_3_left - glm::vec3(0.f, 0.f, dz);
        }

        for (int k = 0; k < 7; ++k) {
            glm::vec3 c = wheel_centers_left[k];

            startIndex = static_cast<int>(vertices.size());

            for (int i = 0; i < slices; ++i) {
                float angle = two_pi * i / slices;
                float cs = cosf(angle);
                float sn = sinf(angle);

                glm::vec3 p0 = c + glm::vec3(0.f, wheel_radius * cs, wheel_radius * sn);
                glm::vec3 p1 = p0 + glm::vec3(-wheel_width, 0.f, 0.f);

                vertices.push_back(VertexFormat(p0, COLOR_RED));
                vertices.push_back(VertexFormat(p1, COLOR_RED));
            }

            for (int i = 0; i < slices; ++i) {
                int next = (i + 1) % slices;

                int v0 = startIndex + i * 2;
                int v1 = startIndex + next * 2;
                int v2 = startIndex + i * 2 + 1;
                int v3 = startIndex + next * 2 + 1;

                indices.push_back(v0);
                indices.push_back(v2);
                indices.push_back(v3);

                indices.push_back(v0);
                indices.push_back(v3);
                indices.push_back(v1);
            }

            capCenterIndex = static_cast<int>(vertices.size());
            vertices.push_back(VertexFormat(c, COLOR_RED));

            for (int i = 0; i < slices; ++i) {
                int next = (i + 1) % slices;

                int v_curr = startIndex + i * 2;
                int v_next = startIndex + next * 2;

                indices.push_back(capCenterIndex);
                indices.push_back(v_next);
                indices.push_back(v_curr);
            }
        }

        Mesh* mesh = new Mesh("train");
        mesh->InitFromData(vertices, indices);

        return mesh;
    }

    Mesh* CreateWagon() {
        glm::vec3 center = glm::vec3(0, 0, 0);

        float base_length = SIZE_SEGMENT - 0.3f;
        float base_width = SIZE_SEGMENT / 2.f;
        float base_height = SIZE_SEGMENT / 20.f;

        float cabin_length = SIZE_SEGMENT / 3.f;
        float cabin_width = SIZE_SEGMENT / 2.f;
        float cabin_height = SIZE_SEGMENT / 3.f;

        float wheel_radius = base_length / 16.f;
        float wheel_width = base_height;

        glm::vec3 base_corner = center + glm::vec3(-base_width / 2.f, 2 * wheel_radius, -base_length / 2.f);

        std::vector<VertexFormat> vertices;

        vertices.emplace_back(base_corner, COLOR_YELLOW); // 0
        vertices.emplace_back(base_corner + glm::vec3(base_width, 0, 0), COLOR_YELLOW); // 1
        vertices.emplace_back(base_corner + glm::vec3(base_width, 0, base_length), COLOR_YELLOW); // 2
        vertices.emplace_back(base_corner + glm::vec3(0, 0, base_length), COLOR_YELLOW); // 3
        vertices.emplace_back(base_corner + glm::vec3(0, base_height, 0), COLOR_YELLOW); // 4
        vertices.emplace_back(base_corner + glm::vec3(base_width, base_height, 0), COLOR_YELLOW); // 5
        vertices.emplace_back(base_corner + glm::vec3(base_width, base_height, base_length), COLOR_YELLOW); // 6
        vertices.emplace_back(base_corner + glm::vec3(0, base_height, base_length), COLOR_YELLOW); // 7

        std::vector<unsigned int> indices = {
            0, 1, 2,
            0, 2, 3,

            4, 5, 6,
            4, 6, 7,

            0, 1, 5,
            0, 5, 4,

            2, 3, 7,
            2, 7, 6,

            1, 2, 6,
            1, 5, 6,

            0, 3, 7,
            0, 7, 4
        };

        glm::vec3 cabin_corner = base_corner + glm::vec3(0, base_height, 0);

        vertices.emplace_back(cabin_corner + glm::vec3(0, 0, base_length), COLOR_GREEN); // 8
        vertices.emplace_back(cabin_corner + glm::vec3(cabin_width, 0, base_length), COLOR_GREEN); // 9
        vertices.emplace_back(cabin_corner + glm::vec3(cabin_width, cabin_height, base_length), COLOR_GREEN); // 10
        vertices.emplace_back(cabin_corner + glm::vec3(0, cabin_height, base_length), COLOR_GREEN); // 11
        vertices.emplace_back(cabin_corner + glm::vec3(0, cabin_height, 0), COLOR_GREEN); // 12
        vertices.emplace_back(cabin_corner + glm::vec3(cabin_width, cabin_height, 0), COLOR_GREEN); // 13
        vertices.emplace_back(cabin_corner, COLOR_GREEN); // 14
        vertices.emplace_back(cabin_corner + glm::vec3(cabin_width, 0, 0), COLOR_GREEN); // 15

        indices.push_back(14);
        indices.push_back(15);
        indices.push_back(13);

        indices.push_back(14);
        indices.push_back(13);
        indices.push_back(12);


        indices.push_back(15);
        indices.push_back(9);
        indices.push_back(10);

        indices.push_back(15);
        indices.push_back(10);
        indices.push_back(13);


        indices.push_back(9);
        indices.push_back(8);
        indices.push_back(11);

        indices.push_back(9);
        indices.push_back(11);
        indices.push_back(10);


        indices.push_back(8);
        indices.push_back(14);
        indices.push_back(12);

        indices.push_back(8);
        indices.push_back(12);
        indices.push_back(11);


        indices.push_back(11);
        indices.push_back(12);
        indices.push_back(13);

        indices.push_back(11);
        indices.push_back(13);
        indices.push_back(10);

        const int slices = 32;
        const float two_pi = 6.28318530718f;

        glm::vec3 center_wheel_mid_right = base_corner + glm::vec3(0.f, -wheel_radius, base_length / 2.f);
        float wheel_spacing = 2.f * wheel_radius;

        glm::vec3 wheel_centers_right[2];
        wheel_centers_right[0] = center_wheel_mid_right - glm::vec3(0.f, 0.f, 3.f * wheel_spacing);
        wheel_centers_right[1] = center_wheel_mid_right + glm::vec3(0.f, 0.f, 3.f * wheel_spacing);

        for (int k = 0; k < 2; ++k) {
            glm::vec3 c = wheel_centers_right[k];
            int startIndex = static_cast<int>(vertices.size());

            for (int i = 0; i < slices; ++i) {
                float angle = two_pi * i / slices;
                float cs = cosf(angle);
                float sn = sinf(angle);
                glm::vec3 p0 = c + glm::vec3(0.f, wheel_radius * cs, wheel_radius * sn);
                glm::vec3 p1 = p0 + glm::vec3(wheel_width, 0.f, 0.f);
                vertices.push_back(VertexFormat(p0, COLOR_RED));
                vertices.push_back(VertexFormat(p1, COLOR_RED));
            }

            for (int i = 0; i < slices; ++i) {
                int next = (i + 1) % slices;
                int v0 = startIndex + i * 2;
                int v1 = startIndex + next * 2;
                int v2 = startIndex + i * 2 + 1;
                int v3 = startIndex + next * 2 + 1;
                indices.push_back(v0);
                indices.push_back(v2);
                indices.push_back(v3);
                indices.push_back(v0);
                indices.push_back(v3);
                indices.push_back(v1);
            }

            int capCenterIndex = static_cast<int>(vertices.size());
            vertices.push_back(VertexFormat(c, COLOR_RED));

            for (int i = 0; i < slices; ++i) {
                int next = (i + 1) % slices;
                int v_curr = startIndex + i * 2;
                int v_next = startIndex + next * 2;
                indices.push_back(capCenterIndex);
                indices.push_back(v_next);
                indices.push_back(v_curr);
            }
        }

        glm::vec3 center_wheel_mid_left = base_corner + glm::vec3(base_width, -wheel_radius, base_length / 2.f);

        glm::vec3 wheel_centers_left[2];
        wheel_centers_left[0] = center_wheel_mid_left - glm::vec3(0.f, 0.f, 3.f * wheel_spacing);
        wheel_centers_left[1] = center_wheel_mid_left + glm::vec3(0.f, 0.f, 3.f * wheel_spacing);

        for (int k = 0; k < 2; ++k) {
            glm::vec3 c = wheel_centers_left[k];
            int startIndex = static_cast<int>(vertices.size());

            for (int i = 0; i < slices; ++i) {
                float angle = two_pi * i / slices;
                float cs = cosf(angle);
                float sn = sinf(angle);
                glm::vec3 p0 = c + glm::vec3(0.f, wheel_radius * cs, wheel_radius * sn);
                glm::vec3 p1 = p0 + glm::vec3(-wheel_width, 0.f, 0.f);
                vertices.push_back(VertexFormat(p0, COLOR_RED));
                vertices.push_back(VertexFormat(p1, COLOR_RED));
            }

            for (int i = 0; i < slices; ++i) {
                int next = (i + 1) % slices;
                int v0 = startIndex + i * 2;
                int v1 = startIndex + next * 2;
                int v2 = startIndex + i * 2 + 1;
                int v3 = startIndex + next * 2 + 1;
                indices.push_back(v0);
                indices.push_back(v2);
                indices.push_back(v3);
                indices.push_back(v0);
                indices.push_back(v3);
                indices.push_back(v1);
            }

            int capCenterIndex = static_cast<int>(vertices.size());
            vertices.push_back(VertexFormat(c, COLOR_RED));

            for (int i = 0; i < slices; ++i) {
                int next = (i + 1) % slices;
                int v_curr = startIndex + i * 2;
                int v_next = startIndex + next * 2;
                indices.push_back(capCenterIndex);
                indices.push_back(v_next);
                indices.push_back(v_curr);
            }
        }


        Mesh* mesh = new Mesh("wagon");
        mesh->InitFromData(vertices, indices);

        return mesh;
    }

    Mesh* CreateDraisineBody() {
        glm::vec3 center = glm::vec3(0, 0, 0);

        float base_width = SIZE_SEGMENT / 2.f - 0.5f;
        float base_length = SIZE_SEGMENT / 2.f;
        float base_height = 0.7f;

        float wheel_radius = 0.3f;
        float wheel_width = 0.25f;

        glm::vec3 corner = center + glm::vec3(-base_width / 2.f, wheel_radius, -base_length / 2.f);

        std::vector<VertexFormat> vertices;
        vertices.emplace_back(corner, COLOR_ORANGE); // 0
        vertices.emplace_back(corner + glm::vec3(0, 0, base_length), COLOR_ORANGE); // 1
        vertices.emplace_back(corner + glm::vec3(base_width, 0, base_length), COLOR_ORANGE); // 2
        vertices.emplace_back(corner + glm::vec3(base_width, 0, 0), COLOR_ORANGE); // 3
        vertices.emplace_back(corner + glm::vec3(0, base_height, 0), COLOR_ORANGE); // 4
        vertices.emplace_back(corner + glm::vec3(0, base_height, base_length), COLOR_ORANGE); // 5
        vertices.emplace_back(corner + glm::vec3(base_width, base_height, base_length), COLOR_ORANGE); // 6
        vertices.emplace_back(corner + glm::vec3(base_width, base_height, 0), COLOR_ORANGE); // 7

        std::vector<unsigned int> indices = {
            0, 1, 2, 0, 2, 3,
            4, 5, 6, 4, 6, 7,
            0, 1, 5, 0, 5, 4,
            2, 3, 7, 2, 7, 6,
            1, 2, 6, 1, 5, 6,
            0, 3, 7, 0, 7, 4
        };

        const int slices = 32;
        const float two_pi = 6.28318530718f;

        auto addWheel = [&](const glm::vec3& c, float xDir) {
            int startIndex = (int)vertices.size();

            for (int i = 0; i < slices; i++) {
                float angle = two_pi * i / slices;
                float cs = cosf(angle);
                float sn = sinf(angle);

                glm::vec3 p0 = c + glm::vec3(0.f, wheel_radius * cs, wheel_radius * sn);
                glm::vec3 p1 = p0 + glm::vec3(xDir * wheel_width, 0.f, 0.f);

                vertices.emplace_back(p0, COLOR_BLACK);
                vertices.emplace_back(p1, COLOR_BLACK);
            }

            for (int i = 0; i < slices; i++) {
                int next = (i + 1) % slices;

                int v0 = startIndex + i * 2;
                int v1 = startIndex + next * 2;
                int v2 = startIndex + i * 2 + 1;
                int v3 = startIndex + next * 2 + 1;

                indices.push_back(v0);
                indices.push_back(v2);
                indices.push_back(v3);
                indices.push_back(v0);
                indices.push_back(v3);
                indices.push_back(v1);
            }

            int capCenterIndex = (int)vertices.size();
            vertices.emplace_back(c, COLOR_BLACK);

            for (int i = 0; i < slices; i++) {
                int next = (i + 1) % slices;
                int v_curr = startIndex + i * 2;
                int v_next = startIndex + next * 2;

                indices.push_back(capCenterIndex);
                indices.push_back(v_next);
                indices.push_back(v_curr);
            }
        };

        float wheel_center_y = corner.y;

        float wheel_front_z = corner.z + wheel_radius;
        float wheel_back_z = corner.z + base_length - wheel_radius;

        float wheel_left_x = corner.x - wheel_width;
        float wheel_right_x = corner.x + base_width + wheel_width;

        glm::vec3 c_fl = glm::vec3(wheel_left_x, wheel_center_y, wheel_front_z);
        glm::vec3 c_bl = glm::vec3(wheel_left_x, wheel_center_y, wheel_back_z);
        glm::vec3 c_fr = glm::vec3(wheel_right_x, wheel_center_y, wheel_front_z);
        glm::vec3 c_br = glm::vec3(wheel_right_x, wheel_center_y, wheel_back_z);


        addWheel(c_fl, +1.f);
        addWheel(c_bl, +1.f);
        addWheel(c_fr, -1.f);
        addWheel(c_br, -1.f);

        float bar_height = 1.f;
        float bar_radius = 0.1f;

        glm::vec3 barBaseCenter = corner + glm::vec3(base_width / 2.f, base_height, base_length / 2.f);
        glm::vec3 barTopCenter = barBaseCenter + glm::vec3(0.f, bar_height, 0.f);

        int barStart = (int)vertices.size();

        for (int i = 0; i < slices; i++) {
            float angle = two_pi * i / slices;
            float cs = cosf(angle);
            float sn = sinf(angle);

            glm::vec3 p0 = barBaseCenter + glm::vec3(bar_radius * cs, 0.f, bar_radius * sn);
            glm::vec3 p1 = barTopCenter + glm::vec3(bar_radius * cs, 0.f, bar_radius * sn);

            vertices.emplace_back(p0, COLOR_BLACK);
            vertices.emplace_back(p1, COLOR_BLACK);
        }

        for (int i = 0; i < slices; i++) {
            int next = (i + 1) % slices;

            int v0 = barStart + i * 2;
            int v1 = barStart + next * 2;
            int v2 = barStart + i * 2 + 1;
            int v3 = barStart + next * 2 + 1;

            indices.push_back(v0);
            indices.push_back(v1);
            indices.push_back(v3);
            indices.push_back(v0);
            indices.push_back(v3);
            indices.push_back(v2);
        }

        int barCapTop = (int)vertices.size();
        vertices.emplace_back(barTopCenter, COLOR_BLACK);

        for (int i = 0; i < slices; i++) {
            int next = (i + 1) % slices;

            int v_curr = barStart + i * 2 + 1;
            int v_next = barStart + next * 2 + 1;

            indices.push_back(barCapTop);
            indices.push_back(v_curr);
            indices.push_back(v_next);
        }

        Mesh* mesh = new Mesh("draisine_body");
        mesh->InitFromData(vertices, indices);
        return mesh;
    }

Mesh* CreateDraisinHandle()
{
    glm::vec3 center = glm::vec3(0, 0, 0);

    float pillar_height = 1.f;

    float handle_length = 1.6f;
    float handle_radius = 0.08f;

    float grip_length = 0.8f;
    float grip_radius = 0.06f;

    const int slices = 24;
    const float two_pi = 6.28318530718f;

    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    glm::vec3 handle_center = center + glm::vec3(0.f, 0.f, 0.f);

    auto addCylinderCentered = [&](const glm::vec3& cylCenter,
                                   const glm::vec3& dir,
                                   float length,
                                   float radius)
    {
        int startIndex = (int)vertices.size();

        glm::vec3 axis = glm::normalize(dir);

        glm::vec3 ortho1 = glm::normalize(glm::cross(axis, glm::vec3(0, 1, 0)));
        if (glm::length(ortho1) < 0.001f)
            ortho1 = glm::normalize(glm::cross(axis, glm::vec3(1, 0, 0)));
        glm::vec3 ortho2 = glm::cross(axis, ortho1);

        glm::vec3 base = cylCenter - axis * (length * 0.5f);
        glm::vec3 top  = cylCenter + axis * (length * 0.5f);

        for (int i = 0; i < slices; i++) {
            float a = two_pi * i / slices;
            glm::vec3 ring = cosf(a) * ortho1 * radius + sinf(a) * ortho2 * radius;

            vertices.emplace_back(base + ring, COLOR_HANDLE);
            vertices.emplace_back(top  + ring, COLOR_HANDLE);
        }

        for (int i = 0; i < slices; i++) {
            int next = (i + 1) % slices;

            int v0 = startIndex + i * 2;
            int v1 = startIndex + next * 2;
            int v2 = startIndex + i * 2 + 1;
            int v3 = startIndex + next * 2 + 1;

            indices.push_back(v0); indices.push_back(v1); indices.push_back(v3);
            indices.push_back(v0); indices.push_back(v3); indices.push_back(v2);
        }
    };

    addCylinderCentered(handle_center, glm::vec3(0, 0, 1), handle_length, handle_radius);

    glm::vec3 left_end  = handle_center - glm::vec3(0.f, 0.f, handle_length * 0.5f);
    glm::vec3 right_end = handle_center + glm::vec3(0.f, 0.f, handle_length * 0.5f);

    addCylinderCentered(left_end,  glm::vec3(1, 0, 0), grip_length, grip_radius);
    addCylinderCentered(right_end, glm::vec3(1, 0, 0), grip_length, grip_radius);

    Mesh* mesh = new Mesh("draisine_handle");
    mesh->InitFromData(vertices, indices);
    return mesh;
}

    Mesh* CreateCube() {
        glm::vec3 corner = glm::vec3(0, 0, 0);

        float side = SIZE_SEGMENT;

        std::vector<VertexFormat> vertices = {
            VertexFormat(corner, COLOR_BROWN),
            VertexFormat(corner + glm::vec3(side, 0, 0), COLOR_BROWN),
            VertexFormat(corner + glm::vec3(side, 0, side), COLOR_BROWN),
            VertexFormat(corner + glm::vec3(0, 0, side), COLOR_BROWN),
            VertexFormat(corner + glm::vec3(0, side, 0), COLOR_BROWN),
            VertexFormat(corner + glm::vec3(side, side, 0), COLOR_BROWN),
            VertexFormat(corner + glm::vec3(side, side, side), COLOR_BROWN),
            VertexFormat(corner + glm::vec3(0, side, side), COLOR_BROWN)
        };

        std::vector<unsigned int> indices = {
            0, 1, 2,
            0, 2, 3,

            4, 5, 6,
            4, 6, 7,

            0, 1, 5,
            0, 5, 4,

            2, 3, 7,
            2, 7, 6,

            1, 2, 6,
            1, 6, 5,

            0, 3, 7,
            0, 7, 4
        };

        Mesh* mesh = new Mesh("cube");
        mesh->InitFromData(vertices, indices);

        return mesh;
    }

    Mesh* CreatePyramid() {
        glm::vec3 corner = glm::vec3(0, 0, 0);

        float side = SIZE_SEGMENT;

        std::vector<VertexFormat> vertices = {
            VertexFormat(corner, COLOR_GOLD),
            VertexFormat(corner + glm::vec3(side, 0, 0), COLOR_GOLD),
            VertexFormat(corner + glm::vec3(side, 0, side), COLOR_GOLD),
            VertexFormat(corner + glm::vec3(0, 0, side), COLOR_GOLD),
            VertexFormat(corner + glm::vec3(side / 2.f, side, side / 2.f), COLOR_GOLD)
        };

        std::vector<unsigned int> indices = {
            0, 1, 2,
            0, 2, 3,

            0, 1, 4,

            1, 2, 4,

            2, 3, 4,

            3, 0, 4
        };

        Mesh* mesh = new Mesh("pyramid");
        mesh->InitFromData(vertices, indices);

        return mesh;
    }

    Mesh* CreateSpehere() {
        float radius = SIZE_SEGMENT / 2.f;
        glm::vec3 center = glm::vec3(SIZE_SEGMENT / 2.f, 0, SIZE_SEGMENT / 2.f);

        int stacks = 16;
        int slices = 16;

        std::vector<VertexFormat> vertices;
        std::vector<unsigned int> indices;

        for (int i = 0; i <= stacks; i++) {
            float phi = M_PI * i / stacks;
            for (int j = 0; j <= slices; j++) {
                float theta = 2 * M_PI * j / slices;

                float x = radius * sin(phi) * cos(theta);
                float y = radius * cos(phi);
                float z = radius * sin(phi) * sin(theta);

                vertices.push_back(VertexFormat(center + glm::vec3(x, y, z), COLOR_PINK));
            }
        }

        for (int i = 0; i < stacks; i++) {
            for (int j = 0; j < slices; j++) {
                int first = i * (slices + 1) + j;
                int second = first + slices + 1;

                indices.push_back(first);
                indices.push_back(second);
                indices.push_back(first + 1);

                indices.push_back(second);
                indices.push_back(second + 1);
                indices.push_back(first + 1);
            }
        }

        Mesh* mesh = new Mesh("sphere");
        mesh->InitFromData(vertices, indices);

        return mesh;
    }




} // Objects

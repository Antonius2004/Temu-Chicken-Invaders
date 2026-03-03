//
// Created by patur on 12/8/2025.
//

#include <iostream>

#include "Tema2.h"
#include "Objects.h"
#include "Constants.h"
#include "TurnRail.h"
#include "StraightRail.h"
#include "stb/stb_image.h"

using namespace std;
using namespace m1;

void Tema2::LoadMeshes() {
    // Grass
    Mesh* mesh = Objects::CreateSquare("grass", glm::vec3(0, 0, 0), COLOR_GRASS);
    AddMeshToList(mesh);

    // Mountain
    mesh = Objects::CreateSquare("mountain", glm::vec3(0, 0, 0), COLOR_MOUNTAIN);
    AddMeshToList(mesh);

    // Mountain
    mesh = Objects::CreateSquare("water", glm::vec3(0, 0, 0), COLOR_WATER);
    AddMeshToList(mesh);

    // Rails
    mesh = Objects::CreateGrassRail("grass_straight_rail", glm::vec3(0, 0, 0));
    AddMeshToList(mesh);

    mesh = Objects::CreateMountainRail("mountain_straight_rail", glm::vec3(0, 0, 0));
    AddMeshToList(mesh);

    mesh = Objects::CreateWaterRail("water_straight_rail", glm::vec3(0, 0, 0));
    AddMeshToList(mesh);

    mesh = Objects::CreateTurnRail("turn_rail", glm::vec3(0, 0, 0));
    AddMeshToList(mesh);

    mesh = Objects::CreateTrain();
    AddMeshToList(mesh);

    mesh = Objects::CreateWagon();
    AddMeshToList(mesh);

    mesh = Objects::CreateDraisineBody();
    AddMeshToList(mesh);

    mesh = Objects::CreateDraisinHandle();
    AddMeshToList(mesh);

    mesh = Objects::CreateCube();
    AddMeshToList(mesh);

    mesh = Objects::CreatePyramid();
    AddMeshToList(mesh);

    mesh = Objects::CreateSpehere();;
    AddMeshToList(mesh);
}

void Tema2::CreateTerrain() {
    std::vector<std::vector<Block>> arr;

    for (int i = 0; i < TERRAIN_SEGMENTS; i++) {
        std::vector<Block> row;
        glm::vec3 base_pos{i * SIZE_SEGMENT, 0, 0};

        for (int j = 0; j < TERRAIN_SEGMENTS; j++) {
            glm::vec3 offset{0, 0, j * SIZE_SEGMENT};
            glm::vec3 pos = base_pos + offset;

            // Default block
            TerrainType terrain_type = TerrainType::Grass;

            // Set mountain
            if ((i > 5 && j > 6) || (i < 2 && j < 4)) terrain_type = TerrainType::Mountain;

            // Set river
            if ((i > 4 && j == 3) || (i == 5 && j > 2 && j < 7) || (i < 5 && j == 6))
                terrain_type = TerrainType::Water;

            Block block = Block(pos, terrain_type, false, false, i, j);

            row.push_back(block);
        }

        arr.push_back(row);
    }

    this->terrain_arr_ = arr;
}

void Tema2::RenderTerrain() {
    auto& terrain = this->terrain_arr_;

    for (int i = 0; i < TERRAIN_SEGMENTS; i++) {
        for (int j = 0; j < TERRAIN_SEGMENTS; j++) {
            auto& block = terrain[i][j];
            RenderMesh(meshes[block.get_mesh_name()], shaders["VertexColor"], block.get_position());
        }
    }
}

void Tema2::RenderStations() {
    {
        int i = 5;
        int j = 1;

        auto &block = this->terrain_arr_[i][j];

        RenderMesh(meshes["cube"], shaders["VertexColor"], block.get_position());
    }
    {
        int i = 4;
        int j = 8;

        auto &block = this->terrain_arr_[i][j];

        RenderMesh(meshes["pyramid"], shaders["VertexColor"], block.get_position());
    }
    {
        int i = 9;
        int j = 11;

        auto &block = this->terrain_arr_[i][j];

        RenderMesh(meshes["sphere"], shaders["VertexColor"], block.get_position());
    }
}


void Tema2::CreateRails() {
    // Build all OX parallel rails
    {
        std::vector<int> lines = {1, 3, 7, 10};
        std::vector<std::pair<int, int>> ranges = {
            {6, 9},
            {3, 9},
            {3, 9},
            {7, 9}
        };

        for (int idx = 0; idx < lines.size(); idx++) {
            int i = lines[idx];
            int j_start = ranges[idx].first;
            int j_end = ranges[idx].second;

            for (int j = j_start; j <= j_end; j++) {
                if (j == 5) { continue; }

                // Set terrain type
                TerrainType type = TerrainType::Grass;
                std::string mesh_name = "grass_straight_rail";
                if ((i == 1 && j == 6) || (i == 3 && j == 6) || (i == 7 && j == 3)) {
                    type = TerrainType::Water;
                    mesh_name = "water_straight_rail";
                }
                if (i >= 6 && j >= 7) {
                    type = TerrainType::Mountain;
                    mesh_name = "mountain_straight_rail";
                }

                // Get block
                auto& block = this->terrain_arr_[i][j];

                // Construct rail
                auto rail = StraightRail(type, mesh_name, StraightOrientation::VE,
                                         block.get_position());

                // Add to block
                block.UpdateRail(rail);
            }
        }
    }

    // Build parallel rails to OY
    {
        std::vector<int> columns = {2, 5, 10};
        std::vector<std::pair<int, int>> ranges = {
            {4, 6},
            {2, 9},
            {2, 9}
        };

        for (size_t idx = 0; idx < columns.size(); ++idx) {
            int j = columns[idx];
            int iStart = ranges[idx].first;
            int iEnd = ranges[idx].second;

            for (int i = iStart; i <= iEnd; ++i) {
                // Skip intersections
                if (i == 3 || i == 7) { continue; }

                // Set terrain type
                TerrainType type = TerrainType::Grass;
                std::string mesh_name = "grass_straight_rail";

                if (i == 5 && j == 5) {
                    type = TerrainType::Water;
                    mesh_name = "water_straight_rail";
                }
                if (i >= 6 && j >= 7) {
                    type = TerrainType::Mountain;
                    mesh_name = "mountain_straight_rail";
                }

                // Get block
                auto& block = this->terrain_arr_[i][j];

                // Construct rail
                auto rail = StraightRail(type, mesh_name, StraightOrientation::NS,
                                         block.get_position());

                // Add to block
                block.UpdateRail(rail);
            }
        }
    }

    // Build corners
    {
        // SE corners
        int i = 7;
        int j = 2;

        auto& block = this->terrain_arr_[i][j];

        auto rail = TurnRail("turn_rail", TurnOrientation::SE,
                             block.get_position());

        block.UpdateRail(rail);
    }

    {
        int i = 10;
        int j = 5;

        auto& block = this->terrain_arr_[i][j];

        auto rail = TurnRail("turn_rail", TurnOrientation::SE,
                             block.get_position());

        block.UpdateRail(rail);
    }

    {
        // NE corners
        int i = 3;
        int j = 2;

        auto& block = this->terrain_arr_[i][j];

        auto rail = TurnRail("turn_rail", TurnOrientation::NE,
                             block.get_position());

        block.UpdateRail(rail);
    }
    {
        int i = 1;
        int j = 5;

        auto& block = this->terrain_arr_[i][j];

        auto rail = TurnRail("turn_rail", TurnOrientation::NE,
                             block.get_position());

        block.UpdateRail(rail);
    }
    {
        // SV corner
        int i = 10;
        int j = 10;

        auto& block = this->terrain_arr_[i][j];

        auto rail = TurnRail("turn_rail", TurnOrientation::SV,
                             block.get_position());

        block.UpdateRail(rail);
    }
    {
        // NV corner
        int i = 1;
        int j = 10;

        auto& block = this->terrain_arr_[i][j];

        auto rail = TurnRail("turn_rail", TurnOrientation::NV,
                             block.get_position());

        block.UpdateRail(rail);
    }

    // Build tri-intersection, 2 turns one straight
    {
        std::vector<int> i = {7, 3};
        int j = 10;

        for (int k = 0; k < 2; k++) {
            auto& block = this->terrain_arr_[i[k]][j];

            auto rail = TurnRail("turn_rail", TurnOrientation::NV, block.get_position());
            block.UpdateRail(rail);

            rail = TurnRail("turn_rail", TurnOrientation::SV, block.get_position());
            block.UpdateRail(rail);

            auto srail = StraightRail(TerrainType::Grass, "grass_straight_rail", StraightOrientation::NS,
                                      block.get_position());
            block.UpdateRail(srail);
        }
    }

    // Build 4-way intersection (all turns and straights)
    {
        std::vector<int> i = {7, 3};
        int j = 5;

        for (int k = 0; k < 2; k++) {
            auto& block = this->terrain_arr_[i[k]][j];

            auto rail = TurnRail("turn_rail", TurnOrientation::NE, block.get_position());
            block.UpdateRail(rail);

            rail = TurnRail("turn_rail", TurnOrientation::NV, block.get_position());
            block.UpdateRail(rail);

            rail = TurnRail("turn_rail", TurnOrientation::SE, block.get_position());
            block.UpdateRail(rail);

            rail = TurnRail("turn_rail", TurnOrientation::SV, block.get_position());
            block.UpdateRail(rail);

            auto srail = StraightRail(TerrainType::Grass, "grass_straight_rail", StraightOrientation::NS,
                                      block.get_position());
            block.UpdateRail(srail);

            srail = StraightRail(TerrainType::Grass, "grass_straight_rail", StraightOrientation::VE,
                                 block.get_position());
            block.UpdateRail(srail);
        }
    }
}

void Tema2::RenderRails() {
    for (auto& row : terrain_arr_) {
        for (auto& block : row) {
            if (!block.is_has_track()) continue;

            for (auto& rail : block.straight_rails()) {
                glm::mat4 model = block.ComputeModelMatrix(rail);
                Mesh* mesh = meshes[rail.mesh_name()];

                if (block.cracked_ == 0) {
                    // old behaviour
                    RenderMesh(mesh, shaders["VertexColor"], model);
                }
                else {
                    // cracked behaviour
                    RenderCrackedRail(mesh, model);
                }
            }

            for (auto& rail : block.turn_rails()) {
                glm::mat4 model = block.ComputeModelMatrix(rail);
                Mesh* mesh = meshes[rail.mesh_name()];

                if (block.cracked_ == 0) { RenderMesh(mesh, shaders["VertexColor"], model); }
                else { RenderCrackedRail(mesh, model); }
            }
        }
    }
}


void Tema2::RenderCrackedRail(Mesh* mesh, const glm::mat4& modelMatrix) {
    Shader* shader = shaders["CrackShader"];
    if (!mesh || !shader || !shader->GetProgramID()) return;

    glUseProgram(shader->program);

    glm::mat4 view = GetSceneCamera()->GetViewMatrix();
    glm::mat4 proj = GetSceneCamera()->GetProjectionMatrix();

    glUniformMatrix4fv(glGetUniformLocation(shader->program, "Model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shader->program, "View"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader->program, "Projection"), 1, GL_FALSE, glm::value_ptr(proj));

    // Set crack amount: 0.0 = no crack, 1.0 = full crack
    float crackAmount = 0.7f; // adjust this value for more/less cracking
    glUniform1f(glGetUniformLocation(shader->program, "crack_amount"), crackAmount);

    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), (int)mesh->indices.size(), GL_UNSIGNED_INT, 0);
}

void Tema2::RenderTrain() {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, train_.position());

    float angle = 0.f;
    switch (train_.get_heading()) {
    case Headings::E:
        angle = 0.f; // default mesh facing E
        break;
    case Headings::V:
        angle = glm::radians(180.f); // turn around
        break;
    case Headings::N:
        angle = glm::radians(90.f);
        break;
    case Headings::S:
        angle = glm::radians(-90.f);
        break;
    }

    modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, 1, 0));
    RenderMesh(meshes["train"], shaders["VertexColor"], modelMatrix);

    // Also render wagon
    modelMatrix = glm::mat4(1);

    angle = 0.f;
    switch (wagon_.get_heading()) {
    case Headings::E:
        angle = 0.f; // default mesh facing E
        break;
    case Headings::V:
        angle = glm::radians(180.f); // turn around
        break;
    case Headings::N:
        angle = glm::radians(90.f);
        break;
    case Headings::S:
        angle = glm::radians(-90.f);
        break;
    }
    modelMatrix = glm::translate(modelMatrix, wagon_.position());
    modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, 1, 0));
    RenderMesh(meshes["wagon"], shaders["VertexColor"], modelMatrix);
}


void Tema2::UpdateTrain(float deltaTimeSeconds) {
    auto& train = this->train_;
    auto& wagon = this->wagon_;

    train_stopped_ = false;

    // Check if any point of any cracked rail is inside train hitbox
    for (auto& rail : all_rails_) {
        if (rail->get_cracked() == 0) continue;

        glm::vec3 p1 = rail->pos1();
        glm::vec3 p2 = rail->pos2();
        glm::vec3 center = (p1 + p2) * 0.5f; // also check center of rail

        if (train.contains_point(p1) || train.contains_point(p2) || train.contains_point(center)) {
            train_stopped_ = true;
            break;
        }
    }


    if (train_stopped_) return;
    // Only if the block it's on is not cracked
    train.add_progress(deltaTimeSeconds * train.speed());
    if (train.progress() >= SIZE_SEGMENT) {
        train.set_progress(0);
        FindNextRail(train.get_current_block());
    }

    wagon.add_progress(deltaTimeSeconds * wagon.speed());
    if (wagon.progress() >= SIZE_SEGMENT) {
        wagon.set_progress(0);
        FindNextRailWagon(wagon.get_current_block());
    }
}

void Tema2::UpdateDraisine() {
    draisine_.UpdatePosition();

    // Calculate block it's on
    int i = static_cast<int>(draisine_.position().x / SIZE_SEGMENT);
    int j = static_cast<int>(draisine_.position().z / SIZE_SEGMENT);

    // Boundary check
    if (i < 0 || i >= TERRAIN_SEGMENTS || j < 0 || j >= TERRAIN_SEGMENTS) {
        cout << "Draisine went off map! Stopping." << endl;
        draisine_.set_speed(0);
        return;
    }

    // Calculate path on rail for every posible rail
    auto& block = terrain_arr_[i][j];

    // Check if current block has rails - if not, we've derailed
    if (!block.is_has_track()) {
        cout << "Draisine derailed! No track at block (" << i << ", " << j << ")" << endl;
        draisine_.set_speed(0);
        return;
    }

    // Reset last intersection if we moved to a different block
    if (draisine_last_intersection_ != nullptr && draisine_last_intersection_ != &block) {
        draisine_last_intersection_ = nullptr;
    }

    // For only one rail in block
    if (block.get_straight_rails().size() + block.get_turn_rails().size() == 1) {
        if (!block.get_straight_rails().empty()) {
            // Verify heading matches rail orientation
            auto& srail = block.get_straight_rails().front();
            StraightOrientation orient = srail.get_orientation();
            Headings heading = draisine_.get_heading();

            bool valid = false;
            if (orient == StraightOrientation::VE && (heading == Headings::E || heading == Headings::V)) {
                valid = true;
            }
            if (orient == StraightOrientation::NS && (heading == Headings::N || heading == Headings::S)) {
                valid = true;
            }

            if (!valid) {
                cout << "Draisine heading doesn't match rail! Derailed." << endl;
                draisine_.set_speed(0);
            }
            return;
        }
        else if (!block.get_turn_rails().empty()) {
            // We can move up until the middle of the rail, then we turn automatically
            auto& trail = block.get_turn_rails().front();
            glm::vec3 rail_center = block.get_position() + glm::vec3(SIZE_SEGMENT / 2.f, 0, SIZE_SEGMENT / 2.f);

            switch (trail.get_orientation()) {
            case TurnOrientation::SE:
                // If we are heading N into the turn and pass the middle we get clamped
                // to the center with a new heading, E
                if (draisine_.get_heading() == Headings::N &&
                    draisine_.position().x >= rail_center.x) {
                    draisine_.SetPosition(rail_center);
                    draisine_.set_heading(Headings::E);
                }
                else if (draisine_.get_heading() == Headings::V &&
                    draisine_.position().z >= rail_center.z) {
                    draisine_.set_position(rail_center);
                    draisine_.set_heading(Headings::S);
                }
                break;

            case TurnOrientation::SV:
                // South-West turn: connects S and V
                if (draisine_.get_heading() == Headings::N &&
                    draisine_.position().x >= rail_center.x) {
                    draisine_.SetPosition(rail_center);
                    draisine_.set_heading(Headings::V);
                }
                else if (draisine_.get_heading() == Headings::E &&
                    draisine_.position().z >= rail_center.z) {
                    draisine_.SetPosition(rail_center);
                    draisine_.set_heading(Headings::S);
                }
                break;

            case TurnOrientation::NE:
                // North-East turn: connects N and E
                if (draisine_.get_heading() == Headings::S &&
                    draisine_.position().x <= rail_center.x) {
                    draisine_.SetPosition(rail_center);
                    draisine_.set_heading(Headings::E);
                }
                else if (draisine_.get_heading() == Headings::V &&
                    draisine_.position().z <= rail_center.z) {
                    draisine_.SetPosition(rail_center);
                    draisine_.set_heading(Headings::N);
                }
                break;

            case TurnOrientation::NV:
                // North-West turn: connects N and V
                if (draisine_.get_heading() == Headings::S &&
                    draisine_.position().x <= rail_center.x) {
                    draisine_.SetPosition(rail_center);
                    draisine_.set_heading(Headings::V);
                }
                else if (draisine_.get_heading() == Headings::E &&
                    draisine_.position().z <= rail_center.z) {
                    draisine_.SetPosition(rail_center);
                    draisine_.set_heading(Headings::N);
                }
                break;
            }
        }
    } else {
        // Handle all intersections
        glm::vec3 rail_center = block.get_position() + glm::vec3(SIZE_SEGMENT / 2.f, 0, SIZE_SEGMENT / 2.f);

        // Skip intersection processing if we already processed this one
        // (but don't return - we still need to let draisine move)
        bool already_processed = (draisine_last_intersection_ == &block);

        // Three-way intersection. All of them have:
        // One NS straight, one SV turn and one NV turn
        // So when on one of those we need to choose left right or straight based on heading
        if (!already_processed && block.get_straight_rails().size() + block.get_turn_rails().size() == 3) {
            // Determine which turn is "left" and which is "right" based on heading
            // For NS straight + SV + NV turns:
            // - Heading N: straight = N, left = V (NV turn), right = not possible (no NE)
            // - Heading S: straight = S, left = not possible (no SE), right = V (SV turn)
            // - Heading E: straight = not possible, left = N (NV), right = S (SV)
            // - Heading V: can't enter this intersection from V side

            Headings heading = draisine_.get_heading();
            bool at_center = false;

            // Check if we've reached the center
            if (heading == Headings::N && draisine_.position().x >= rail_center.x) at_center = true;
            else if (heading == Headings::S && draisine_.position().x <= rail_center.x) at_center = true;
            else if (heading == Headings::E && draisine_.position().z >= rail_center.z) at_center = true;
            else if (heading == Headings::V && draisine_.position().z <= rail_center.z) at_center = true;

            if (at_center) {
                draisine_.SetPosition(rail_center);

                // Determine new heading based on choice and current heading
                Headings new_heading = heading;  // default: go straight

                if (heading == Headings::N) {
                    // Can go straight (N) or left (V via NV turn)
                    if (draisine_choice_ == 0) new_heading = Headings::V;  // left
                    // else stay N (straight)
                }
                else if (heading == Headings::S) {
                    // Can go straight (S) or right (V via SV turn)
                    if (draisine_choice_ == 1) new_heading = Headings::V;  // right
                    // else stay S (straight)
                }
                else if (heading == Headings::E) {
                    // Can go left (N via NV turn) or right (S via SV turn)
                    // No straight E option in this intersection, must turn!
                    if (draisine_choice_ == 0) new_heading = Headings::N;       // left
                    else new_heading = Headings::S;  // right (default if no choice or choice == 1)
                }

                draisine_.set_heading(new_heading);
                draisine_choice_ = -1;  // Reset choice after use
                draisine_last_intersection_ = &block;  // Mark as processed
            }
        }

        // Four-way intersection. All of them have:
        // Two straights (NS and VE) and four turns (NE, NV, SE, SV)
        if (!already_processed && block.get_straight_rails().size() + block.get_turn_rails().size() == 6) {
            Headings heading = draisine_.get_heading();
            bool at_center = false;

            // Check if we've reached the center
            if (heading == Headings::N && draisine_.position().x >= rail_center.x) at_center = true;
            else if (heading == Headings::S && draisine_.position().x <= rail_center.x) at_center = true;
            else if (heading == Headings::E && draisine_.position().z >= rail_center.z) at_center = true;
            else if (heading == Headings::V && draisine_.position().z <= rail_center.z) at_center = true;

            if (at_center) {
                draisine_.SetPosition(rail_center);

                // Determine new heading based on choice and current heading
                Headings new_heading = heading;  // default: go straight

                if (heading == Headings::N) {
                    // Straight = N, Left = V, Right = E
                    if (draisine_choice_ == 0) new_heading = Headings::V;       // left (NV turn)
                    else if (draisine_choice_ == 1) new_heading = Headings::E;  // right (NE turn)
                    // else stay N (straight)
                }
                else if (heading == Headings::S) {
                    // Straight = S, Left = E, Right = V
                    if (draisine_choice_ == 0) new_heading = Headings::E;       // left (SE turn)
                    else if (draisine_choice_ == 1) new_heading = Headings::V;  // right (SV turn)
                    // else stay S (straight)
                }
                else if (heading == Headings::E) {
                    // Straight = E, Left = N, Right = S
                    if (draisine_choice_ == 0) new_heading = Headings::N;       // left (NE turn)
                    else if (draisine_choice_ == 1) new_heading = Headings::S;  // right (SE turn)
                    // else stay E (straight)
                }
                else if (heading == Headings::V) {
                    // Straight = V, Left = S, Right = N
                    if (draisine_choice_ == 0) new_heading = Headings::S;       // left (SV turn)
                    else if (draisine_choice_ == 1) new_heading = Headings::N;  // right (NV turn)
                    // else stay V (straight)
                }

                draisine_.set_heading(new_heading);
                draisine_choice_ = -1;  // Reset choice after use
                draisine_last_intersection_ = &block;  // Mark as processed
            }
        }
    }
}

void Tema2::UpdateNeighBlocksWithRails() {
    // Iterate through all blocks and check neighs
    for (int i = 0; i < TERRAIN_SEGMENTS; i++) {
        for (int j = 0; j < TERRAIN_SEGMENTS; j++) {
            auto& block = this->terrain_arr_[i][j];

            // Check in a square
            if (block.is_has_track()) {
                // N
                int ni = i + 1;
                // Get block
                auto& neigh_block_N = this->terrain_arr_[ni][j];
                if (neigh_block_N.is_has_track())
                    block.neigh_N = &neigh_block_N;

                // S
                ni = i - 1;
                // Get block
                auto& neigh_block_S = this->terrain_arr_[ni][j];
                if (neigh_block_S.is_has_track())
                    block.neigh_S = &neigh_block_S;

                // E
                int nj = j + 1;
                // Get block
                auto& neigh_block_E = this->terrain_arr_[i][nj];
                if (neigh_block_E.is_has_track())
                    block.neigh_E = &neigh_block_E;

                // V
                nj = j - 1;
                // Get block
                auto& neigh_block_V = this->terrain_arr_[i][nj];
                if (neigh_block_V.is_has_track())
                    block.neigh_V = &neigh_block_V;
            }
        }
    }
}

void Tema2::FindNextRail(Block* current_block) {
    Block* next_block = current_block;

    switch (train_.get_heading()) {
    case Headings::N: if (current_block->neigh_N) next_block = current_block->neigh_N;
        break;
    case Headings::S: if (current_block->neigh_S) next_block = current_block->neigh_S;
        break;
    case Headings::E: if (current_block->neigh_E) next_block = current_block->neigh_E;
        break;
    case Headings::V: if (current_block->neigh_V) next_block = current_block->neigh_V;
        break;
    }

    StraightOrientation needed_straight;
    std::pair<TurnOrientation, TurnOrientation> needed_turn;
    switch (train_.get_heading()) {
    case Headings::N: needed_straight = StraightOrientation::NS;
        needed_turn = {TurnOrientation::SV, TurnOrientation::SE};
        break;
    case Headings::S: needed_straight = StraightOrientation::NS;
        needed_turn = {TurnOrientation::NE, TurnOrientation::NV};
        break;
    case Headings::E: needed_straight = StraightOrientation::VE;
        needed_turn = {TurnOrientation::SV, TurnOrientation::NV};
        break;
    case Headings::V: needed_straight = StraightOrientation::VE;
        needed_turn = {TurnOrientation::NE, TurnOrientation::SE};
        break;
    }

    std::vector<Rail*> all_rails;

    for (auto& srail : next_block->straight_rails())
        if (srail.get_orientation() == needed_straight) all_rails.push_back(&srail);

    for (auto& trail : next_block->turn_rails())
        if (trail.get_orientation() == needed_turn.first ||
            trail.get_orientation() == needed_turn.second)
            all_rails.push_back(&trail);

    int size = (int)all_rails.size();
    if (size == 0) return; // nowhere to go → bail safely

    int idx = rand() % size;
    Rail* next_rail = all_rails[idx];

    next_path_choice_.push(idx);

    if (next_rail->type() == Type::Straight)
        train_.ChangeRail(static_cast<StraightRail&>(*next_rail), next_block);
    else if (next_rail->type() == Type::Turn)
        train_.ChangeRail(static_cast<TurnRail&>(*next_rail), next_block);
}


void Tema2::FindNextRailWagon(Block* current_block) {
    Block* next_block = current_block;

    switch (wagon_.get_heading()) {
    case Headings::N: if (current_block->neigh_N) next_block = current_block->neigh_N;
        break;
    case Headings::S: if (current_block->neigh_S) next_block = current_block->neigh_S;
        break;
    case Headings::E: if (current_block->neigh_E) next_block = current_block->neigh_E;
        break;
    case Headings::V: if (current_block->neigh_V) next_block = current_block->neigh_V;
        break;
    }

    StraightOrientation needed_straight;
    std::pair<TurnOrientation, TurnOrientation> needed_turn;
    switch (wagon_.get_heading()) {
    case Headings::N: needed_straight = StraightOrientation::NS;
        needed_turn = {TurnOrientation::SV, TurnOrientation::SE};
        break;
    case Headings::S: needed_straight = StraightOrientation::NS;
        needed_turn = {TurnOrientation::NE, TurnOrientation::NV};
        break;
    case Headings::E: needed_straight = StraightOrientation::VE;
        needed_turn = {TurnOrientation::SV, TurnOrientation::NV};
        break;
    case Headings::V: needed_straight = StraightOrientation::VE;
        needed_turn = {TurnOrientation::NE, TurnOrientation::SE};
        break;
    }

    std::vector<Rail*> all_rails;

    for (auto& srail : next_block->straight_rails())
        if (srail.get_orientation() == needed_straight) all_rails.push_back(&srail);

    for (auto& trail : next_block->turn_rails())
        if (trail.get_orientation() == needed_turn.first ||
            trail.get_orientation() == needed_turn.second)
            all_rails.push_back(&trail);

    int size = (int)all_rails.size();
    if (size == 0) return;

    int idx;

    if (wagon_choice_buffer_ == -1) { idx = 0; }
    else {
        idx = wagon_choice_buffer_;
        if (idx < 0 || idx >= size) idx %= size;
    }

    Rail* next_rail = all_rails[idx];

    if (next_rail->type() == Type::Straight)
        wagon_.ChangeRail(static_cast<StraightRail&>(*next_rail), next_block);
    else if (next_rail->type() == Type::Turn)
        wagon_.ChangeRail(static_cast<TurnRail&>(*next_rail), next_block);

    if (!next_path_choice_.empty()) {
        wagon_choice_buffer_ = next_path_choice_.front();
        next_path_choice_.pop();
    }
}

void Tema2::CrackBlock() {
    int r = rand() % 100;
    if (r >= 30) return;

    std::vector<Block*> candidates;

    for (auto& row : terrain_arr_) {
        for (auto& block : row) { if (block.is_has_track() && block.cracked_ == 0) { candidates.push_back(&block); } }
    }

    if (candidates.empty()) return;

    int idx = rand() % candidates.size();
    Block* chosen = candidates[idx];

    // crack it
    chosen->set_cracked(1);
}

void Tema2::AddAllRailsToList() {
    for (auto& row : terrain_arr_) {
        for (auto& block : row) {
            for (auto& rail : block.straight_rails()) { all_rails_.push_back(&rail); }
            for (auto& rail : block.turn_rails()) { all_rails_.push_back(&rail); }
        }
    }
}

void Tema2::RenderDraisine() {
    // Get draisine
    Draisine draisine = this->draisine_;

    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, draisine.position());

    float angle = 0.f;
    switch (draisine.get_heading()) {
    case Headings::E:
        angle = 0.f; // default mesh facing E
        break;
    case Headings::V:
        angle = glm::radians(180.f); // turn around
        break;
    case Headings::N:
        angle = glm::radians(90.f);
        break;
    case Headings::S:
        angle = glm::radians(-90.f);
        break;
    }

    modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, 1, 0));

    RenderMesh(meshes["draisine_body"], shaders["VertexColor"], modelMatrix);

    float swing_angle = sin(handle_rotation_time_ * 3.0f) * glm::radians(30.0f);

    glm::mat4 handleModel = glm::mat4(1);
    handleModel = glm::translate(handleModel, draisine.position());
    handleModel = glm::rotate(handleModel, angle, glm::vec3(0, 1, 0));
    handleModel = glm::translate(handleModel, glm::vec3(0, 2, 0));
    handleModel = glm::rotate(handleModel, swing_angle, glm::vec3(1, 0, 0));
    RenderMesh(meshes["draisine_handle"], shaders["VertexColor"], handleModel);
}

void Tema2::UpdateTPSCamera() {
    gfxc::Camera* cam = GetSceneCamera();

    const float DIST = 5.0f;
    const float HEIGHT = 3.0f;

    glm::vec3 target = draisine_.position();

    // Forward direction the draisine is facing
    glm::vec3 forward;
    switch (draisine_.get_heading()) {
    case Headings::E: forward = glm::vec3(0, 0, 1);
        break; // East = +Z
    case Headings::V: forward = glm::vec3(0, 0, -1);
        break; // West = -Z
    case Headings::N: forward = glm::vec3(1, 0, 0);
        break; // North = +X
    case Headings::S: forward = glm::vec3(-1, 0, 0);
        break; // South = -X
    }

    glm::vec3 camPos = target - forward * DIST + glm::vec3(0, HEIGHT, 0);
    cam->SetPosition(camPos);

    glm::vec3 lookAt = target + glm::vec3(0, 0.5f, 0);

    glm::vec3 dir = glm::normalize(lookAt - camPos);
    glm::vec3 worldUp = glm::vec3(0, 1, 0);
    glm::vec3 right = glm::normalize(glm::cross(worldUp, -dir));
    glm::vec3 up = glm::cross(-dir, right);

    glm::mat3 rotMat(right, up, -dir);
    glm::quat rotation = glm::quat_cast(rotMat);
    cam->SetRotation(rotation);
}

void Tema2::CheckRepair() {
    int i = static_cast<int>(draisine_.position().x / SIZE_SEGMENT);
    int j = static_cast<int>(draisine_.position().z / SIZE_SEGMENT);

    if (i < 0 || i >= TERRAIN_SEGMENTS || j < 0 || j >= TERRAIN_SEGMENTS) return;

    std::vector<Block*> blocks_to_check;
    blocks_to_check.push_back(&terrain_arr_[i][j]);

    Block& current = terrain_arr_[i][j];
    if (current.neigh_N) blocks_to_check.push_back(current.neigh_N);
    if (current.neigh_S) blocks_to_check.push_back(current.neigh_S);
    if (current.neigh_E) blocks_to_check.push_back(current.neigh_E);
    if (current.neigh_V) blocks_to_check.push_back(current.neigh_V);

    for (Block* block : blocks_to_check) {
        if (!block->is_has_track() || block->cracked_ == 0) continue;

        bool should_repair = false;

        for (auto& rail : block->straight_rails()) {
            if (draisine_.contains_point(rail.pos1()) || draisine_.contains_point(rail.pos2())) {
                should_repair = true;
                break;
            }
        }

        if (!should_repair) {
            for (auto& rail : block->turn_rails()) {
                if (draisine_.contains_point(rail.pos1()) || draisine_.contains_point(rail.pos2())) {
                    should_repair = true;
                    break;
                }
            }
        }

        if (should_repair) {
            block->set_cracked(false);
            for (auto& rail : block->straight_rails()) rail.set_cracked(false);
            for (auto& rail : block->turn_rails()) rail.set_cracked(false);
        }
    }
}

void Tema2::RenderGameOver() {
    const glm::ivec2 resolution = window->props.resolution;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    textRenderer->RenderText("GAME OVER", resolution.x / 2.0f - 150.0f, resolution.y / 2.0f + 50.0f, 2.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    textRenderer->RenderText("Score: " + to_string(this->score), resolution.x / 2.0f - 100.0f, resolution.y / 2.0f - 50.0f, 1.5f, glm::vec3(1.0f, 1.0f, 1.0f));
}


#include "Tema2.h"

#include <iostream>

#include "Objects.h"
#include "Wagon.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2() {}


Tema2::~Tema2()
= default;


void Tema2::Init() {
    // Load meshes into GPU
    LoadMeshes();

    // Create terrain
    CreateTerrain();

    // Set head rail
    {
        int i = 10;
        int j = 6;
        auto& block = terrain_arr_[i][j];

        auto rail = StraightRail(TerrainType::Grass, "grass_straight_rail",
                                 StraightOrientation::VE, block.get_position());
        block.UpdateRail(rail);

        rail_start_ = block;

        // Set train
        train_ = Train(static_cast<Rail>(block.get_straight_rails().front()), block.get_position(), &block);
    }


    // Create rest of rails
    CreateRails();
    UpdateNeighBlocksWithRails();

    // Init wagon
    {
        int i = 10;
        int j = 5;
        auto& block_wagon = terrain_arr_[i][j];

        auto& trail = block_wagon.get_turn_rails().front();

        wagon_start_ = block_wagon;

        wagon_ = Wagon(static_cast<Rail>(trail), block_wagon.get_position(), &block_wagon);
    }

    {
        Shader* shader = new Shader("CrackShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir,
                                    SOURCE_PATH::M1, "tema2", "shaders", "CrackVS.glsl"),
                          GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir,
                                    SOURCE_PATH::M1, "tema2", "shaders", "CrackFS.glsl"),
                          GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // Create draisine
    {
        int i = 3;
        int j = 3;

        auto& block_draisine = terrain_arr_[i][j];
        draisine_ = Draisine(static_cast<Rail>(block_draisine.get_straight_rails().front()),
                             block_draisine.get_position(), &block_draisine);
    }

    // Text renderer
    const glm::ivec2 resolution = window->props.resolution;
    textRenderer = new gfxc::TextRenderer(window->props.selfDir, resolution.x, resolution.y);

    // Load a font
    textRenderer->Load(PATH_JOIN(window->props.selfDir, "assets", "fonts", "Hack-Bold.ttf"), 32);

    AddAllRailsToList();
}


void Tema2::FrameStart() {}


void Tema2::Update(float deltaTimeSeconds) {
    const glm::ivec2 resolution = window->props.resolution;
    glm::vec3 color_sky_rgb = COLOR_SKY;
    glClearColor(color_sky_rgb.x, color_sky_rgb.y, color_sky_rgb.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, resolution.x, resolution.y);

    if (game_over_) {
        RenderGameOver();
        return;
    }

    RenderTerrain();
    RenderStations();
    RenderRails();
    RenderTrain();
    RenderDraisine();

    UpdateTrain(deltaTimeSeconds);
    UpdateDraisine();

    crack_timer_ += deltaTimeSeconds;

    if (crack_timer_ >= 1.0f) {
        crack_timer_ = 0.0f;
        CrackBlock();
    }

    time_elapsed_ += deltaTimeSeconds;
    if (time_elapsed_ >= 1.0f) {
        score += 1;
        time_elapsed_ = 0.0f;
    }
    textRenderer->RenderText("Score: " + to_string(score), 10.0f, 10.0f, 1.5f, glm::vec3(1, 1, 1));

    if (!train_stopped_)
        time_since_stop_ = 0;
    else {
        time_since_stop_ += deltaTimeSeconds;
        textRenderer->RenderText("Train stopped for " + to_string(static_cast<int>(time_since_stop_)) + "s",
                                 10.0f, 50.0f, 1.5f, glm::vec3(1, 0, 0));
        if (time_since_stop_ >= 5) { game_over_ = true; }
    }

    handle_rotation_time_ += deltaTimeSeconds;

    UpdateTPSCamera();
}


void Tema2::FrameEnd() {}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods) {
    if (window->KeyHold(GLFW_KEY_W)) { draisine_.Accelerate(deltaTime); }
    if (window->KeyHold(GLFW_KEY_S)) { draisine_.Deccelerate(deltaTime); }
}


void Tema2::OnKeyPress(int key, int mods) {
    if (key == GLFW_KEY_A) { draisine_choice_ = 0; }
    if (key == GLFW_KEY_D) { draisine_choice_ = 1; }
    if (key == GLFW_KEY_F) { CheckRepair(); }
}


void Tema2::OnKeyRelease(int key, int mods) {
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
    // Add mouse move event
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {
    // Treat mouse scroll event
}


void Tema2::OnWindowResize(int width, int height) {
    // Treat window resize event
}

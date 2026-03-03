//
// Created by patur on 10/30/2025.
//

#include <iostream>
#include <algorithm>
#include <random>

#include "Tema1.h"
#include "objects2D.h"
#include "constants.h"
#include "assimp/postprocess.h"
#include "utils/text_utils.h"

using namespace std;
using namespace m1;

Tema1::Tema1()
{
    // Init logic space
    logicSpace = {0, 0, LOGIC_SPACE_W, LOGIC_SPACE_H};

    // Init view space
    glm::ivec2 resolution = window->GetResolution();
    viewSpace = {0, 0, resolution.x, resolution.y};

    // Init matrixes
    visMatrix = glm::mat3(1);
    modelMatrix = glm::mat3(1);

    // Menu on by default
    menu = true;

    // Game over false
    gameOver = false;

    // Tiles placed
    tilesPlaced = 0;

    // Grid Data init
    editBlocks.resize(EDIT_MATRIX_H);

    for (int i = 0; i < EDIT_MATRIX_H; i++) {
        editBlocks[i].reserve(EDIT_MATRIX_W);
        for (int j = 0; j < EDIT_MATRIX_W; j++) {
            editBlocks[i].emplace_back(glm::vec3(EDIT_BLOCK_OFFS_X + j * EDIT_BLOCK_LEN,
                EDIT_BLOCK_OFFS_Y + i * EDIT_BLOCK_LEN, 0), i, j);
        }
    }

    // Set connection false
    this->connected = false;

    // Player ship
    this->playerShip = PlayerShip();

    // Lives
    this->lives = 1;

    // Wave
    this->wave = 1;

    // Text renderer
    textRenderer = new gfxc::TextRenderer(window->props.selfDir, resolution.x, resolution.y
    );

    // Load a font
    textRenderer->Load(PATH_JOIN(window->props.selfDir, "assets", "fonts", "Hack-Bold.ttf"), 32);
}


Tema1::~Tema1()
= default;


void Tema1::Init()
{
    // Set up top-down camera on Z-axis
    glm::ivec2 resolution = window->GetResolution();

    auto camera = GetSceneCamera();

    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, -1.0f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();

    glDisable(GL_DEPTH_TEST);

    // Disable input
    GetCameraInput()->SetActive(false);

    // Load mesnu meshes into GPU
    LoadMenuMeshes();

    // Load game meshes
    LoadGameMeshes();
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Tema1::Update(float deltaTimeSeconds) {
    // Also keep delta time as class variable
    this->deltaTime = deltaTimeSeconds;

    // Add delta time for cooldowns
    timeSinceLastShot += deltaTimeSeconds;
    timeSinceLastShotEgg += deltaTimeSeconds;

    // Get resolution
    glm::ivec2 resolution = window->GetResolution();

    // Set up viewspace
    viewSpace = {0, 0, resolution.x, resolution.y};

    // For menu, it's default, for game we zoom out 2 times as default
    if (menu)
        SetViewportAreaMenu(viewSpace, glm::vec3(0.f), true);
    else
        SetViewportAreaGame(viewSpace, glm::vec3(0.f), true);

    // Get the scaling matrix from logic space to view space
    visMatrix = VisualizationTransf2DUnif(logicSpace, viewSpace);

    // Update chicken time
    if (!menu) chickenTime += deltaTimeSeconds;

    // Check lives counter
    if (this->lives <= 0 || (wave == 3 && this->chickensAlive == 0))
        gameOver = true;

    // Render scene
    if (menu)
        RenderMenu();
    else if (!gameOver)
        RenderGame();
    else
        RenderGameOver();

    // Update location of existing projectiles
    for (auto &proj : this->cannonProjectiles) {
        proj.addMove(deltaTimeSeconds, UP_DIRECTION);
    }

    for (auto &proj : this->chickenProjectiles) {
        proj.addMove(deltaTimeSeconds, DOWN_DIRECTION);
    }

    // Have a chance per chicken to shoot every one second
    if (timeSinceLastShotEgg > shootCooldownEgg) {
        ShootEgg();
        timeSinceLastShotEgg = 0;
    }

    // Check hitboxes
    CheckCannonHit();
    CheckEggHit();
    CheckChickens();
}



void Tema1::FrameEnd() {
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    // Ship movement
    if (window->KeyHold(GLFW_KEY_UP)) {
        playerShip.MoveUp(deltaTime);
    }
    if (window->KeyHold(GLFW_KEY_DOWN)) {
        playerShip.MoveDown(deltaTime);
    }
    if (window->KeyHold(GLFW_KEY_LEFT)) {
        playerShip.MoveLeft(deltaTime);
    }
    if (window->KeyHold(GLFW_KEY_RIGHT)) {
        playerShip.MoveRight(deltaTime);
    }
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Shoot cannons with space
    if (key == GLFW_KEY_SPACE && timeSinceLastShot >= shootCooldown) {
        ShootCannons();
        timeSinceLastShot = 0;
    }
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Convert to logic space coords
    glm::vec2 pos = WindowToLogic(mouseX, mouseY);

    // Keep them as class variables
    this->mouseX = pos.x;
    this->mouseY = pos.y;
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Convert to logic space coords
    glm::vec2 pos = WindowToLogic(mouseX, mouseY);

    const bool isRightButton = IS_BIT_SET(button, GLFW_MOUSE_BUTTON_RIGHT);
    const bool isMiddleButton = IS_BIT_SET(button, GLFW_MOUSE_BUTTON_MIDDLE);

    // Left button
    if (button == 1) {
        // Check interactable blocks
        for (auto &pair : this->interactableMeshes) {
            // Check start button
            auto &im = pair.second;
            if (im.getName() == "startButton" && menu) {
                if (this->tilesPlaced > 0 && tilesPlaced <= 10 && this->connected && im.isInside(pos.x, pos.y)) {
                    // Init player ship
                    InitGame();

                    // Switch to gamemode
                    this->menu = false;
                }
            // Rest of meshes
            } else {
                if (im.isInside(pos.x, pos.y)) {
                    im.set_is_clicked(true);
                }
            }
        }
    }

    // Right button
    if (button == 2) {
        for (int i = 0; i < EDIT_MATRIX_H; i++) {
            for (int j = 0; j < EDIT_MATRIX_W; j++) {
                EditBlockData &eb = this->editBlocks[i][j];
                // Check if mouse is inside a taken block to delete it
                if (eb.isInside(pos.x, pos.y) && eb.taken1()) {
                    eb.set_taken(false);
                    this->tilesPlaced--;
                    this->connected = this->UpdateConnected();
                    RemoveObstructed(eb);
                }
            }
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Mouse coords from to window to logic space
    glm::vec2 pos = WindowToLogic(mouseX, mouseY);

    // Drop onto grid logic
    for (auto &pair : this->interactableMeshes) {
        auto &im = pair.second;
        if (im.is_clicked()) {
            for (int i = 0; i < EDIT_MATRIX_H; i++) {
                for (int j = 0; j < EDIT_MATRIX_W; j++) {
                    auto &eb = this->editBlocks[i][j];
                    if (eb.isInside(pos.x, pos.y) && !eb.taken1() && !eb.isObstructed() &&
                        eb.canPlace(im, this->editBlocks)) {

                        eb.set_taken(true);
                        eb.set_mesh_name(im.getName());
                        AddObstructed(eb);

                        this->tilesPlaced++;
                        this->connected = UpdateConnected();
                    }
                }
            }
            im.set_is_clicked(false);
        }
    }
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    // Treat mouse scroll event
}


void Tema1::OnWindowResize(int width, int height)
{
    // Treat window resize event
}

// Uniform 2D visualization matrix (same scale factor on x and y axes)
glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace &logicSpace, const ViewportSpace &viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}

void Tema1::SetViewportAreaMenu(const ViewportSpace &viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width),
        (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}

void Tema1::SetViewportAreaGame(const ViewportSpace &viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width) * 2.f,
        (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height) * 2.f, 0.1f, 400);
    GetSceneCamera()->Update();
}

void Tema1::LoadMenuMeshes() {
    // Create red rectangle around the scene
    Mesh *rect = objects2D::CreateRectangle("border", glm::vec3(BORDER_PAD, BORDER_PAD, 0.f),
        LOGIC_SPACE_W - BORDER_PAD, LOGIC_SPACE_H - 2 * BORDER_PAD, glm::vec3(1.f, 0.f, 0.f), false);
    AddMeshToList(rect);

    // Create red rectangles on the left
    rect = objects2D::CreateRectangle("blockBorder", glm::vec3(BORDER_PAD, BORDER_PAD, 0.f),
        (float)(LOGIC_SPACE_W - 2 * BORDER_PAD) / 5, (float)(LOGIC_SPACE_H - 2 * BORDER_PAD) / 3,
        glm::vec3(1.f, 0.f, 0.f), false);
    AddMeshToList(rect);

    // Create blue border, we make it fit the matrix later
    glm::vec3 editWindowBLCorner = glm::vec3((float)(BORDER_PAD + (LOGIC_SPACE_W - 2 * BORDER_PAD) / 5), BORDER_PAD, 0);

    rect = objects2D::CreateRectangle("editBorder",editWindowBLCorner, EDIT_BLOCK_LEN * (EDIT_MATRIX_W + 1),
        EDIT_BLOCK_LEN * (EDIT_MATRIX_H + 1), glm::vec3(0.f, 0.f, 1.f), false);
    AddMeshToList(rect);

    // Create edit squares for matrix
    Mesh *square = objects2D::CreateSquare("editSquare", glm::vec3(0, 0, 0), EDIT_BLOCK_LEN,
        glm::vec3(72.f, 130.f, 255.f) / 255.f, true);
    AddMeshToList(square);

    // Create squares for tiles left to place
    square = objects2D::CreateSquare("tilesLeftIndicator", editWindowBLCorner, EDIT_BLOCK_LEN,
        glm::vec3(39.f, 156.f, 2.f) / 255.f, true);
    AddMeshToList(square);

    // Load start button mesh
    Mesh *startButton = objects2D::CreateStartButton("startButton", glm::vec3(0, 0, 0), EDIT_BLOCK_LEN,
        glm::vec3(39.f, 156.f, 2.f) / 255.f, true);
    AddMeshToList(startButton);
    // Add to clickables
    glm::vec3 corner = glm::vec3(80 + 10 * (EDIT_BLOCK_LEN + TILES_PLACED_IND_OFF)
        + BORDER_PAD + CHOOSE_WINDOW_W, BORDER_PAD + 920, 0);
    AddMeshToInteractables("startButton", corner, EDIT_BLOCK_LEN, EDIT_BLOCK_LEN);

    // Load red start button mesh
    startButton = objects2D::CreateStartButton("startButtonRed", glm::vec3(0, 0, 0), EDIT_BLOCK_LEN,
        glm::vec3(1, 0, 0), true);
    AddMeshToList(startButton);

    // Gray tile mesh
    float chooseBlockWindowWidth = BORDER_PAD + ((float)(LOGIC_SPACE_W - 2 * BORDER_PAD) / 5);
    float chooseBlockWindowHeight = BORDER_PAD + (float)(LOGIC_SPACE_H - 2 * BORDER_PAD) / 3;
    glm::vec3 center = glm::vec3(chooseBlockWindowWidth / 2, chooseBlockWindowHeight / 2, 0);

    Mesh *buildingTile = objects2D::CreateTile("buildingTile", glm::vec3(0, 0, 1), EDIT_BLOCK_LEN,
        glm::vec3(128.f, 128.f, 128.f) / 255.f, true);
    AddMeshToList(buildingTile);
    // Add to clickables
    corner = glm::vec3(BORDER_PAD + CHOOSE_WINDOW_W / 2.f - EDIT_BLOCK_LEN / 2.f,
        BORDER_PAD + CHOOSE_WINDOW_H / 2.f - EDIT_BLOCK_LEN / 2.f, 0);
    AddMeshToInteractables("buildingTile", corner, EDIT_BLOCK_LEN, EDIT_BLOCK_LEN);

    // Thruster Mesh
    Mesh *thruster = objects2D::CreateThruster("thruster", glm::vec3(0, 0, 1), EDIT_BLOCK_LEN,
        glm::vec3(255, 0, 0) / 255.f, true);
    AddMeshToList(thruster);
    // Add to clickables
    corner = glm::vec3(BORDER_PAD + CHOOSE_WINDOW_W / 2.f - EDIT_BLOCK_LEN / 2.f,
        BORDER_PAD + CHOOSE_WINDOW_H * 1.5, 0);
    AddMeshToInteractables("thruster", corner, EDIT_BLOCK_LEN, 2 * EDIT_BLOCK_LEN);

    // Cannon Mesh
    Mesh *canon = objects2D::CreateCannon("cannon", glm::vec3(0, 0, 1));
    AddMeshToList(canon);
    // Add to clickables
    corner = glm::vec3(BORDER_PAD + CHOOSE_WINDOW_W / 2.f - EDIT_BLOCK_LEN / 2.f, BORDER_PAD + CHOOSE_WINDOW_H * 2.5 - EDIT_BLOCK_LEN * 1.5f, 0);
    AddMeshToInteractables("cannon", corner, EDIT_BLOCK_LEN, 3 * EDIT_BLOCK_LEN);

    // Debug white square
    square = objects2D::CreateSquare("whiteSquare", glm::vec3(0, 0, 0), EDIT_BLOCK_LEN, glm::vec3(1, 1, 1), false);
    AddMeshToList(square);
}

void Tema1::RenderMenu() {
    // Render border
    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["border"], shaders["VertexColor"], visMatrix * modelMatrix);

    // Render block borders on the left
    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["blockBorder"], shaders["VertexColor"], visMatrix * modelMatrix);

    // 2nd
    modelMatrix = glm::mat3(1);
    modelMatrix *= Transformations::Translate(0.f, (float)(LOGIC_SPACE_H - 2 * BORDER_PAD) / 3);
    RenderMesh2D(meshes["blockBorder"], shaders["VertexColor"], visMatrix * modelMatrix);

    // 3rd
    modelMatrix *= Transformations::Translate(0.f, (float)(LOGIC_SPACE_H - 2 * BORDER_PAD) / 3);
    RenderMesh2D(meshes["blockBorder"], shaders["VertexColor"], visMatrix * modelMatrix);

    // Render edit border
    modelMatrix = glm::mat3(1);
    modelMatrix *= Transformations::Translate(45, 60);
    RenderMesh2D(meshes["editBorder"], shaders["VertexColor"], visMatrix * modelMatrix);

    // Render matrix squares
    for (int i = 0; i < EDIT_MATRIX_H; i++) {
        glm::mat3 start = EDIT_BLOCK_MAT_OFFS * Transformations::Translate(0, i * EDIT_BLOCK_LEN);

        for (int j = 0; j < EDIT_MATRIX_W; j++) {
            modelMatrix = start;
            modelMatrix *= Transformations::Translate(j * EDIT_BLOCK_LEN, 0);

            modelMatrix *= Transformations::Translate(EDIT_BLOCK_LEN / 2.f, EDIT_BLOCK_LEN / 2.f);
            modelMatrix *= Transformations::Scale(0.7f, 0.7f);
            modelMatrix *= Transformations::Translate(-EDIT_BLOCK_LEN / 2.f, -EDIT_BLOCK_LEN / 2.f);

            if (!this->editBlocks[i][j].isObstructed())
                RenderMesh2D(meshes["editSquare"], shaders["VertexColor"], visMatrix * modelMatrix);
        }
    }

    // Render tiles left to place indicator
    modelMatrix = Transformations::Translate(80, 920);
    for (int i = 0; i < 10 - tilesPlaced; i++) {
        RenderMesh2D(meshes["tilesLeftIndicator"], shaders["VertexColor"], visMatrix * modelMatrix);
        modelMatrix *= Transformations::Translate(EDIT_BLOCK_LEN + TILES_PLACED_IND_OFF, 0);
    }

    // Render start button
    modelMatrix = Transformations::Translate(80 + 10 * (EDIT_BLOCK_LEN + TILES_PLACED_IND_OFF)
        + BORDER_PAD + CHOOSE_WINDOW_W, BORDER_PAD + 920);
    if (tilesPlaced <= 10 && this->connected) {
        RenderMesh2D(meshes["startButton"], shaders["VertexColor"], visMatrix * modelMatrix);
    } else {
        RenderMesh2D(meshes["startButtonRed"], shaders["VertexColor"], visMatrix * modelMatrix);
    }

    // Render building tiles
    // Gray tile
    modelMatrix = Transformations::Translate(BORDER_PAD + CHOOSE_WINDOW_W / 2.f, BORDER_PAD + CHOOSE_WINDOW_H / 2.f);
    modelMatrix *= Transformations::Translate(-EDIT_BLOCK_LEN / 2.f, -EDIT_BLOCK_LEN / 2.f);
    RenderMesh2D(meshes["buildingTile"], shaders["VertexColor"], visMatrix * modelMatrix);
    // Update its position in interactables
    this->interactableMeshes.at("buildingTile").setModelMatrix(modelMatrix);

    // Thruster
    modelMatrix = glm::mat3(1);
    modelMatrix *= Transformations::Translate(BORDER_PAD + CHOOSE_WINDOW_W / 2.f, BORDER_PAD + 1.5f * CHOOSE_WINDOW_H);
    modelMatrix *= Transformations::Translate(-EDIT_BLOCK_LEN / 2.f, 0);
    RenderMesh2D(meshes["thruster"], shaders["VertexColor"], visMatrix * modelMatrix);
    // Update its position in interactables
    this->interactableMeshes.at("thruster").setModelMatrix(modelMatrix);

    // Cannon
    modelMatrix = glm::mat3(1);
    modelMatrix *= Transformations::Translate(BORDER_PAD + CHOOSE_WINDOW_W / 2.f, BORDER_PAD + CHOOSE_WINDOW_H * 2.5f);
    modelMatrix *= Transformations::Translate(-EDIT_BLOCK_LEN / 2.f, -EDIT_BLOCK_LEN * 1.5f);
    RenderMesh2D(meshes["cannon"], shaders["VertexColor"], visMatrix * modelMatrix);
    // Update its position in interactables
    this->interactableMeshes.at("cannon").setModelMatrix(modelMatrix);

    // Render placed blocks
    for (int i = 0; i < EDIT_MATRIX_H; i++) {
        for (int j = 0; j < EDIT_MATRIX_W; j++) {
            auto eb = this->editBlocks[i][j];
            if (eb.taken1()) {
                modelMatrix = glm::mat3(1);
                // Take mesh to corner
                modelMatrix *= Transformations::Translate(eb.corner1().x, eb.corner1().y);
                RenderMesh2D(meshes[eb.mesh_name()], shaders["VertexColor"], visMatrix * modelMatrix);
            }
        }
    }

    // Render dragged blocks
    for (auto &pair : this->interactableMeshes) {
        auto &im = pair.second;
        if (im.is_clicked()) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= Transformations::Translate(mouseX - im.getCenter().x, mouseY - im.getCenter().y);
            modelMatrix *= im.getModelMatrix();

            RenderMesh2D(meshes[im.getName()], shaders["VertexColor"], visMatrix * modelMatrix);
        }
    }
}

glm::vec2 Tema1::WindowToLogic(int x, int y) {
    const glm::ivec2 framebufferRes = window->props.resolution;
    const float scaleFactor = window->props.scaleFactor;

    const float framebufferX = x * scaleFactor;
    const float framebufferY = y * scaleFactor;

    float logicX = (framebufferX - visMatrix[2][0]) / visMatrix[0][0];
    float logicY = (framebufferRes.y - framebufferY - visMatrix[2][1]) / visMatrix[1][1];
    return glm::vec2(logicX, logicY);
}

void Tema1::AddMeshToInteractables(const std::string& name, glm::vec3 corner, float width, float height) {
    // Add a mesh to the interactables list
    this->interactableMeshes.insert({ name, InteractableMesh(name, corner, width, height) });
}

void Tema1::AddObstructed(EditBlockData &eb) {
    // Obstructed means it's not taken by an object, but you still can't place
    // anything there. Cannons and trhusters add obstructions above or below.

    std::string name = eb.mesh_name();

    if (name == "buildingTile") {
        // Just the one block
        eb.setObstructed(true);
    } else if (name == "thruster") {
        // Add obstructions below
        int m = eb.getPos().x;
        int n = eb.getPos().y;

        for (int i = m; i >= 0; i--) {
            this->editBlocks[i][n].setObstructed(true);

            if (i != m) {
                if (this->editBlocks[i][n].taken1()) this->tilesPlaced--;
                this->editBlocks[i][n].set_taken(false);
            }
        }
    } else if (name == "cannon") {
        // Add obstructions above
        int m = eb.getPos().x;
        int n = eb.getPos().y;

        for (int i = m; i < EDIT_MATRIX_H; i++) {
            this->editBlocks[i][n].setObstructed(true);

            if (i != m) {
                if (this->editBlocks[i][n].taken1()) this->tilesPlaced--;
                this->editBlocks[i][n].set_taken(false);
            }
        }
    }
}

void Tema1::RemoveObstructed(EditBlockData &eb) {
    // When deleting a tile, we want to remove it's created obstructions.
    std::string name = eb.mesh_name();

    if (name == "buildingTile") {
        eb.setObstructed(false);
    } else if (name == "thruster") {
        int m = eb.getPos().x;
        int n = eb.getPos().y;

        for (int i = m; i >= 0; i--) {
            this->editBlocks[i][n].setObstructed(false);
        }
    } else if (name == "cannon") {
        int m = eb.getPos().x;
        int n = eb.getPos().y;

        for (int i = m; i < EDIT_MATRIX_H; i++) {
            this->editBlocks[i][n].setObstructed(false);
        }
    }
}

bool Tema1::UpdateConnected() const {
    // Update connection status when placing or deleting a block by running a DFS on the connected blocks.

    if (tilesPlaced == 0)
        return false;
    if (tilesPlaced == 1)
        return true;

    // Find a starting tile
    int startX = -1, startY = -1;
    for (int i = 0; i < EDIT_MATRIX_H && startX == -1; i++) {
        for (int j = 0; j < EDIT_MATRIX_W; j++) {
            if (editBlocks[i][j].taken1()) {
                startX = i;
                startY = j;
                break;
            }
        }
    }

    if (startX == -1) return false;

    // DFS stack
    std::vector<std::pair<int,int>> stack;
    std::vector<std::vector<bool>> visited(EDIT_MATRIX_H, std::vector<bool>(EDIT_MATRIX_W, false));

    stack.emplace_back(startX, startY);
    visited[startX][startY] = true;

    int connectedCount = 0;

    while (!stack.empty()) {
        auto p = stack.back();
        int x = p.first;
        int y = p.second;
        stack.pop_back();
        connectedCount++;

        // Up
        if (x > 0 && editBlocks[x - 1][y].taken1() && !visited[x - 1][y]) {
            visited[x - 1][y] = true;
            stack.emplace_back(x - 1, y);
        }

        // Down
        if (x < EDIT_MATRIX_H - 1 && editBlocks[x + 1][y].taken1() && !visited[x + 1][y]) {
            visited[x + 1][y] = true;
            stack.emplace_back(x + 1, y);
        }

        // Left
        if (y > 0 && editBlocks[x][y - 1].taken1() && !visited[x][y - 1]) {
            visited[x][y - 1] = true;
            stack.emplace_back(x, y - 1);
        }

        // Right
        if (y < EDIT_MATRIX_W - 1 && editBlocks[x][y + 1].taken1() && !visited[x][y + 1]) {
            visited[x][y + 1] = true;
            stack.emplace_back(x, y + 1);
        }
    }

    // Check if we reached all tiles
    return connectedCount == tilesPlaced;
}

glm::vec2 Tema1::ComputeShipDimensions() const {
    // Compute how many blocks it's got on the X and Y axis
    std::vector<bool> horiz;
    std::vector<bool> vert;

    horiz.resize(EDIT_MATRIX_W);
    vert.resize(EDIT_MATRIX_H);

    for (int i = 0; i < EDIT_MATRIX_H; i++) {
        for (int j = 0; j < EDIT_MATRIX_W; j++) {
            if (this->editBlocks[i][j].taken1()) {
                if (this->editBlocks[i][j].mesh_name() == "cannon") {
                    horiz[j] = true;

                    // Take cannon into account
                    vert[i] = true;
                    vert[i + 1] = true;
                    vert[i + 2] = true;
                } else {
                    horiz[j] = true;
                    vert[i] = true;
                }
            }
        }
    }

    return {std::count(horiz.begin(), horiz.end(), true),
            std::count(vert.begin(), vert.end(), true)};
}

glm::vec2 Tema1::ComputeShipCenter() {
    // Get the average of all the centers of blocks in ships to get the ship center.
    glm::vec3 sum{0, 0, 0};

    for (const auto& eb : this->playerShip.getBlocks()) {
        sum += eb.corner1() + glm::vec3(EDIT_BLOCK_LEN / 2.f, EDIT_BLOCK_LEN / 2.f, 0);
    }

    sum /= static_cast<float>(this->playerShip.getBlocks().size());

    return glm::vec2{sum.x, sum.y};
}

glm::vec2 Tema1::ComputeStartCoords() {
    // Horizontally centered
    float x = GAME_SPACE_W / 2.f;

    // Arbitrary y to fit an average ship
    float y = 150.f;
    return glm::vec2{x, y};
}

glm::vec3 Tema1::ComputeHitboxCorner() {
    // Get lowest X and Y of the blocks of the ship to get its corner
    float x = LOGIC_SPACE_W;
    float y = LOGIC_SPACE_H;

    // Get lowest x and y
    for (auto &eb : this->playerShip.getBlocks()) {
        if (x > eb.corner1().x) x = eb.corner1().x;
        if (y > eb.corner1().y) y = eb.corner1().y;
    }

    glm::vec3 hitboxCorner = glm::vec3(x, y, 0);
    return hitboxCorner;
}

void Tema1::LoadGameMeshes() {
    // Meshes used in game phase
    Mesh *chicken = objects2D::CreateChicken("chicken", glm::vec3(0, 0, 0));
    AddMeshToList(chicken);

    Mesh *cannonProj = objects2D::CreateCannonProjectile("cannonProjectile", glm::vec3(0, 0, 0));
    AddMeshToList(cannonProj);

    Mesh *chickenProj = objects2D::CreateChickenProjectile("chickenProjectile", glm::vec3(0, 0, 0));
    AddMeshToList(chickenProj);

    Mesh *square = objects2D::CreateSquare("whiteSquare", glm::vec3(0, 0, 0), EDIT_BLOCK_LEN, glm::vec3(1, 1, 1), true);
    AddMeshToList(square);

    Mesh *life = objects2D::CreateLife("life", glm::vec3(0, 0, 0), glm::vec3(1, 0, 0));
    AddMeshToList(life);

    Mesh *speed = objects2D::CreateLife("speed", glm::vec3(0, 0, 0), glm::vec3(63 / 255.f, 207 / 255.f, 255 / 255.f));
    AddMeshToList(speed);
}

void Tema1::InitGame() {
    // Reset time for sin wave
    this->chickenTime = 0;

    // Init ship
    // Gather blocks
    for (int i = 0; i < EDIT_MATRIX_H; i++) {
        for (int j = 0; j < EDIT_MATRIX_W; j++) {
            if (this->editBlocks[i][j].taken1()) {
                this->playerShip.addBlock(this->editBlocks[i][j]);
            }
        }
    }

    // Set size
    this->playerShip.setSize(ComputeShipDimensions());

    // Set center
    this->playerShip.setCenter(this->ComputeShipCenter());

    // Set speed and cannons while we're at it
    this->playerShip.ComputeSpeed();

    // Now we can compute the score multiplier
    this->multiplier = MULTIPLIER / (this->playerShip.getSpeed() + this->playerShip.getCannons());

    // Lives
    this->lives += this->playerShip.getTiles();

    // Compute where to place ship at the start
    this->startPos = ComputeStartCoords();

    // Calculate offset from ship center to world center
    const float offsX = this->playerShip.getCenter().x - startPos.x;
    const float offsY = this->playerShip.getCenter().y - startPos.y;

    // Move each block
    for (auto &eb : this->playerShip.getBlocks()) {
        glm::vec3 newCorner = eb.corner1() - glm::vec3(offsX, offsY, 0);
        eb.set_corner(newCorner);
    }

    // Compute hitbox
    this->playerShip.setHitboxCorner(this->ComputeHitboxCorner());

    // Init round
    this->round = 1;

    // Chickens alive
    this->chickensAlive = 10;

    // Init chickens
    this->chickens.clear();
    chickens.resize(2);
    for (int i = 0; i < 2; i++) {
        glm::vec3 rowCorner = this->startCorner - glm::vec3(0, i * CHICKEN_V_OFFS, 0);
        chickens[i].reserve(5);
        for (int j = 0; j < 5; j++) {
            chickens[i].emplace_back(rowCorner + glm::vec3(j * CHICKEN_H_OFFS, 0, 0));
        }
    }
}

void Tema1::RenderGame() {
    // Render game elements
    RenderShip();
    RenderChickens();
    RenderProjectiles();

    // Render UI last
    RenderUI();
}

void Tema1::RenderShip() {
    // Render every block in the ship
    PlayerShip &ps = this->playerShip;
    float scale = SHIP_SCALE_FACTOR;

    for (auto& eb : ps.getBlocks()) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= Transformations::Translate(eb.corner1().x, eb.corner1().y);
        RenderMesh2D(meshes[eb.mesh_name()], shaders["VertexColor"], visMatrix * modelMatrix);
    }
}

void Tema1::RenderChickens() {
    // Render every chicken

    // Sin wave parameters
    float amplitude = 0;
    float omega = 0;
    float downFactor = 0;

    if (this->wave == 1) {
        amplitude = 900.f;
        omega = 1.0f;
        downFactor = -20.0f;
    } else if (this->wave == 2) {
        amplitude = 900.f;
        omega = 1.0f;
        downFactor = -40.f;
    } else if (this->wave == 3) {
        amplitude = 900.f;
        omega = 1.0f;
        downFactor = -60.f;
    }

    // So we only add the difference between the movements so that they don't add up
    static float prevXOffset = 0.0f;
    static float prevYOffset = 0.0f;

    float xOffset = amplitude * sin(omega * chickenTime);
    float yOffset = downFactor * chickenTime;

    // Compute the difference since last frame
    float dx = xOffset - prevXOffset;
    float dy = yOffset - prevYOffset;

    // Apply only diff movement
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 5; j++) {
            Chicken &chicken = chickens[i][j];
            // Render chicken only if it is alive
                chicken.addMove(glm::vec3(dx, dy, 0));

            if (chicken.isAlive()) {
                modelMatrix = Transformations::Translate(chicken.getCorner().x, chicken.getCorner().y);
                RenderMesh2D(meshes["chicken"], shaders["VertexColor"], visMatrix * modelMatrix);
            }
        }
    }

    // Update previous offset
    prevXOffset = xOffset;
    prevYOffset = yOffset;
}

void Tema1::ShootCannons() {
    // When space is pressed, for every cannon make a projectile project
    PlayerShip &ps = this->playerShip;
    glm::vec3 offs = glm::vec3(5, 6 * EDIT_BLOCK_LEN * SHIP_SCALE_FACTOR, 0);
    for (auto &eb : this->playerShip.getBlocks()) {
        if (eb.mesh_name() == "cannon") {
            glm::vec3 projCorner = eb.corner1() + offs;

            // Instantiate object
            cannonProjectiles.emplace_back(projCorner);
        }
    }
}

void Tema1::ShootEgg() {
    // For every wave, there's a different chance for a chicken every one second to produce an egg
    for (auto &chickenRow : chickens) {
        for (auto &chicken : chickenRow) {
            // Only for alive chickens
            if (!chicken.isAlive()) continue;

            bool shoot = false;
            int x = Rand100();
            // 10 % chance per chicken of shooting egg
            if (wave == 1 && x <= 10) {
                shoot = true;
            } else if (wave == 2 && x <= 30) {
                shoot = true;
            } else if (wave == 3 && x <= 50) {
                shoot = true;
            }

            // Instantiate
            if (shoot) {
                chickenProjectiles.emplace_back(chicken.getCorner());
            }
        }
    }
}


void Tema1::RenderProjectiles() {
    // Render every cannon projectile
    for (auto &proj : this->cannonProjectiles) {
        // Place it where it needs to be
        modelMatrix = Transformations::Translate(proj.getCorner().x, proj.getCorner().y);
        RenderMesh2D(meshes["cannonProjectile"], shaders["VertexColor"], visMatrix * modelMatrix);
    }

    // Render every chicken projectile
    for (auto &proj : this->chickenProjectiles) {
        modelMatrix = Transformations::Translate(proj.getCorner().x, proj.getCorner().y);
        modelMatrix *= Transformations::Scale(1.f, 1.6f);
        RenderMesh2D(meshes["chickenProjectile"], shaders["VertexColor"], visMatrix * modelMatrix);
    }
}

void Tema1::CheckCannonHit() {
    // Check what a cannonball can hit, despawn if it's:
    // out of bounds, inside a chicken, inside an egg

    // Iterate with an iterator because we might erase
    for (auto projIt = cannonProjectiles.begin(); projIt != cannonProjectiles.end(); ) {
        bool hitChicken = false;
        bool hitEgg = false;

        // Check if it's out of bounds
        if (projIt->getCorner().y > GAME_SPACE_H) {
            // Delete
            projIt = cannonProjectiles.erase(projIt);
            continue;
        }

        // Check collision with chickens
        for (auto &chickenRow : chickens) {
            for (auto &chicken : chickenRow) {
                if (!chicken.isAlive()) continue;

                if (projIt->isInsideCircle(chicken.getCenter(), chicken.getHitboxRadius())) {
                    // Destroy chicken
                    chicken.setAlive(false);
                    chickensAlive--;
                    this->score += 10 * multiplier;
                    hitChicken = true;
                    break;
                }
            }
            if (hitChicken) break;
        }

        if (!hitChicken) {
            // If we didn't hit a chicken, check collision with eggs
            for (auto eggIt = chickenProjectiles.begin(); eggIt != chickenProjectiles.end(); ) {
                if (projIt->isInsideCircle(eggIt->getCenter(), eggIt->getRadius())) {
                    // Destroy the egg
                    eggIt = chickenProjectiles.erase(eggIt);
                    this->score += 5 * multiplier;
                    hitEgg = true;
                    break;
                } else {
                    ++eggIt;
                }
            }
        }

        // Remove the cannon projectile if it hit anything
        if (hitChicken || hitEgg) {
            projIt = cannonProjectiles.erase(projIt);
        } else {
            ++projIt;
        }
    }
}

void Tema1::CheckEggHit() {
    // Check what egg hit. If it's out of bounds destroy it.
    for (auto eggIt = chickenProjectiles.begin(); eggIt != chickenProjectiles.end(); ) {
        // Check if it's out of bounds
        if (eggIt->getCorner().y < -100) {
            eggIt = chickenProjectiles.erase(eggIt);
            continue;
        }

        bool hitShip = false;

        float shipW = this->playerShip.getSize().x * EDIT_BLOCK_LEN;
        float shipH = this->playerShip.getSize().y * EDIT_BLOCK_LEN;

        // Check if it's inside ship
        if (eggIt->isInsideSquare(this->playerShip.getHitboxCorner(), shipW, shipH)) {
            hitShip = true;
            this->lives--;
        }

        if (hitShip)
            eggIt = chickenProjectiles.erase(eggIt);
        else
            ++eggIt;
    }
}

void Tema1::RenderGameOver() {
    // Render gameover and score
    if (!this->multiplierAdded) {
        int bonus = this->lives * 10 * multiplier;
        this->score += bonus;
        this->multiplierAdded = true;
    }

    if (wave == 3 && chickensAlive == 0) {
        textRenderer->RenderText("YOU WIN", 420, 200, 3.0f);
    } else {
        textRenderer->RenderText("GAME OVER", 380, 200, 3.0f);
    }
    textRenderer->RenderText("Final score: " + std::to_string(score), 340, 350, 2.0f);
}

void Tema1::RenderUI() {
    // Render lives
    modelMatrix = Transformations::Translate(LIFE_W, GAME_SPACE_H - LIFE_H * 2.5);
    modelMatrix *= Transformations::Scale(2.f, 2.f);
    for (int i = 0; i < lives; i++) {
        RenderMesh2D(meshes["life"], shaders["VertexColor"], visMatrix * modelMatrix);
        modelMatrix *= Transformations::Translate(LIFE_OFFSET, 0);
    }

    // Render speed indicator
    modelMatrix = Transformations::Translate(LIFE_W, GAME_SPACE_H - LIFE_H * 6);
    modelMatrix *= Transformations::Scale(2.f, 2.f);
    for (int i = 0; i < this->playerShip.getSpeed(); i++) {
        RenderMesh2D(meshes["speed"], shaders["VertexColor"], visMatrix * modelMatrix);
        modelMatrix *= Transformations::Translate(LIFE_OFFSET, 0);
    }

    // Render wave
    textRenderer->RenderText("Wave: " + std::to_string(wave), 1080, 20, 1.0f);

    // Render score
    textRenderer->RenderText("Score: " + std::to_string(score), 1050, 60, 1.0f);

}

void Tema1::CheckChickens() {
    // Check if any chicken touched the bottom of the screen
    // Update waves and reset chickens
    for (auto &chickenRow : this->chickens) {
        for (auto &chicken : chickenRow) {
            if (chicken.getCorner().y < 0) {
                this->gameOver = true;
            }
        }
    }

    if (wave == 1 && chickensAlive == 0) {
        this->chickenTime = 0;
        this->wave = 2;
        this->chickensAlive = 10;
        this->cannonProjectiles.clear();
        for (auto &chickenRow : this->chickens) {
            for (auto &chicken : chickenRow) {
                // Set chicken back alive so that its visible
                chicken.setAlive(true);
            }
        }
    }

    if (wave == 2 && chickensAlive == 0) {
        this->chickenTime = 0;
        this->wave = 3;
        this->chickensAlive = 10;
        this->cannonProjectiles.clear();
        for (auto &chickenRow : this->chickens) {
            for (auto &chicken : chickenRow) {
                // Set chicken back alive so that its visible
                chicken.setAlive(true);
            }
        }
    }
}

int Tema1::Rand100() {
    // Random number generator between 1 and 100
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(1, 100);

    return dist(gen);
}



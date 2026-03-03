//
// Created by patur on 10/30/2025.
//

#ifndef GFXFRAMEWORK_TEMA1_H
#define GFXFRAMEWORK_TEMA1_H

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "CannonProjectile.h"
#include "ChickenProjectile.h"
#include "components/simple_scene.h"
#include "Transformations.h"
#include "EditBlockData.h"
#include "InteractableMesh.h"
#include "PlayerShip.h"
#include "Chicken.h"
#include "components/text_renderer.h"

namespace m1
{
    class Tema1 final : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1() override;
        void Init() override;
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

    protected:
        struct LogicSpace {
            float x, y, width, height;
        };

        struct ViewportSpace {
            int x, y, width, height;
        };

        // Default functions
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        // Render functions
        void RenderMenu();
        void RenderGame();
        void RenderShip();
        void RenderChickens();
        void RenderProjectiles();
        void RenderUI();
        void RenderGameOver();

        // Load meshes functions
        void LoadMenuMeshes();
        void LoadGameMeshes();

        // Initiate game
        void InitGame();
        glm::vec2 ComputeShipDimensions() const;
        glm::vec2 ComputeShipCenter();
        static glm::vec2 ComputeStartCoords();
        glm::vec3 ComputeHitboxCorner();

        // Shooting logic
        void ShootCannons();
        void CheckCannonHit();
        void ShootEgg();
        void CheckEggHit();
        void CheckChickens();

        // Editor helpers
        void AddMeshToInteractables(const std::string& name, glm::vec3 corner, float width, float height);
        void AddObstructed(EditBlockData &eb);
        void RemoveObstructed(EditBlockData &eb);
        bool UpdateConnected() const;

        // Viewport functions
        static glm::mat3 VisualizationTransf2DUnif(const LogicSpace &logicSpace, const ViewportSpace &viewSpace);
        void SetViewportAreaMenu(const ViewportSpace & viewSpace, glm::vec3 colorColor, bool clear);
        void SetViewportAreaGame(const ViewportSpace & viewSpace, glm::vec3 colorColor, bool clear);
        glm::vec2 WindowToLogic(int x, int y);

        // Utils
        int Rand100();

    private:
        LogicSpace logicSpace{};
        ViewportSpace viewSpace{};

        glm::mat3 visMatrix{};
        glm::mat3 modelMatrix{};

        // Gamemode
        bool menu;

        // Tiles placed
        int tilesPlaced;

        // Interactable meshes
        std::unordered_map<std::string, InteractableMesh> interactableMeshes;

        // Grid
        std::vector<std::vector<EditBlockData>> editBlocks;

        // Mouse pos translated to logic coords
        int mouseX, mouseY;

        // Mesh connection status
        bool connected;

        // Player ship
        PlayerShip playerShip;

        // Starting coords for ship in scene
        glm::vec2 startPos;

        // Round number
        int round;

        // Lives
        int lives;

        // Chicken array
        std::vector<std::vector<Chicken>> chickens;

        // Starting corner for chickens
        glm::vec3 startCorner{GAME_SPACE_W / 4.f + 160, GAME_SPACE_H - 200, 0};

        // Chickens alive
        int chickensAlive;

        // delta time
        float deltaTime;

        // delta time for chickens
        float chickenTime = 0.f;

        // Cannon projectiles
        std::vector<CannonProjectile> cannonProjectiles;

        // Chicken projectiles
        std::vector<ChickenProjectile> chickenProjectiles;

        // Shooting cooldown
        float timeSinceLastShot = 0.0f;
        float shootCooldown = 1.f;

        // Shooting eggs cooldown
        float timeSinceLastShotEgg = 0.0f;
        float shootCooldownEgg = 1.f;

        // Game over
        bool gameOver = false;

        // Score
        int score = 0;

        // Score multiplier
        float multiplier = MULTIPLIER;

        // Wave
        int wave = 1;

        // Text renderer object
        gfxc::TextRenderer *textRenderer;

        // Add multiplier once
        bool multiplierAdded = false;
    };
}   // namespace m1


#endif //GFXFRAMEWORK_TEMA1_H
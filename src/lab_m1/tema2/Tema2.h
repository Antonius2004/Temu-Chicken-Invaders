#pragma once

#include <queue>
#include <vector>
#include "components/simple_scene.h"
#include "Block.h"
#include "Draisine.h"
#include "Train.h"
#include "components/text_renderer.h"


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        Tema2();
        ~Tema2() override;

        void Init() override;

    private:
        // Framework methods
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        // My methods
        void LoadMeshes();
        void CreateTerrain();
        void RenderTerrain();
        void CreateRails();
        void UpdateNeighBlocksWithRails();
        void RenderRails();
        void RenderCrackedRail(Mesh* mesh, const glm::mat4& modelMatrix);
        void RenderTrain();
        void UpdateTrain(float deltaTimeSeconds);
        void FindNextRail(Block *current_block);
        void FindNextRailWagon(Block *current_block);
        void CrackBlock();
        void AddAllRailsToList();
        void RenderDraisine();
        void UpdateTPSCamera();
        void UpdateDraisine();
        void CheckRepair();
        void RenderStations();
        void RenderGameOver();

        // Getters and setter

        // My class variables
        std::vector<std::vector<Block>> terrain_arr_;
        Block rail_start_;
        Train train_;

        Block wagon_start_;
        Train wagon_;

        std::queue<int> next_path_choice_;
        int wagon_choice_buffer_ = -1;

        float crack_timer_ = 0.0f;

        std::vector<Rail *> all_rails_;

        Draisine draisine_;
        int draisine_choice_ = -1;
        Block* draisine_last_intersection_ = nullptr;

        float handle_rotation_time_ = 0.0f;

        int score = 0;

        float time_elapsed_ = 0;

        float time_since_stop_ = 0.f;

        bool train_stopped_ = false;

        bool game_over_ = false;

        gfxc::TextRenderer *textRenderer;
    };
}   // namespace m1

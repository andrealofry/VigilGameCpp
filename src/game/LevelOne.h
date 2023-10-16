#pragma once

#include <memory>
#include "Game.h"

#include "../vendor/glm/gtc/matrix_transform.hpp"

#include "../VertexBuffer.h"
#include "../VertexBufferLayout.h"
#include "../Texture.h"
#include "Player.h"

namespace game {
    class LevelOne : public Game {
    public:
        LevelOne();
        ~LevelOne();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        Player m_Player;
        float speed = 20.0f;
    };
}



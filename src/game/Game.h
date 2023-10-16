#pragma once

#include <vector>
#include <string>
#include <functional>
#include <iostream>

namespace game{
    class Game
    {
    public:
        explicit Game() {}
        virtual ~Game(){}

        virtual void OnUpdate(float  deltaTime) {}
        virtual void OnRender() {}
        virtual void OnImGuiRender() {}
    };

    class GameMenu : public Game
    {
    public:
        GameMenu(Game *&currentGamePointer);

        void OnImGuiRender() override;

        template<typename T>
        void RegisterGame(const std::string& name)
        {
            std::cout << "Registering  game " << name << std::endl;

            m_Games.push_back(std::make_pair(name, [](){ return new T(); }));
        }
    private:
        Game*& m_CurrentGame;
        std::vector<std::pair<std::string, std::function<Game*()>>> m_Games;
    };
}
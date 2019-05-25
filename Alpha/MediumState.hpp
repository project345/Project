#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace Sarang {
    class MediumState : public State {
    public:
        MediumState(GameDataRef data);
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
        
    private:
        GameDataRef _data;
        sf::Clock _clock;
        sf::Sprite _hidden;
        sf::Sprite _surface;
        sf::Sprite _restart;
    };
}
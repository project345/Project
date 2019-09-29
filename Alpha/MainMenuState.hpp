#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace MESY {
    class MainMenuState : public State {
    public:
        MainMenuState(GameDataRef data);
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
        
    private:
		sf::Music music;
        GameDataRef _data;
        sf::Clock _clock;
        sf::Sprite _startgame, _background;
    };
}
//@author Max Stewart //1086706, Elbert Alcantara //4435223, Sarang Han //5098495
#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace MESY {
    class SplashState : public State {
    public:
        SplashState(GameDataRef data);
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
        
    private:
		bool Intro_Done = false;
        GameDataRef _data;
        sf::Clock _clock;
        sf::Sprite _background_intro, _background_tit;
    };
}

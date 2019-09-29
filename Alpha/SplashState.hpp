#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.hpp"
#include "Game.hpp"


namespace MESY {
    class SplashState : public State {
    public:
        SplashState(GameDataRef data, const char* mode);
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
        
    private:
		bool _intro_done;
		const char* _mode;
		sf::Music _music;
        GameDataRef _data;
        sf::Clock _clock;
		sf::Event event;
        sf::Sprite _background_intro1, _background_intro2, _background_intro3, _background_gameOver, _background_gameWon;
		sf::Sprite _background_tit1, _background_tit2, _background_tit3;
		sf::Sprite _intro1, _intro2, _intro3, _intro4, _intro5, _escintro;
    };
}
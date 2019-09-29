#include <sstream>
#include <iostream>
#include "SplashState.hpp"
#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"
#include "Game.hpp"


namespace MESY {
    SplashState::SplashState(GameDataRef data, const char* mode) : _data(data) {

		_music.openFromFile(INTRO_MUSIC);
		_music.setVolume(100);
		_music.play();

		_intro_done = false;

		_mode = mode;
		if (strcmp(mode, "intro") == 0) {
			_data->assets.LoadTexture("Splash Intro1", SPLASH_INTRO1);
			_data->assets.LoadTexture("Splash Intro2", SPLASH_INTRO2);

			_data->assets.LoadTexture("Splash Title1", SPLASH_TITLE1);
			_data->assets.LoadTexture("Splash Title2", SPLASH_TITLE2);
			_data->assets.LoadTexture("Splash Title3", SPLASH_TITLE3);

			_data->assets.LoadTexture("Intro1", INTRO1);
			_data->assets.LoadTexture("Intro2", INTRO2);
			_data->assets.LoadTexture("Intro3", INTRO3);
			_data->assets.LoadTexture("Intro4", INTRO4);
			_data->assets.LoadTexture("Intro5", INTRO5);
			_data->assets.LoadTexture("Escintro", ESCINTRO);
		

			_intro1.setTexture(this->_data->assets.GetTexture("Intro1"));
			_intro2.setTexture(this->_data->assets.GetTexture("Intro2"));
			_intro3.setTexture(this->_data->assets.GetTexture("Intro3"));
			_intro4.setTexture(this->_data->assets.GetTexture("Intro4"));
			_intro5.setTexture(this->_data->assets.GetTexture("Intro5"));
			_escintro.setTexture(this->_data->assets.GetTexture("Escintro"));

			sf::Vector2f targetSizeIntro1(700.0f / 0.45, 437.0f / 0.45);
			sf::Vector2f targetSizeIntro2(334.0f / 0.42, 394.0f / 0.42);
			sf::Vector2f targetSizeIntro3(1000.0f / 0.8, 667.0f / 0.8);
			sf::Vector2f targetSizeIntro4(980.0f / 0.7, 500.0f /0.535);
			sf::Vector2f targetSizeIntro5(2187.0f / 2.95, 2850.0f / 2.95);
			_intro1.setScale(targetSizeIntro1.x / _intro1.getLocalBounds().width, targetSizeIntro1.y / _intro1.getLocalBounds().height);
			_intro2.setScale(targetSizeIntro2.x / _intro2.getLocalBounds().width, targetSizeIntro2.y / _intro2.getLocalBounds().height);
			_intro3.setScale(targetSizeIntro3.x / _intro3.getLocalBounds().width, targetSizeIntro3.y / _intro3.getLocalBounds().height);
			_intro4.setScale(targetSizeIntro4.x / _intro4.getLocalBounds().width, targetSizeIntro4.y / _intro4.getLocalBounds().height);
			_intro5.setScale(targetSizeIntro5.x / _intro5.getLocalBounds().width, targetSizeIntro5.y / _intro5.getLocalBounds().height);
			_intro1.setPosition(-350, 0);
			_intro3.setPosition(-400, 0);
			_intro4.setPosition(-260, 0);
			_escintro.setPosition(0, 100);

			_background_intro1.setTexture(this->_data->assets.GetTexture("Splash Intro1"));
			_background_intro2.setTexture(this->_data->assets.GetTexture("Splash Intro2"));

			_background_tit1.setTexture(this->_data->assets.GetTexture("Splash Title1"));
			_background_tit2.setTexture(this->_data->assets.GetTexture("Splash Title2"));
			_background_tit3.setTexture(this->_data->assets.GetTexture("Splash Title3"));

			sf::Vector2f targetSize(620.0f/0.8, 800.0f/0.8);
			_background_intro1.setScale(targetSize.x / _background_intro1.getLocalBounds().width, targetSize.y / _background_intro1.getLocalBounds().height);
			_background_intro2.setScale(targetSize.x / _background_intro2.getLocalBounds().width, targetSize.y / _background_intro2.getLocalBounds().height);

			_background_intro1.setPosition(-10, 0);
			_background_intro2.setPosition(-10, 0);

			sf::Vector2f targetSize1((float)(1920.0f / 1.3), (float)(1280.0f / 1.3));
			_background_tit1.setScale(targetSize1.x / _background_tit1.getLocalBounds().width, targetSize1.y / _background_tit1.getLocalBounds().height);
			_background_tit2.setScale(targetSize1.x / _background_tit2.getLocalBounds().width, targetSize1.y / _background_tit2.getLocalBounds().height);
			_background_tit3.setScale(targetSize1.x / _background_tit3.getLocalBounds().width, targetSize1.y / _background_tit3.getLocalBounds().height);

			_background_tit1.setPosition(-360, -50);
			_background_tit2.setPosition(-360, -50);
			_background_tit3.setPosition(-360, -50);
		}
		else if (strcmp(mode, "gameOver") == 0) {
			_music.stop();
			_data->assets.LoadTexture("Game Over", GAME_OVER_SCREEN);
			_background_gameOver.setTexture(this->_data->assets.GetTexture("Game Over"));

			sf::Vector2f targetSize((float)(1920.0f / 1.3), (float)(1280.0f / 1.3));
			_background_gameOver.setScale(targetSize.x / _background_gameOver.getLocalBounds().width, targetSize.y / _background_gameOver.getLocalBounds().height);
			_background_gameOver.setPosition(-360, -50);
		}
		else if (strcmp(mode, "gameWon") == 0) {
			_music.stop();
			_data->assets.LoadTexture("Game Won", GAME_WON_SCREEN);
			_background_gameWon.setTexture(this->_data->assets.GetTexture("Game Won"));

			sf::Vector2f targetSize((float)(1920.0f / 1.3), (float)(1280.0f / 1.3));
			_background_gameWon.setScale(targetSize.x / _background_gameWon.getLocalBounds().width, targetSize.y / _background_gameWon.getLocalBounds().height);
			_background_gameWon.setPosition(-350, 0);
		}
	}
    
    void SplashState::HandleInput() {
		while(_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				_data->window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					_music.stop();
					this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
				}
			}
		}
	}

    void SplashState::Update(float dt) {
		if (this->_clock.getElapsedTime().asSeconds() > SPLASH_INTRO_SHOW_TIME && _intro_done == false) {
			_music.stop();
			this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
			_intro_done = true;
		}
    }

    void SplashState::Draw(float dt) {
		if (strcmp(_mode, "intro") == 0) {
			_data->window.clear();
			if (this->_clock.getElapsedTime().asSeconds() > 40) {
				_data->window.draw(_intro5);
			}
			else if (this->_clock.getElapsedTime().asSeconds() > 41) {
				_data->window.draw(_intro4);
			}
			else if (this->_clock.getElapsedTime().asSeconds() > 32) {
				_data->window.draw(_intro3);
			}
			else if (this->_clock.getElapsedTime().asSeconds() > 24) {
				_data->window.draw(_intro2);
			}
			else if (this->_clock.getElapsedTime().asSeconds() > 17.5) {
				_data->window.draw(_intro1);
			}
			else if (this->_clock.getElapsedTime().asSeconds() > 8) {
				_data->window.draw(_background_tit3);
			}
			else if (this->_clock.getElapsedTime().asSeconds() > 7) {
				_data->window.draw(_background_tit2);
			}
			else if (this->_clock.getElapsedTime().asSeconds() > 6) {
				_data->window.draw(_background_tit1);
			}
			else if (this->_clock.getElapsedTime().asSeconds() > 4) {
				_data->window.draw(_background_intro2);
			}
			else {
				_data->window.draw(_background_intro1);
			}
		}
		else if (strcmp(_mode, "gameOver") == 0) {
			_data->window.draw(_background_gameOver);
		}
		else if (strcmp(_mode, "gameWon") == 0) {
			_data->window.draw(_background_gameWon);
		}
		_data->window.draw(_escintro);
        _data->window.display();
    }
}
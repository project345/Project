//@author Max Stewart //1086706, Elbert Alcantara //4435223, Sarang Han //5098495
#include <sstream>
#include "SplashState.hpp"
#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"
#include <iostream>

namespace MESY {
	SplashState::SplashState(GameDataRef data) : _data(data) {
		_data->assets.LoadTexture("Splash Intro", SPLASH_INTRO);
		_data->assets.LoadTexture("Splash Title", SPLASH_TITLE);

		_background_intro.setTexture(this->_data->assets.GetTexture("Splash Intro"));
		_background_tit.setTexture(this->_data->assets.GetTexture("Splash Title"));

		sf::Vector2f targetSize(620.0f, 800.0f);
		_background_intro.setScale(targetSize.x / _background_intro.getLocalBounds().width, targetSize.y / _background_intro.getLocalBounds().height);
		_background_intro.setPosition(-10, 0);

		sf::Vector2f targetSize1((float)(1920.0f / 1.5), (float)(1280.0f / 1.5));
		_background_tit.setScale(targetSize1.x / _background_tit.getLocalBounds().width, targetSize1.y / _background_tit.getLocalBounds().height);
		_background_tit.setPosition(-315, -50);
	}

	void SplashState::HandleInput() {
		sf::Event event;

		while (_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				_data->window.close();
			}
		}
	}

	void SplashState::Update(float dt) {
		if (this->_clock.getElapsedTime().asSeconds() > SPLASH_TITLE_SHOW_TIME) {
			this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
		}
	}

	void SplashState::Draw(float dt) {
		_data->window.clear();
		if (this->_clock.getElapsedTime().asSeconds() > SPLASH_INTRO_SHOW_TIME && Intro_Done == false) {
			_data->window.draw(_background_tit);
		}
		else {
			_data->window.draw(_background_intro);
		}
		_data->window.display();
	}
}

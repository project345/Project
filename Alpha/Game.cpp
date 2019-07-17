//@author Max Stewart //1086706, Elbert Alcantara //4435223, Sarang Han //5098495
#include "Game.hpp"
#include "SplashState.hpp"


namespace MESY {
	Game::Game(int width, int height, std::string title) {
		_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
		_data->machine.AddState(StateRef(new SplashState(this->_data)));
		this->Run();
	}

	void Game::Run() {
		float newTime, frameTime, interpolation, accumulator, currentTime;

		currentTime = this->_clock.getElapsedTime().asSeconds();
		accumulator = 0.0f;

		while (this->_data->window.isOpen()) {
			this->_data->machine.ProcessStateChanges();

			newTime = this->_clock.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;
			currentTime = newTime;
			accumulator = 0.08f;

			while (accumulator >= dt) {
				this->_data->machine.GetActiveState()->HandleInput();
				this->_data->machine.GetActiveState()->Update(dt);
				accumulator -= dt;
			}
			interpolation = accumulator / dt;
			this->_data->machine.GetActiveState()->Draw(interpolation);
		}
	}
}

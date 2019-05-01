#pragma once

#include <sstream>
#include "DEFINITIONS.h"
#include "GameState.h"


#include <iostream>

namespace StewartGames
{
	GameState::GameState(GameDataRef data) : _data(data) {

	}

	void GameState::Init()
	{
		this->_data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
		
		this->_data->assets.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH);

		_tiles = new int*[5];
		for (int i = 0; i < 5; i++) {
			_tiles[i] = new int[5];
			for (int j = 0; j < 5; j++)
			{
				_tiles[i][j] = 0;
			}
		}
		_player = new Player(_data);
		_player->Init();

		_background.setTexture(this->_data->assets.GetTexture("Game Background"));

	}

	void GameState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::W)
				{
					_player->MovePlayerUp();
					
				}
				if (event.key.code == sf::Keyboard::S) {
					_player->MovePlayerDown();
				}
				if (event.key.code == sf::Keyboard::A) {
					_player->MovePlayerLeft();
				}
				if (event.key.code == sf::Keyboard::D) {
					_player->MovePlayerRight();
				}
			}
		}
	}

	void GameState::Update(float dt)
	{
	
	}

	void GameState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_background);
		_player->Draw();
		this->_data->window.display();
	}
}
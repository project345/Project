#pragma once

#include <sstream>
#include "GameState.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace StewartGames
{
	GameState::GameState(GameDataRef data) : _data(data)
	{

	}

	void GameState::Init()
	{
		this->_data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
		_tiles = new int*[5];
		for (int i = 0; i < 5; i++) {
			_tiles[i] = new int[5];
			for (int j = 0; j < 5; j++)
			{
				_tiles[i][j] = 0;
			}
		}

		PrintTileArray();

		_background.setTexture(this->_data->assets.GetTexture("Game Background"));
		
	}

	void GameState::PrintTileArray() {
		std::cout << std::endl << std::endl;
		for (int x = 0; x < 5; x++)
		{
			for (int y = 0; y < 5; y++)
			{
				std::cout << _tiles[x][y] << " ";
			}
			std::cout << std::endl;
		}
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
				if (event.key.code == sf::Keyboard::S)
				{
					
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

		this->_data->window.display();
	}
}
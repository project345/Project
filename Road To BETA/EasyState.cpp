#include <sstream>
#include <time.h>
#include "SplashState.hpp"
#include "DEFINITIONS.hpp"
#include "EasyState.hpp"
#include "MainMenuState.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace MESY {
    EasyState::EasyState(GameDataRef data) : _data(data) {
		this->_data->assets.LoadTexture("Restart Button", RESTART_FILEPATH);
		this->_data->assets.LoadTexture("Surface", DESERT_FILEPATH);
		this->_data->assets.LoadTexture("Mines", TILES_FILEPATH);
		this->_data->assets.LoadTexture("Background", BOARD_BACKGROUND_FILEPATH);

		_restart.setTexture(this->_data->assets.GetTexture("Restart Button"));
		_hidden.setTexture(this->_data->assets.GetTexture("Mines"));
		_surface.setTexture(this->_data->assets.GetTexture("Surface"));
		_background.setTexture(this->_data->assets.GetTexture("Background"));

		sf::Vector2f targetSize1(100.0f, 70.0f);
		_restart.setScale(targetSize1.x / _restart.getLocalBounds().width, targetSize1.y / _restart.getLocalBounds().height);
		_restart.setPosition(SCREEN_WIDTH / 2 - (_restart.getGlobalBounds().width / 2), 13);
		_surface.setPosition(0, _surface.getGlobalBounds().height / 2);

		sf::Vector2f targetSize((float)(1920.0f / 1.5), (float)(1280.0f / 1.5));
		_background.setScale(targetSize.x / _background.getLocalBounds().width, targetSize.y / _background.getLocalBounds().height);
		_background.setPosition(-315, -50);

		for (int i = 1; i <= 15; i++) {
			for (int j = 1; j <= 20; j++) {
				grid_upper[i][j] = (rand() % 9) + 12;
				if (rand() % 3 == 0) { 
					grid_under[i][j] = 9; 
				} else { 
					grid_under[i][j] = 0; 
				}
			}
		}

		_player = new Player(_data);
		yPos = 0;
		xPos = 0;
	}
	
	void EasyState::Setup(int x) {
		//sets players position to the tile the player clicked, and makes hasChosen = true which needs to be true so player can be drawn.
		_player->setPos(x);

		//sets which tiles to be clear of mines in the start, now its the player's choice, if upper = 0 it will show tile, if under = 0, it will have no bomb
		grid_upper[x][1] = 0;
		grid_under[x][1] = 0; grid_under[x-1][1] = 0; grid_under[x+1][1] = 0; grid_under[x][2] = 0; grid_under[x-1][2] = 0; grid_under[x+1][2] = 0;
		/*
			This calculates how many mines are beside the current tile,
			giving the tile the proper number.
		*/
		for (int i = 1; i <= 15; i++) {
			for (int j = 1; j <= 20; j++) {
				int n = 0;
				if (grid_under[i][j] == 9) continue;
				if (grid_under[i + 1][j] == 9) n++;
				if (grid_under[i][j + 1] == 9) n++;
				if (grid_under[i - 1][j] == 9) n++;
				if (grid_under[i][j - 1] == 9) n++;
				if (grid_under[i + 1][j + 1] == 9) n++;
				if (grid_under[i - 1][j - 1] == 9) n++;
				if (grid_under[i - 1][j + 1] == 9) n++;
				if (grid_under[i + 1][j - 1] == 9) n++;
				grid_under[i][j] = n;
			}
		}
	}

    void EasyState::HandleInput() {
        
		pos = this->_data->input.GetMousePosition(this->_data->window);
        
        while(_data->window.pollEvent(event)) {
            
			if(sf::Event::Closed == event.type) {
                _data->window.close();
            }
            
            if(this->_data->input.IsSpriteClicked(this->_restart, sf::Mouse::Left, this->_data->window)) {
                this->_data->machine.AddState(StateRef(new MainMenuState(_data)),true);
            }

			if (event.type == sf::Event::MouseButtonPressed) {
				x = (pos.x - TILE_WIDTH) / TILE_WIDTH;
				y = (pos.y - 2 * TILE_WIDTH) / TILE_WIDTH;

				if (x > 0 && x < 16 && y == 1 && !_player->PlayerChosen()) {
					Setup(x);
				}
				if (_player->PlayerChosen()) {
					if (event.key.code == sf::Mouse::Left) {
						grid_upper[x][y] = 0; //If tile is clicked, it being 0 will later mean it will display texture underneath.
					} else if (event.key.code == sf::Mouse::Right) {
						grid_under[x][y] = 11;
						grid_upper[x][y] = 0;
					}
				}
			}
			int result = 0;
			if (event.type == sf::Event::KeyPressed && !_player->PlayerMoving() && _player->PlayerChosen()) {
				if (event.key.code == sf::Keyboard::W) {
					_player->MovePlayer(0, -1, 32);
				}
				if (event.key.code == sf::Keyboard::S) {
					_player->MovePlayer(0, 1, 0);
				}
				if (event.key.code == sf::Keyboard::A) {
					_player->MovePlayer(-1, 0, 64);
				}
				if (event.key.code == sf::Keyboard::D) {
					_player->MovePlayer(1, 0, 96);
				}
				sf::Vector2i currentPos = _player->GetPos();
				
				x = currentPos.x;
				y = currentPos.y;
				grid_upper[x][y] = 0;
				if (grid_under[x][y] == 9) { _player->Explode(x, y); }
			}
        }
    }
    
    void EasyState::Update(float dt) {
		_player->Move(dt);
    }
    
    void EasyState::Draw(float dt) {
        _data->window.clear(sf::Color::Magenta);
        _data->window.draw(_background);

		for (int i = 1; i <= 15; i++) {
			for (int j = 1; j <= 20; j++) {
				//If tile underneath is 9 then it is a mine, and upper grid == 0, hence will show all 
				//Tiles underneath the surface texture, ending the game
				if (grid_under[x][y] == 9 && grid_upper[x][y] == 0) {
					grid_upper[i][j] = 0;
					// Restart Game
				}

				//Will draw texture underneath
				if (grid_upper[i][j] == 0) {
					_hidden.setTextureRect(sf::IntRect(grid_under[i][j] * TILE_WIDTH, 0, TILE_WIDTH, TILE_WIDTH));
					_hidden.setPosition((float)((i + 1) * TILE_WIDTH), (float)((j + 2) * TILE_WIDTH));
					_data->window.draw(_hidden);
				} else { //Else will just draw surface texture
					_surface.setTextureRect(sf::IntRect(i * TILE_WIDTH, j * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH));
					_surface.setPosition((float)((i + 1) * TILE_WIDTH), (float)((j + 2) * TILE_WIDTH));
					_data->window.draw(_surface);
				}
			}
		}
		_data->window.draw(_restart);
		if (_player->PlayerChosen()) {
			_player->Draw();
		}
        _data->window.display();
    }
}
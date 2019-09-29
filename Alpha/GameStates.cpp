#include <sstream>
#include <iostream>
#include <time.h>
#include "SplashState.hpp"
#include "DEFINITIONS.hpp"
#include "GameStates.hpp"
#include "MainMenuState.hpp"


namespace MESY {
	GameStates::GameStates(GameDataRef data) : _data(data) {

		music.openFromFile(MAIN_MUSIC);
		music.setVolume(50);
		music.play();
		music.setLoop(true);

		life = 2;

		this->_data->assets.LoadTexture("Restart Button", RESTART_FILEPATH);
		this->_data->assets.LoadTexture("Surface", DESERT_FILEPATH);
		this->_data->assets.LoadTexture("Tiles", TILES_FILEPATH);
		this->_data->assets.LoadTexture("Background", BOARD_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Lifecount", LIFE_COUNT);

		_restart.setTexture(this->_data->assets.GetTexture("Restart Button"));
		_background.setTexture(this->_data->assets.GetTexture("Background"));

		sf::Vector2f targetSize1(250.0f, 100.0f);
		_restart.setScale(targetSize1.x / _restart.getLocalBounds().width, targetSize1.y / _restart.getLocalBounds().height);
		_restart.setPosition(SCREEN_WIDTH / 2 - (_restart.getGlobalBounds().width / 2), -2);

		sf::Vector2f targetSize((float)(1920.0f / 1.3), (float)(1280.0f / 1.3));
		_background.setScale(targetSize.x / _background.getLocalBounds().width, targetSize.y / _background.getLocalBounds().height);
		_background.setPosition(-315, -50);

		_player = new Player(_data);

		_Shape.setPointCount(4);

		for (int i = 1; i <= BOARD_WIDTH; i++) {
			for (int j = 1; j <= BOARD_HEIGHT; j++) {
				_grid_upper[i][j] = 1;

				if (rand() % 3 == 0) {
					_grid_under[i][j] = 9;
				}
				else {
					_grid_under[i][j] = 0;
				}
			}
		}
		for (int i = 0; i < GRID_WIDTH; i++) {
			for (int j = 0; j < GRID_HEIGHT; j++) {
				_under_duplicate[i][j] = _grid_under[i][j];
			}
		}

		for (int i = 0; i < GRID_WIDTH; i++) {
			for (int j = 0; j < GRID_HEIGHT; j++) {
				_upper_duplicate[i][j] = _grid_upper[i][j];
			}
		}
	}

	void GameStates::Setup(int x) {
		//sets players position to the tile the player clicked, and makes hasChosen = true which needs to be true so player can be drawn.
		_player->setPos(x);

		//sets which tiles to be clear of mines in the start, now its the player's choice, if upper = 0 it will show tile, if under = 0, it will have no bomb
		_grid_upper[x][1] = 0;
		_grid_under[x][1] = 0; _grid_under[x - 1][1] = 0; _grid_under[x + 1][1] = 0; _grid_under[x][2] = 0; _grid_under[x - 1][2] = 0; _grid_under[x + 1][2] = 0;

		/*
			This calculates how many mines are beside the current tile,
			giving the tile the proper number.
		*/
		for (int i = 1; i <= BOARD_WIDTH; i++) {
			for (int j = 1; j <= BOARD_HEIGHT; j++) {
				int n = 0;
				if (_grid_under[i][j] == 9) continue;
				if (_grid_under[i + 1][j] == 9) n++;
				if (_grid_under[i][j + 1] == 9) n++;
				if (_grid_under[i - 1][j] == 9) n++;
				if (_grid_under[i][j - 1] == 9) n++;
				if (_grid_under[i + 1][j + 1] == 9) n++;
				if (_grid_under[i - 1][j - 1] == 9) n++;
				if (_grid_under[i - 1][j + 1] == 9) n++;
				if (_grid_under[i + 1][j - 1] == 9) n++;
				_grid_under[i][j] = n;
				if (rand() % 50 == 0) {
					_grid_upper[i][j] = 10;
				}
			}
		}
	}

	void GameStates::HandleInput() {

		pos = this->_data->input.GetMousePosition(this->_data->window);

		while (_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				_data->window.close();
			}

			if (this->_data->input.IsSpriteClicked(this->_restart, sf::Mouse::Left, this->_data->window)) {
				music.stop();
				this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
			}
			if (event.type == sf::Event::MouseButtonPressed) {

				x = (pos.x - TILE_WIDTH) / (TILE_WIDTH);
				y = (pos.y - 2 * TILE_WIDTH) / (TILE_WIDTH);

				if (x > 0 && x < 20 && y == 1 && !_player->PlayerChosen()) {
					Setup(x);
				}

				if (_player->PlayerChosen()) {
					if (event.key.code == sf::Mouse::Left) {
						_grid_upper[x][y] = 0; //If tile is clicked, it being 0 will later mean it will display texture underneath.
						if (_grid_under[x][y] == 9) {
							life--;
						}
						else if (_grid_upper[x][y] == 10) {
							life++;
						}
					}

					if (event.key.code == sf::Mouse::Right) { //Deals with the flag, that is why we have duplicates
						if (_grid_under[x][y] != 11 && _grid_upper[x][y] != 0) {
							_grid_under[x][y] = 11;
							_grid_upper[x][y] = 0;
							std::cout << _under_duplicate[x][y];
						}
						else if (_grid_under[x][y] == 11) {
							_grid_under[x][y] = _under_duplicate[x][y];
							_grid_upper[x][y] = _upper_duplicate[x][y];
						}
					}
				}
			}
			int result = 0;
			if (event.type == sf::Event::KeyPressed && !_player->PlayerMoving() && _player->PlayerChosen()) {
				if (event.key.code == sf::Keyboard::W && _grid_under[x][y] != 11 && _grid_under[x][y - 1] != 11 && !hasWon) {
					_player->MovePlayer(0, -1, 32);
				}
				if (event.key.code == sf::Keyboard::S && _grid_under[x][y] != 11 && _grid_under[x][y + 1] != 11 && !hasWon) {
					_player->MovePlayer(0, 1, 0);
				}
				if (event.key.code == sf::Keyboard::A && _grid_under[x][y] != 11 && _grid_under[x - 1][y] != 11 && !hasWon) {
					_player->MovePlayer(-1, 0, 64);
				}
				if (event.key.code == sf::Keyboard::D && _grid_under[x][y] != 11 && _grid_under[x + 1][y] != 11 && !hasWon) {
					_player->MovePlayer(1, 0, 96);
				}
				sf::Vector2i currentPos = _player->GetPos();
				x = currentPos.x;
				y = currentPos.y;

				if (y == 20) {
					Win();
				}
				if (_grid_under[x][y] == 9) {
					_player->Explode(x, y, life == 0);
					life--;
				}
				else if (_grid_upper[x][y] == 10) {
					life++;
				}
				_grid_upper[x][y] = 0;
			}
		}
	}

	void GameStates::Update(float dt) {
		_player->Move(dt * 20);
	}

	void GameStates::Draw(float dt) {
		_data->window.draw(_background);

		_life_sprite.setTexture(this->_data->assets.GetTexture("Lifecount"));
		_life_sprite.setTextureRect(sf::IntRect(300, 0, 382, 32));
		_life_sprite.setPosition(310, 880);

		_life_count.setTexture(this->_data->assets.GetTexture("Lifecount"));
		_life_count.setTextureRect(sf::IntRect((life - 1) * TILE_WIDTH, 0, TILE_WIDTH, TILE_WIDTH));
		_life_count.setPosition(390, 880);

		_data->window.draw(_life_count);
		_data->window.draw(_life_sprite);

		for (int i = 1; i <= BOARD_WIDTH; i++) {
			for (int j = 1; j <= BOARD_HEIGHT; j++) {
				//If tile underneath is 9 then it is a mine, and upper grid == 0, hence will show all 
					//Tiles underneath the surface texture, ending the game
				if (_grid_under[x][y] == 9 && _grid_upper[x][y] == 0) {
					if (life == 0) {
						_grid_upper[i][j] = 0;
					}
					if (life == 0) { music.stop(); }
					_player->Explode(x, y, life == 0);
				}// Restart Game

				if (_grid_upper[i][j] == 10) {
					_Shape.setTexture(&this->_data->assets.GetTexture("Tiles"), false);
					_Shape.setTextureRect(sf::IntRect(_grid_upper[i][j] * TILE_WIDTH, 0, TILE_WIDTH, TILE_WIDTH));
				}else if (_grid_upper[i][j] == 0) {
					_Shape.setTexture(&this->_data->assets.GetTexture("Tiles"), false);
					_Shape.setTextureRect(sf::IntRect(_grid_under[i][j] * TILE_WIDTH, 0, TILE_WIDTH, TILE_WIDTH));
				}else { //Else will just draw surface texture
					_Shape.setTexture(&this->_data->assets.GetTexture("Surface"), false);
					_Shape.setTextureRect(sf::IntRect((i-1) * TILE_WIDTH, (j-1) * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH));
				}
				_Shape.setPoint((std::size_t)0, sf::Vector2f((float)0, (float)0));
				_Shape.setPoint((std::size_t)1, sf::Vector2f((float)32, (float)0));
				_Shape.setPoint((std::size_t)2, sf::Vector2f((float)32, (float)32));
				_Shape.setPoint((std::size_t)3, sf::Vector2f((float)0, (float)32));
				_Shape.setPosition((float)((i + 1) * TILE_WIDTH), (float)((j + 2) * TILE_WIDTH));
				_Shape.setOutlineColor(sf::Color(139, 69, 19, 200));
				_Shape.setOutlineThickness(2);
				_data->window.draw(_Shape);
			}
		}
		_data->window.draw(_restart);
		if (_player->PlayerChosen()) {
			_player->Draw();
		}
        _data->window.display();
    }

	void GameStates::Win() {
		hasWon = true;
		_player->MoveOff(x);
	}
}
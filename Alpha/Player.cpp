#include "Game.hpp"
#include "iostream"
#include "DEFINITIONS.hpp"
#include "Player.hpp"

namespace Sarang {

	Player::Player(GameDataRef data) : _data(data) {
		_playerPosInArray = new int* [GRID_SIZE];
		for (int i = 0; i < GRID_SIZE; i++) {
			_playerPosInArray[i] = new int[GRID_SIZE];
			for (int j = 0; j < GRID_SIZE; j++) {
				_playerPosInArray[i][j] = 0; // 0 for Empty space
			}
		}

		_xPosition = 0;
		_yPosition = 0;
		_playerPosInArray[0][0] = 1; // 1 for player in that space
		std::cout << "TILED ARRAY";
		PrintTileArray();

		sf::Texture texture;
		sf::IntRect rectSourceSprite(300, 0, 123, 123);
		this->_data->assets.LoadTexture("Player", PLAYER_WALKING);
		_playerSprite.setTexture(this->_data->assets.GetTexture("Player"));
		_playerSprite.setTextureRect(sf::IntRect(0, 0, 24, 32));
		_playerSprite.setPosition(2 * TILE_WIDTH + 5, 3 * TILE_WIDTH);
	}

	void Player::PrintTileArray() {
		std::cout << std::endl << std::endl;
		for (int x = 0; x < GRID_SIZE; x++) {
			for (int y = 0; y < GRID_SIZE; y++) {
				std::cout << _playerPosInArray[x][y] << " ";
			}
			std::cout << std::endl;
		}
	}

	void Player::SetPos(int x, int y) {
		_playerSprite.setPosition(x, y);
	}

	void Player::MovePlayerDown() {
		if (_yPosition < GRID_SIZE - 1) {
			_playerPosInArray[_yPosition][_xPosition] = 0;
			_yPosition += 1;
			_playerPosInArray[_yPosition][_xPosition] = 1;
			PrintTileArray();

			spriteShown = 0;
			isMoving = true;
			offsetY = TILE_WIDTH;
			offsetX = 0;
			originalPosition = _playerSprite.getPosition();
		}
	}

	void Player::MovePlayerUp() {
		if (_yPosition > 0) {
			_playerPosInArray[_yPosition][_xPosition] = 0;
			_yPosition -= 1;
			_playerPosInArray[_yPosition][_xPosition] = 1;
			PrintTileArray();

			spriteShown = 32;
			isMoving = true;
			offsetY = -TILE_WIDTH;
			offsetX = 0;
			originalPosition = _playerSprite.getPosition();
		}
	}

	void Player::MovePlayerLeft() {
		if (_xPosition > 0) {
			_playerPosInArray[_yPosition][_xPosition] = 0;
			_xPosition -= 1;
			_playerPosInArray[_yPosition][_xPosition] = 1;
			PrintTileArray();

			spriteShown = 64;
			isMoving = true;
			offsetY = 0;
			offsetX = -TILE_WIDTH;
			originalPosition = _playerSprite.getPosition();
		}
	}

	void Player::MovePlayerRight() {
		if (_xPosition < GRID_SIZE - 1) {
			_playerPosInArray[_yPosition][_xPosition] = 0;
			_xPosition += 1;
			_playerPosInArray[_yPosition][_xPosition] = 1;
			PrintTileArray();

			spriteShown = 96;
			isMoving = true;
			offsetY = 0;
			offsetX = TILE_WIDTH;
			originalPosition = _playerSprite.getPosition();
		}
	}

	void Player::CounterWalking() {
		_counterWalking++;
		if (_counterWalking == 7) {
			_counterWalking = 0;
		}
	}

	void Player::Draw() {
		this->_data->window.draw(_playerSprite);
	}

	void Player::Move(float dt) {
	
		sf::Vector2f currentPos = _playerSprite.getPosition();
		sf::Vector2f targetPos = originalPosition + sf::Vector2f(offsetX, offsetY);
		// Pythagoras to find vector difference
		float distance = (sqrt(abs(((targetPos.x - currentPos.x) * (targetPos.x - currentPos.x)) + ((targetPos.y - currentPos.y) * (targetPos.y - currentPos.y)))));

		if (isMoving && distance >= 0.2f) {
			_playerSprite.move(offsetX * dt, offsetY * dt);
			_playerSprite.setTextureRect(sf::IntRect(_counterWalking * 24, spriteShown, 24, 32));
			CounterWalking();
		}
	}
}
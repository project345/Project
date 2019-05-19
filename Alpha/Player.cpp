#include "Game.hpp"
#include "iostream"
#include "DEFINITIONS.hpp"
#include "Player.hpp"

namespace Sarang {

	Player::Player(GameDataRef data, int gridUnder[][22]) : _data(data) {
		for (int i = 0; i < GRID_WIDTH; i++) {
			for (int j = 0; j < GRID_HEIGHT; j++){
				_playerPosInArray[i][j] = gridUnder[i][j];
			}
		}

		std::cout << "TILED ARRAY";
		PrintTileArray();

		sf::Texture texture;
		sf::IntRect rectSourceSprite(300, 0, 123, 123);

		this->_data->assets.LoadTexture("Player", PLAYER_WALKING);

		_playerSprite.setTexture(this->_data->assets.GetTexture("Player"));
		_playerSprite.setTextureRect(sf::IntRect(0, 0, 24, 32));

		isMoving = false;
		ChosenStart = false;
	}

	bool Player::PlayerMoving() {
		return isMoving;
	}

	bool Player::PlayerChosen() {
		return ChosenStart;
	}

	void Player::setPos(int x) {
		ChosenStart = true;
		_xPosition = x;
		_yPosition = 1;
		_playerSprite.setPosition((_xPosition + 1)* TILE_WIDTH + 5, (_yPosition + 2)* TILE_WIDTH);
	}

	void Player::PrintTileArray() {
		std::cout << std::endl << std::endl;
		for (int y = 1; y < GRID_HEIGHT-1; y++) {
			for (int x = 1; x < GRID_WIDTH-1; x++) {
				std::cout << _playerPosInArray[x][y] << " ";
			}
			std::cout << std::endl;
		}
	}

	bool Player::CheckMove(int newX, int newY) {
		// Check if the player has moved into a bomb surrounding player
		if (_playerPosInArray[newX][newY] == 9) { std::cout << "BOMB" << std::endl; return true;}
		return false;
	}

	void Player::MovePlayerDown() {
		if (_yPosition < BOARD_HEIGHT) {
			int result = CheckMove(_xPosition, _yPosition + 1);
			_yPosition += 1;
			spriteShown = 0;
			isMoving = true;
			offsetY = TILE_WIDTH;
			offsetX = 0;
			originalPosition = _playerSprite.getPosition();
		}
	}

	void Player::MovePlayerUp() {
		if (_yPosition > 1) {
			int result = CheckMove(_xPosition, _yPosition - 1);
			_yPosition -= 1;
			spriteShown = 32;
			isMoving = true;
			offsetY = -TILE_WIDTH;
			offsetX = 0;
			originalPosition = _playerSprite.getPosition();
		}
	}

	void Player::MovePlayerLeft() {
		if (_xPosition > 1) {
			int result = CheckMove(_xPosition - 1, _yPosition);
			_xPosition -= 1;
			spriteShown = 64;
			isMoving = true;
			offsetY = 0;
			offsetX = -TILE_WIDTH;
			originalPosition = _playerSprite.getPosition();
		}
	}

	void Player::MovePlayerRight() {
		if (_xPosition < BOARD_WIDTH) {
			int result = CheckMove(_xPosition + 1, _yPosition);
			_xPosition += 1;
			spriteShown = 96;
			isMoving = true;
			offsetY = 0;
			offsetX = TILE_WIDTH;
			originalPosition = _playerSprite.getPosition();
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

			_counterWalking++;

			if (_counterWalking > 7) {
				_counterWalking = 0;
			}
		}else {
			isMoving = false;
		}
	}
}
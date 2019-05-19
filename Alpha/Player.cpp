#include "Game.hpp"
#include "iostream"
#include "DEFINITIONS.hpp"
#include "Player.hpp"

namespace Sarang {

	Player::Player(GameDataRef data, int gridUnder[][22]) : _data(data) {
		// Old way of making the array NOT USED ANYMORE
		//_playerPosInArray = new int* [GRID_HEIGHT];
		/*for (int i = 0; i < GRID_HEIGHT; i++) {
			_playerPosInArray[i] = new int[GRID_WIDTH];
			for (int j = 0; j < GRID_WIDTH; j++) {
				_playerPosInArray[i][j] = 0; // 0 for Empty space
			}
		}*/

		for (int i = 0; i <= 15; i++) {
			for (int j = 0; j <= 20; j++)
			{
				_playerPosInArray[i][j] = gridUnder[i][j];
			}
		}

		_xPosition = 1;
		_yPosition = 1;
		std::cout << "TILED ARRAY" << std::endl;
		//PrintTileArray();

		sf::Texture texture;
		sf::IntRect rectSourceSprite(300, 0, 123, 123);
		this->_data->assets.LoadTexture("Player", PLAYER_WALKING);
		_playerSprite.setTexture(this->_data->assets.GetTexture("Player"));
		_playerSprite.setTextureRect(sf::IntRect(0, 0, 24, 32));
		_playerSprite.setPosition(2 * TILE_WIDTH + 5, 3 * TILE_WIDTH);
	}

	void Player::PrintTileArray() {
		std::cout << std::endl << std::endl;
		for (int y = 0; y < GRID_HEIGHT; y++) {
			for (int x = 0; x < GRID_WIDTH; x++) {
				std::cout << _playerPosInArray[x][y] << " ";
			}
			std::cout << std::endl;
		}
	}

	void Player::SetPos(int x, int y) {
		_playerSprite.setPosition(x, y);
	}

	sf::Vector2i Player::GetPos() {
		sf::Vector2i currentPos = sf::Vector2i(_xPosition, _yPosition);
		return currentPos;
	}

	int Player::CheckSurrounds(int newX, int newY, bool isMove) {
		int result = _playerPosInArray[newX][newY];
		if (isMove && result == 9) {
			// Call to game over
			std::cout << "GAME OVER";
		}
		return result;
	}

	int Player::MovePlayerDown() {
		if (_yPosition < GRID_HEIGHT) {
			int result = CheckSurrounds(_xPosition, _yPosition + 1, true);
			_yPosition += 1;

			spriteShown = 0;
			isMoving = true;
			offsetY = TILE_WIDTH;
			offsetX = 0;
			originalPosition = _playerSprite.getPosition();
			return result;
		}
		return 0;
	}

	int Player::MovePlayerUp() {
		if (_yPosition > 1) {
			int result = CheckSurrounds(_xPosition, _yPosition - 1, true);
			_yPosition -= 1;

			spriteShown = 32;
			isMoving = true;
			offsetY = -TILE_WIDTH;
			offsetX = 0;
			originalPosition = _playerSprite.getPosition();
			return result;
		}
		return 0;
	}

	int Player::MovePlayerLeft() {
		if (_xPosition > 1) {
			int result = CheckSurrounds(_xPosition - 1, _yPosition, true);
			_xPosition -= 1;

			spriteShown = 64;
			isMoving = true;
			offsetY = 0;
			offsetX = -TILE_WIDTH;
			originalPosition = _playerSprite.getPosition();
			return result;
		}
		return 0;
	}

	int Player::MovePlayerRight() {
		if (_xPosition < GRID_WIDTH) {
			int result = CheckSurrounds(_xPosition + 1, _yPosition, true);
			_xPosition += 1;

			spriteShown = 96;
			isMoving = true;
			offsetY = 0;
			offsetX = TILE_WIDTH;
			originalPosition = _playerSprite.getPosition();
			return result;
		}
		return 0;
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
		else {
			isMoving = false;
		}
	}
}
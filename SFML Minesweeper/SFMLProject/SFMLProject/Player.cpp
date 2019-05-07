#include "GameState.h"
#include "iostream"
#include "DEFINITIONS.h"
#include "Player.h"

namespace StewartGames
{
	Player::Player(GameDataRef data) : _data(data) {
		_playerPosInArray = new int*[GRID_SIZE];
		for (int i = 0; i < GRID_SIZE; i++) {
			_playerPosInArray[i] = new int[GRID_SIZE];
			for (int j = 0; j < GRID_SIZE; j++) {
				_playerPosInArray[i][j] = 0; // 0 for Empty space
			}
		}

		_xPosition = 0;
		_yPosition = 0;
		_playerPosInArray[0][0] = 1; // 1 for player in that space

		PrintTileArray();

		sf::Texture texture;
		sf::IntRect rectSourceSprite(300, 0, 123, 123);
		this->_data->assets.LoadTexture("Player", PLAYER_WALKING);
		_playerSprite.setTexture(this->_data->assets.GetTexture("Player"));
		_playerSprite.setTextureRect(sf::IntRect(0, 0, 24, 32));
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

	void Player::MovePlayerDown() {
		if (_yPosition < GRID_SIZE - 1) {
			_playerPosInArray[_yPosition][_xPosition] = 0;
			_yPosition += 1;
			_playerPosInArray[_yPosition][_xPosition] = 1;
			PrintTileArray();
			sf::Vector2f newPos = _playerSprite.getPosition();
			newPos.y += 50;
			
			isMoving = true;
			offsetY = 50;
			offsetX = 0;
			originalPosition = _playerSprite.getPosition();

			/*while (_playerSprite.getPosition() != newPos) {
				_playerSprite.move(0, 1); // need to time by speed and time (dt) maybe move to update
				_playerSprite.setTextureRect(sf::IntRect(_counterWalking * 24, 0, 24, 32));
				CounterWalking();
				std::cout << "WORKING ";
			}*/
		}
	}

	void Player::MovePlayerUp() {
		if (_yPosition > 0) {
			_playerPosInArray[_yPosition][_xPosition] = 0;
			_yPosition -= 1;
			_playerPosInArray[_yPosition][_xPosition] = 1;
			PrintTileArray();
			_playerSprite.move(0, -(SCREEN_HEIGHT / 10));
			_playerSprite.setTextureRect(sf::IntRect(_counterWalking * 24, 32, 24, 32));
			CounterWalking();
		}
	}

	void Player::MovePlayerLeft() {
		if (_xPosition > 0) {
			_playerPosInArray[_yPosition][_xPosition] = 0;
			_xPosition -= 1;
			_playerPosInArray[_yPosition][_xPosition] = 1;
			PrintTileArray();
			_playerSprite.move(-(SCREEN_HEIGHT / 10), 0);
			_playerSprite.setTextureRect(sf::IntRect(_counterWalking * 24, 64, 24, 32));
			CounterWalking();
		}
	}

	void Player::MovePlayerRight() {
		if (_xPosition < GRID_SIZE - 1) {
			_playerPosInArray[_yPosition][_xPosition] = 0;
			_xPosition += 1;
			_playerPosInArray[_yPosition][_xPosition] = 1;
			PrintTileArray();
			_playerSprite.move(SCREEN_HEIGHT / 10, 0);
			_playerSprite.setTextureRect(sf::IntRect(_counterWalking * 24, 96, 24, 32));
			CounterWalking();
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
		
		if (currentPos == targetPos) {
			isMoving = false;
		}
		if (isMoving && currentPos.y <= targetPos.y) {
			_playerSprite.move(offsetX * dt, offsetY * dt);
			_playerSprite.setTextureRect(sf::IntRect(_counterWalking * 24, 0, 24, 32));
			CounterWalking();
		}
	}
}

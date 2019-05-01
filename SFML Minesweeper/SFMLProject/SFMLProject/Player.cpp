#include "GameState.h"
#include "iostream"
#include "DEFINITIONS.h"
#include "Player.h"

namespace StewartGames
{
	Player::Player(GameDataRef data) : _data(data) {

	}

	void Player::Init() {
				
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
			_playerSprite.move(0, SCREEN_HEIGHT / 10);
			_playerSprite.setTextureRect(sf::IntRect(0, 0, 24, 32));
		}
	}

	void Player::MovePlayerUp() {
		if (_yPosition > 0) {
			_playerPosInArray[_yPosition][_xPosition] = 0;
			_yPosition -= 1;
			_playerPosInArray[_yPosition][_xPosition] = 1;
			PrintTileArray();
			_playerSprite.move(0, -(SCREEN_HEIGHT / 10));
			_playerSprite.setTextureRect(sf::IntRect(0, 32, 24, 32));
		}
	}

	void Player::MovePlayerLeft() {
		if (_xPosition > 0) {
			_playerPosInArray[_yPosition][_xPosition] = 0;
			_xPosition -= 1;
			_playerPosInArray[_yPosition][_xPosition] = 1;
			PrintTileArray();
			_playerSprite.move(-(SCREEN_HEIGHT / 10), 0);
			_playerSprite.setTextureRect(sf::IntRect(0, 64, 24, 32));
		}
	}

	void Player::MovePlayerRight() {
		if (_xPosition < GRID_SIZE - 1) {
			_playerPosInArray[_yPosition][_xPosition] = 0;
			_xPosition += 1;
			_playerPosInArray[_yPosition][_xPosition] = 1;
			PrintTileArray();
			_playerSprite.move(SCREEN_HEIGHT / 10, 0);
			_playerSprite.setTextureRect(sf::IntRect(0, 96, 24, 32));
		}
	}

	void Player::Draw() {
		this->_data->window.draw(_playerSprite);
	}
}

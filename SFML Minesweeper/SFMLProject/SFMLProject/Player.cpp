#include "iostream"
#include "Player.h"

namespace StewartGames
{
	Player::Player() {

	}

	void Player::Init() {
				
		_playerPosInArray = new int*[5];
		for (int i = 0; i < 5; i++) {
			_playerPosInArray[i] = new int[5];
			for (int j = 0; j < 5; j++) {
				_playerPosInArray[i][j] = 0; // 0 for Empty space
			}
		}
		
		_xPosition = 0;
		_yPosition = 0;
		_playerPosInArray[0][0] = 1; // 1 for player in that space

		PrintTileArray();
	}

	void Player::PrintTileArray() {
		std::cout << std::endl << std::endl;
		for (int x = 0; x < 5; x++) {
			for (int y = 0; y < 5; y++) {
				std::cout << _playerPosInArray[x][y] << " ";
			}
			std::cout << std::endl;
		}
	}

	void Player::MovePlayerDown() {
		_playerPosInArray[_yPosition][_xPosition] = 0;
		_yPosition += 1;
		_playerPosInArray[_yPosition][_xPosition] = 1;
		PrintTileArray();
	}

	void Player::MovePlayerUp() {
		_playerPosInArray[_yPosition][_xPosition] = 0;
		_yPosition -= 1;
		_playerPosInArray[_yPosition][_xPosition] = 1;
		PrintTileArray();
	}

	void Player::MovePlayerLeft() {
		_playerPosInArray[_yPosition][_xPosition] = 0;
		_xPosition -= 1;
		_playerPosInArray[_yPosition][_xPosition] = 1;
		PrintTileArray();
	}

	void Player::MovePlayerRight() {
		_playerPosInArray[_yPosition][_xPosition] = 0;
		_xPosition += 1;
		_playerPosInArray[_yPosition][_xPosition] = 1;
		PrintTileArray();
	}
}

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
	}

	void Player::MovePlayerDown() {
		_yPosition += 1;
		_playerPosInArray[_xPosition][_yPosition] = 1;
		_playerPosInArray[_xPosition][_yPosition - 1] = 0;
	}

	void Player::MovePlayerUp() {

	}

	void Player::MovePlayerLeft() {

	}

	void Player::MovePlayerRight() {

	}
}

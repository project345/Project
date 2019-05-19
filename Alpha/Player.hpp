#pragma once

#define PLAYER_IN_SPACE = 1
#define EMPTY_SPACE = 0

namespace Sarang {

	class Player {
	public:
		Player(GameDataRef data, int gridUnder[][22]);
		void PrintTileArray();
		void MovePlayerDown();
		void MovePlayerUp();
		void MovePlayerLeft();
		void MovePlayerRight();
		void Draw();
		void Move(float dt);
		void setPos(int x);
		bool CheckMove(int newX, int newY); //Checks if there is bomb
		bool PlayerMoving();
		bool PlayerChosen();

	private:
		GameDataRef _data;

		sf::Sprite _playerSprite;

		sf::Vector2f originalPosition;

		int _playerPosInArray[17][22];
		int _counterWalking = 0;
		int offsetX;
		int offsetY;
		int spriteShown;
		int _xPosition;
		int _yPosition;
		bool isMoving;
		bool ChosenStart;
	};

}
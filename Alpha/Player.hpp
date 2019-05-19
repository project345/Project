#pragma once

#define PLAYER_IN_SPACE = 1
#define EMPTY_SPACE = 0

namespace Sarang {

	class Player {
	public:
		Player(GameDataRef data, int gridUnder[][22]);

		void PrintTileArray();
		int MovePlayerDown();
		int MovePlayerUp();
		int MovePlayerLeft();
		int MovePlayerRight();
		void CounterWalking();
		void Draw();
		void Move(float dt);
		void SetPos(int x, int y);
		int CheckSurrounds(int newX, int newY, bool isMove = false);
		bool isMoving;

		sf::Vector2i GetPos();
	private:
		GameDataRef _data;
		int _playerPosInArray[17][22];
		int _xPosition;
		int _yPosition;
		int _counterWalking = 0;
		int offsetX;
		int offsetY;
		sf::Vector2f originalPosition;
		int spriteShown;
		sf::Sprite _playerSprite;
	};

}
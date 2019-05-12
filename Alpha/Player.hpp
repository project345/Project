#pragma once

#define PLAYER_IN_SPACE = 1
#define EMPTY_SPACE = 0

namespace Sarang {

	class Player
	{
	public:
		Player(GameDataRef data);

		void PrintTileArray();
		void MovePlayerDown();
		void MovePlayerUp();
		void MovePlayerLeft();
		void MovePlayerRight();

		void CounterWalking();
		void Draw();

		void Move(float dt);

	private:
		GameDataRef _data;

		int** _playerPosInArray;

		int _xPosition;
		int _yPosition;

		int _counterWalking = 0;
		bool isMoving;

		int offsetX;
		int offsetY;
		sf::Vector2f originalPosition;

		int spriteShown;

		sf::Sprite _playerSprite;
	};

}
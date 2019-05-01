#pragma once

#define PLAYER_IN_SPACE = 1
#define EMPTY_SPACE = 0

namespace StewartGames
{
	class Player
	{
	public:
		Player(GameDataRef data);
		void Init();

		void PrintTileArray();
		void MovePlayerDown();
		void MovePlayerUp();
		void MovePlayerLeft();
		void MovePlayerRight();

		void CounterWalking();
		void Draw();

	private:
		GameDataRef _data;
		
		int** _playerPosInArray;

		int _xPosition;
		int _yPosition;

		int _counterWalking = 0;

		sf::Sprite _playerSprite;
	};
}


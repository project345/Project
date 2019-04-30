#pragma once

namespace StewartGames
{
	class Player
	{
	public:
		Player();
		void Init();

		void PrintTileArray();
		void MovePlayerDown();
		void MovePlayerUp();
		void MovePlayerLeft();
		void MovePlayerRight();

	private:
		int** _playerPosInArray;

		int _xPosition;
		int _yPosition;
	};
}


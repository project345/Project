#pragma once

namespace Sarang {

	class Player {
	public:
		Player(GameDataRef data, int gridUnder[][22]);
		int MovePlayer(int newX, int newY, int spriteShown);
		void Draw();
		void Move(float dt);
		void setPos(int x);
		sf::Vector2i GetPos();
		int CheckMove(int newX, int newY); //Checks if there is bomb
		bool PlayerMoving();
		bool PlayerChosen();
		
	private:
		GameDataRef _data;
		sf::Sprite _playerSprite;
		sf::Sprite _explosionSprite;
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
		bool _isExplosion;
	};

}
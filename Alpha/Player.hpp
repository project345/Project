#pragma once

namespace MESSY {

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
		sf::Sprite playerSprite, explosionSprite;
		sf::Vector2f originalPosition;
		int _playerPosInArray[17][22];
		int offsetX, offsetY, spriteShown, xPosition, yPosition, counterWalking = 0;
		bool isMoving, chosenStart, isExplosion;
	};
}
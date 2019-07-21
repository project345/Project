#pragma once

namespace MESY {

	class Player {
	public:
		Player(GameDataRef data);
		void MovePlayer(int newX, int newY, int spriteShown);
		void Draw();
		void Move(float dt);
		void setPos(int x);
		sf::Vector2i GetPos();
		void Explode(int newX, int newY);
		bool PlayerMoving();
		bool PlayerChosen();
		
	private:
		GameDataRef _data;
		sf::Sprite playerSprite, explosionSprite;
		sf::Vector2f originalPosition;
		int offsetX, offsetY, spriteShown, xPosition, yPosition, counterWalking = 0;
		bool isMoving, chosenStart, isExplosion;
	};
}
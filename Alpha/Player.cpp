#include "Game.hpp"
#include "iostream"
#include "DEFINITIONS.hpp"
#include "Player.hpp"

namespace MESY {

	Player::Player(GameDataRef data, int gridUnder[][22]) : _data(data) {
		for (int i = 0; i < GRID_WIDTH; i++) {
			for (int j = 0; j < GRID_HEIGHT; j++){
				_playerPosInArray[i][j] = gridUnder[i][j];
			}
		}

		sf::Texture texture;
		sf::IntRect rectSourceSprite(300, 0, 123, 123);

		this->_data->assets.LoadTexture("Player", PLAYER_WALKING);
		this->_data->assets.LoadTexture("Explosion", EXPLOSION_FILEPATH);

		playerSprite.setTexture(this->_data->assets.GetTexture("Player"));
		playerSprite.setTextureRect(sf::IntRect(0, 0, 24, 32));
		explosionSprite.setTexture(this->_data->assets.GetTexture("Explosion"));
		explosionSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));

		isMoving = false;
		chosenStart = false;
	}

	bool Player::PlayerMoving() {
		return isMoving;
	}

	bool Player::PlayerChosen() {
		return chosenStart;
	}

	void Player::setPos(int x) {
		chosenStart = true;
		xPosition = x;
		yPosition = 1;
		playerSprite.setPosition((float)((xPosition + 1)* TILE_WIDTH + 5), (float)((yPosition + 2)* TILE_WIDTH));
	}

	sf::Vector2i Player::GetPos()
	{
		return sf::Vector2i(xPosition, yPosition);
	}

	int Player::CheckMove(int newX, int newY) {
		if (_playerPosInArray[newX][newY] == 9) {
			isExplosion = true;
			explosionSprite.setPosition((float)(((newX + 1) * TILE_WIDTH) - (32 / 2)), (float)(((newY + 2) * TILE_WIDTH) - (32 / 2)));
		}
		return _playerPosInArray[newX][newY];
	}

	int Player::MovePlayer(int newX, int newY, int spriteShown) {
		bool isValid = false;
		if (newY == -1 && yPosition > 1) {
			isValid = true;
		}
		if (newY == 1 && yPosition < BOARD_HEIGHT) {
			isValid = true;
		}
		if (newX == -1 && xPosition > 1) {
			isValid = true;
		}
		if (newX == 1 && xPosition < BOARD_WIDTH) {
			isValid = true;
		}
		if(isValid){
			int result = CheckMove(xPosition + newX, yPosition + newY);
			yPosition += newY;
			xPosition += newX;
			this->spriteShown = spriteShown;
			isMoving = true;
			offsetX = newX * TILE_WIDTH;
			offsetY = newY * TILE_WIDTH;
			originalPosition = playerSprite.getPosition();
			return result;
		}
		return 0;
	}

	void Player::Draw() {
		this->_data->window.draw(playerSprite);
		if (isExplosion) {
			this->_data->window.draw(explosionSprite);
		}
	}

	void Player::Move(float dt) {
		sf::Vector2f currentPos = playerSprite.getPosition();
		sf::Vector2f targetPos = originalPosition + sf::Vector2f((float)offsetX, (float)offsetY);
		float distance = (sqrt(abs(((targetPos.x - currentPos.x) * (targetPos.x - currentPos.x)) + ((targetPos.y - currentPos.y) * (targetPos.y - currentPos.y))))); // Pythagoras to find vector difference
		if (isMoving && distance >= 0.2f) {
			playerSprite.move((offsetX/2) * dt, (offsetY/2) * dt);
			playerSprite.setTextureRect(sf::IntRect(counterWalking * 24, spriteShown, 24, 32));
			counterWalking++;
			if (counterWalking > 7) {
				counterWalking = 0;
			}
		} else {
			isMoving = false;
		}
	}
}
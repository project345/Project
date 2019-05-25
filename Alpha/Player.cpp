#include "Game.hpp"
#include "iostream"
#include "DEFINITIONS.hpp"
#include "Player.hpp"

namespace Sarang {

	Player::Player(GameDataRef data, int gridUnder[][22]) : _data(data) {
		for (int i = 0; i < GRID_WIDTH; i++) {
			for (int j = 0; j < GRID_HEIGHT; j++){
				_playerPosInArray[i][j] = gridUnder[i][j];
			}
		}

		std::cout << "TILED ARRAY";

		sf::Texture texture;
		sf::IntRect rectSourceSprite(300, 0, 123, 123);

		this->_data->assets.LoadTexture("Player", PLAYER_WALKING);
		this->_data->assets.LoadTexture("Explosion", EXPLOSION_FILEPATH);

		_playerSprite.setTexture(this->_data->assets.GetTexture("Player"));
		_playerSprite.setTextureRect(sf::IntRect(0, 0, 24, 32));
		_explosionSprite.setTexture(this->_data->assets.GetTexture("Explosion"));
		_explosionSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));

		isMoving = false;
		ChosenStart = false;
	}

	bool Player::PlayerMoving() {
		return isMoving;
	}

	bool Player::PlayerChosen() {
		return ChosenStart;
	}

	void Player::setPos(int x) {
		ChosenStart = true;
		_xPosition = x;
		_yPosition = 1;
		_playerSprite.setPosition((_xPosition + 1)* TILE_WIDTH + 5, (_yPosition + 2)* TILE_WIDTH);
	}

	sf::Vector2i Player::GetPos()
	{
		sf::Vector2i currentPos = sf::Vector2i(_xPosition, _yPosition);
		return currentPos;
	}

	void Player::PrintTileArray() {
		std::cout << std::endl << std::endl;
		for (int y = 1; y < GRID_HEIGHT-1; y++) {
			for (int x = 1; x < GRID_WIDTH-1; x++) {
				std::cout << _playerPosInArray[x][y] << " ";
			}
			std::cout << std::endl;
		}
	}

	int Player::CheckMove(int newX, int newY) {
		if (_playerPosInArray[newX][newY] == 9) {
			_isExplosion = true;
			std::cout << _playerPosInArray[newX][newY] << std::endl;
			_explosionSprite.setPosition(((newX + 1) * TILE_WIDTH) - (32 / 2), ((newY + 2) * TILE_WIDTH) - (32 / 2));
		}
		return _playerPosInArray[newX][newY];
	}

	int Player::MovePlayer(int newX, int newY, int spriteShown) {
		bool isValid = false;
		if (newY == -1 && _yPosition > 1) {
			isValid = true;
		}
		if (newY == 1 && _yPosition < BOARD_HEIGHT) {
			isValid = true;
		}
		if (newX == -1 && _xPosition > 1) {
			isValid = true;
		}
		if (newX == 1 && _xPosition < BOARD_WIDTH) {
			isValid = true;
		}
		if(isValid){
			int result = CheckMove(_xPosition + newX, _yPosition + newY);
			_yPosition += newY;
			_xPosition += newX;
			this->spriteShown = spriteShown;
			isMoving = true;
			offsetX = newX * TILE_WIDTH;
			offsetY = newY * TILE_WIDTH;
			originalPosition = _playerSprite.getPosition();
			
			return result;
		}
		return 0;
	}

	void Player::Draw() {
		this->_data->window.draw(_playerSprite);
		if (_isExplosion) {
			this->_data->window.draw(_explosionSprite);
		}
	}

	void Player::Move(float dt) {
	
		sf::Vector2f currentPos = _playerSprite.getPosition();
		sf::Vector2f targetPos = originalPosition + sf::Vector2f(offsetX, offsetY);
		float distance = (sqrt(abs(((targetPos.x - currentPos.x) * (targetPos.x - currentPos.x)) + ((targetPos.y - currentPos.y) * (targetPos.y - currentPos.y))))); // Pythagoras to find vector difference
		if (isMoving && distance >= 0.2f) {
			_playerSprite.move((offsetX/2) * dt, (offsetY/2) * dt);
			_playerSprite.setTextureRect(sf::IntRect(_counterWalking * 24, spriteShown, 24, 32));
			_counterWalking++;
			if (_counterWalking > 7) {
				_counterWalking = 0;
			}
		}else {
			isMoving = false;
		}
	}
}
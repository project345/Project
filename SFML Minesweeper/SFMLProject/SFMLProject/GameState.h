#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "Player.h"

namespace StewartGames
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Clock _clock;

		sf::Sprite _background;

		Player *_player;

		int** _tiles;

		int currentXPos = 0;
		int currentYPos = 1;

		sf::Sprite spriteMain;

	};
}
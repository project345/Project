#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Player.hpp"

namespace MESY {
    class GameStates : public State {
    public:
        GameStates(GameDataRef data, int x);
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
		void Setup(int x);
		void Win();
        
    private:
        GameDataRef _data;
		Player* _player;
		sf::ConvexShape _Shape;
		sf::Texture _under, _upper;
		sf::Event event;
		sf::Vector2i pos;
		sf::Sprite _restart, _background;
		int _grid_under[GRID_WIDTH][GRID_HEIGHT], _grid_upper[GRID_WIDTH][GRID_HEIGHT], _under_duplicate[GRID_WIDTH][GRID_HEIGHT], _upper_duplicate[GRID_WIDTH][GRID_HEIGHT];
		int x, y, x0, x1, x2, y0, y1, y2, GameState;
		double gradient = 48 / 32;
		bool hasWon = false;
    };
}
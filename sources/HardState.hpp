#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace Sarang{
    class HardState : public State{
    public:
        HardState(GameDataRef data);
        
        void Init();
        
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
        
    private:
        GameDataRef _data;
        
        sf::Clock _clock;
        
		sf::Event event;

		sf::Vector2i pos;

		sf::ConvexShape _triangle;

		sf::Sprite _restart;
		sf::Sprite _background;

		int _grid_under[17][22];
		int _grid_upper[17][22];
		int _under_duplicate[17][22];
		int _upper_duplicate[17][22];
		
		sf::Texture _under;
		sf::Texture _upper;

		int x, y, x0, x1, x2, y0, y1, y2;;
    };
}





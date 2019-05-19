#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Player.hpp"

namespace Sarang{
    class EasyState : public State{
    public:
        EasyState(GameDataRef data);
        
        void Init();
        
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);

		void RemoveUpperTile(int result, int xPos, int yPos);
        
    private:
        GameDataRef _data;

		sf::Event event;

		sf::Vector2i pos;

		sf::Texture _under;
		sf::Texture _upper;

        sf::Clock _clock;
        sf::Sprite _restart;
		sf::Sprite _surface;
		sf::Sprite _hidden;
		sf::Sprite _background;
        
        int grid_upper[17][22];
        int grid_under[17][22];
        int x, y;

		// Player
		Player* _player;

		int xPos = 1;
		int yPos = 1;
    };
}

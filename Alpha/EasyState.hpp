#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Player.hpp"

namespace MESSY {
    class EasyState : public State {
    public:
        EasyState(GameDataRef data);
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
		void RemoveUpperTile(int xPos, int yPos);
		void Setup(int x);
        
    private:
        GameDataRef _data;
		Player* _player;
		sf::Sprite _restart, _surface, _hidden, _background;
		sf::Texture _under, _upper;
		sf::Event event;
		sf::Vector2i pos;
        sf::Clock _clock;
        int grid_upper[17][22], grid_under[17][22];
        int x = 0, y = 0;
		int xPos, yPos;
    };
}
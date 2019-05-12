#include <sstream>
#include <time.h>
#include "SplashState.hpp"
#include "DEFINITIONS.hpp"
#include "EasyState.hpp"
#include "MainMenuState.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Sarang{
    EasyState::EasyState(GameDataRef data) : _data(data){
        
    }
    
    void EasyState::Init(){
	
		this->_data->assets.LoadTexture("Restart Button", RESTART_FILEPATH);
		this->_data->assets.LoadTexture("Surface", DESERT_FILEPATH);
		this->_data->assets.LoadTexture("Mines", TILES_FILEPATH);
		this->_data->assets.LoadTexture("Background", BOARD_BACKGROUND_FILEPATH);

		_restart.setTexture(this->_data->assets.GetTexture("Restart Button"));
		_hidden.setTexture(this->_data->assets.GetTexture("Mines"));
		_surface.setTexture(this->_data->assets.GetTexture("Surface"));
		_background.setTexture(this->_data->assets.GetTexture("Background"));
		
		sf::Vector2f targetSize1(100.0f, 70.0f);

		_restart.setScale(
			targetSize1.x / _restart.getLocalBounds().width,
			targetSize1.y / _restart.getLocalBounds().height);

		_restart.setPosition(SCREEN_WIDTH / 2 - (_restart.getGlobalBounds().width / 2), 13);

		_surface.setPosition(0, _surface.getGlobalBounds().height/2);

		sf::Vector2f targetSize(1920.0f / 1.5, 1280.0f / 1.5);

		_background.setScale(
			targetSize.x / _background.getLocalBounds().width,
			targetSize.y / _background.getLocalBounds().height);

		_background.setPosition(-315, -50);
		
		for (int i = 1; i <= 15; i++)
			for (int j = 1; j <= 20; j++)
			{
				grid_upper[i][j] = (rand() % 9) + 12;
				if (rand() % 5 == 0) { grid_under[i][j] = 9; }
				else { grid_under[i][j] = 0; }
			}

		/*
			This calculates how many mines are beside the current tile,
			giving the tile the proper number.
		*/
		for (int i = 1; i <= 15; i++)
			for (int j = 1; j <= 20; j++)
			{
				int n = 0;
				if (grid_under[i][j] == 9) continue;
				if (grid_under[i + 1][j] == 9) n++;
				if (grid_under[i][j + 1] == 9) n++;
				if (grid_under[i - 1][j] == 9) n++;
				if (grid_under[i][j - 1] == 9) n++;
				if (grid_under[i + 1][j + 1] == 9) n++;
				if (grid_under[i - 1][j - 1] == 9) n++;
				if (grid_under[i - 1][j + 1] == 9) n++;
				if (grid_under[i + 1][j - 1] == 9) n++;
				grid_under[i][j] = n;
			}
    }
    
    void EasyState::HandleInput(){
        
		pos = this->_data->input.GetMousePosition(this->_data->window);

		x = (pos.x - TILE_WIDTH) / TILE_WIDTH;
		y = (pos.y - 2*TILE_WIDTH) / TILE_WIDTH;
        
        while(_data->window.pollEvent(event)){
            
			if(sf::Event::Closed == event.type){
                _data->window.close();
            }
            
            if(this->_data->input.IsSpriteClicked(this->_restart, sf::Mouse::Left, this->_data->window)){
                this->_data->machine.AddState(StateRef(new MainMenuState(_data)),true);
            }
			if (event.type == sf::Event::MouseButtonPressed){
				grid_upper[x][y] = 0; //If tile is clicked, it being 0 will later mean it will display texture underneath.
				if (event.key.code == sf::Mouse::Right) grid_under[x][y] = 11;
			}
        }        
    }       
    
    void EasyState::Update(float dt){
        
    }
    
    void EasyState::Draw(float dt){
        _data->window.clear(sf::Color::Magenta);
        
		_data->window.draw(_background);

		for (int i = 1; i <= 15; i++)
			for (int j = 1; j <= 20; j++)
			{
				//If tile underneath is 9 then it is a mine, and upper grid == 0, hence will show all 
				//Tiles underneath the surface texture, ending the game
				if (grid_under[x][y] == 9 && grid_upper[x][y] == 0) { grid_upper[i][j] = 0; }

				//Will draw texture underneath
				if (grid_upper[i][j] == 0)
				{
					_hidden.setTextureRect(sf::IntRect(grid_under[i][j] * TILE_WIDTH, 0, TILE_WIDTH, TILE_WIDTH));
					_hidden.setPosition((i + 1) * TILE_WIDTH, (j + 2) * TILE_WIDTH);
					_data->window.draw(_hidden);
				}
				//Else will just draw surface texture
				else {
					_surface.setTextureRect(sf::IntRect(grid_upper[i][j] * TILE_WIDTH, 0, TILE_WIDTH, TILE_WIDTH));
					_surface.setPosition((i + 1) * TILE_WIDTH, (j + 2) * TILE_WIDTH);
					_data->window.draw(_surface);
				}
			}
		
		_data->window.draw(_restart);

        _data->window.display();
    }
}



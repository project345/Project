#include <sstream>
#include "DEFINITIONS.hpp"
#include "HardState.hpp"
#include "MainMenuState.hpp"

#include <iostream>

namespace Sarang{
    HardState::HardState(GameDataRef data) : _data(data){
        
    }
    
    void HardState::Init(){
        this->_data->assets.LoadTexture("Restart Button", RESTART_FILEPATH);
		this->_data->assets.LoadTexture("Background", BOARD_BACKGROUND_FILEPATH);
         
        _restart.setTexture(this->_data->assets.GetTexture("Restart Button"));
		_background.setTexture(this->_data->assets.GetTexture("Background"));

		_under.loadFromFile(TILES_FILEPATH);
		_upper.loadFromFile(DONALD_TRUMP);
        

        _restart.setPosition(SCREEN_WIDTH/2 - (_restart.getGlobalBounds().width/2), SCREEN_HEIGHT*0.001);

		_triangle.setPointCount(3);

		sf::Vector2f targetSize1(100.0f, 70.0f);

		_restart.setScale(
			targetSize1.x / _restart.getLocalBounds().width,
			targetSize1.y / _restart.getLocalBounds().height);

		_restart.setPosition(SCREEN_WIDTH / 2 - (_restart.getGlobalBounds().width / 2), 13);

		sf::Vector2f targetSize(1920.0f / 1.5, 1280.0f / 1.5);

		_background.setScale(
			targetSize.x / _background.getLocalBounds().width,
			targetSize.y / _background.getLocalBounds().height);

		_background.setPosition(-315, -50);
		/*
		The first part randomly puts a section of desert.jpg to the tile.
		Next part decides randomly 1/5 times whether to
		put a mine in the current tile.
	*/
		for (int i = 1; i <= 15; i++)
			for (int j = 1; j <= 20; j++)
			{
				_grid_upper[i][j] = (rand() % 9) + 12;

				//the first if makes it so there are no mines at the top middle
				//giving the player a starting point
				if (i < 6 && j != 1 || i > 10 && j != 1 || i < 7 && j > 2 || i > 9 && j > 2) {
					if (rand() % 5 == 0) {_grid_under[i][j] = 9; }
					else {_grid_under[i][j] = 0; }
				}
			}

		/*
			This calculates how many mines are beside the current tile,
			giving the tile the proper number.
		*/
		for (int i = 1; i <= 15; i++)
			for (int j = 1; j <= 20; j++)
			{
				int n = 0;
				if (_grid_under[i][j] == 9) continue;
				if (_grid_under[i + 1][j] == 9) n++;
				if (_grid_under[i][j + 1] == 9) n++;
				if (_grid_under[i - 1][j] == 9) n++;
				if (_grid_under[i][j - 1] == 9) n++;
				if (_grid_under[i + 1][j + 1] == 9) n++;
				if (_grid_under[i - 1][j - 1] == 9) n++;
				if (_grid_under[i - 1][j + 1] == 9) n++;
				if (_grid_under[i + 1][j - 1] == 9) n++;
				/*
					Below are needed for the triangle minesweeper
					Triangle minesweeper has more blocks connected
					to each individual block so we need to change the number
					presented in each triangle
				*/
				if (i % 2 != 0 && j % 2 != 0 || i % 2 == 0 && j % 2 == 0) {
					if (_grid_under[i - 2][j] == 9) n++;
					if (_grid_under[i + 2][j] == 9) n++;
					if (_grid_under[i - 2][j + 1] == 9) n++;
					if (_grid_under[i + 2][j + 1] == 9) n++;
				}
				else if (i % 2 == 0 && j % 2 != 0 || i % 2 != 0 && j % 2 == 0) {
					if (_grid_under[i - 2][j] == 9) n++;
					if (_grid_under[i + 2][j] == 9) n++;
					if (_grid_under[i - 2][j - 1] == 9) n++;
					if (_grid_under[i + 2][j - 1] == 9) n++;
				}
				_grid_under[i][j] = n;
			}
		for (int i = 0; i < 17; i++)
			for (int j = 0; j < 22; j++)
			{
				_under_duplicate[i][j] = _grid_under[i][j];
			}

		for (int i = 0; i < 17; i++)
			for (int j = 0; j < 22; j++)
			{
				_upper_duplicate[i][j] = _grid_upper[i][j];
			}
    }
    
    void HardState::HandleInput(){
		pos = this->_data->input.GetMousePosition(this->_data->window);
        
		x = (pos.x - TILE_WIDTH) / (TILE_WIDTH);
		y = (pos.y - 2 * TILE_WIDTH) / (TILE_WIDTH);

        while(_data->window.pollEvent(event)){
            if(sf::Event::Closed == event.type){
                _data->window.close();
            }
            
            if(this->_data->input.IsSpriteClicked(this->_restart, sf::Mouse::Left, this->_data->window)){
                this->_data->machine.AddState(StateRef(new MainMenuState(_data)),true);
            }
            
			if (event.type == sf::Event::MouseButtonPressed)
			{
				_grid_upper[x][y] = 0; //If tile is clicked, it being 0 will later mean it will display texture underneath.
				if (event.key.code == sf::Mouse::Right)
				{
					if (_grid_under[x][y] != 11) {
						_grid_under[x][y] = 11;
					}
					else {
						_grid_under[x][y] = _under_duplicate[x][y];
						_grid_upper[x][y] = _upper_duplicate[x][y];
					}
				}
			}
        }
    }
    void HardState::Update(float dt){
        
    }
    void HardState::Draw(float dt){
        _data->window.clear(sf::Color::Yellow);
        
		_data->window.draw(_background);

		for (int i = 1; i <= 15; i++)
			for (int j = 1; j <= 20; j++)
			{
				//If tile underneath is 9 then it is a mine, and upper grid == 0, hence will show all 
				//Tiles underneath the surface texture, ending the game
				if (_grid_under[x][y] == 9 && _grid_upper[x][y] == 0) {_grid_upper[i][j] = 0; }

				//Will draw texture underneath
				if (_grid_upper[i][j] == 0)
				{
					/*
						For triangle below(hidden surface texture with numbers and shit):
					*/
					if (i % 2 != 0 && j % 2 != 0 || i % 2 == 0 && j % 2 == 0) {
						x0 = 16, y0 = 0, x1 = -16, y1 = 32, x2 = 48, y2 = 32;
					}
					else if (i % 2 == 0 && j % 2 != 0 || i % 2 != 0 && j % 2 == 0) {
						x0 = 16, y0 = 32, x1 = -16, y1 = 0, x2 = 48, y2 = 0;
					}

					_triangle.setTextureRect(sf::IntRect(_grid_under[i][j] * TILE_WIDTH, 0, TILE_WIDTH, TILE_WIDTH));
					_triangle.setTexture(&_under, false);
				}
				//Else will just draw surface texture
				else {
					/*
						For triangle below(surface texture:
					*/
					if (i % 2 != 0 && j % 2 != 0 || i % 2 == 0 && j % 2 == 0) {
						x0 = 16, y0 = 0, x1 = -16, y1 = 32, x2 = 48, y2 = 32;
						_triangle.setTextureRect(sf::IntRect((i + 1) * 30 * 4, j * 32 * 4, 60 * 4, 32 * 4));
						_triangle.setTexture(&_upper, false);
					}
					else if (i % 2 == 0 && j % 2 != 0 || i % 2 != 0 && j % 2 == 0) {
						x0 = 16, y0 = 32, x1 = -16, y1 = 0, x2 = 48, y2 = 0;

						//This ensures that the middle point is already cleared for the starting point
						if (i == 8 && j == 1) {
							_triangle.setTexture(&_under, false);
							_triangle.setTextureRect(sf::IntRect((i + 1) * 30 * 4, j * 32 * 4, 60 * 4, 32 * 4));
						}
						else {
							_triangle.setTexture(&_upper, false);
							_triangle.setTextureRect(sf::IntRect((i + 1) * 30 * 4, j * 32 * 4, 60 * 4, 32 * 4));
						}
					}
				}
				_triangle.setPoint(0, sf::Vector2f(x0, y0));
				_triangle.setPoint(1, sf::Vector2f(x1, y1));
				_triangle.setPoint(2, sf::Vector2f(x2, y2));
				_triangle.setPosition((i + 1) * TILE_WIDTH, (j + 2) * TILE_WIDTH);
				_triangle.setOutlineColor(sf::Color(139, 69, 19, 200));
				_triangle.setOutlineThickness(2);
				_data->window.draw(_triangle);
			}

		_data->window.draw(_restart);
		_data->window.display();
       
    }
}



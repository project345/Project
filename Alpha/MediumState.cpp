#include <sstream>
#include "DEFINITIONS.hpp"
#include "MediumState.hpp"
#include "MainMenuState.hpp"

#include <iostream>

namespace Sarang{
    MediumState::MediumState(GameDataRef data) : _data(data){ 
		_data->assets.LoadTexture("Restart Button", RESTART_FILEPATH);
		_data->assets.LoadTexture("under", TILES_FILEPATH);
		_data->assets.LoadTexture("upper", DESERT_FILEPATH);

		_restart.setTexture(this->_data->assets.GetTexture("Restart Button"));
		_hidden.setTexture(this->_data->assets.GetTexture("under"));
		_surface.setTexture(this->_data->assets.GetTexture("upper"));

		_restart.setPosition(SCREEN_WIDTH / 2 - (_restart.getGlobalBounds().width / 2), SCREEN_HEIGHT * 0.001);
		_surface.setPosition(0, _surface.getGlobalBounds().height / 2);
	}
    
    void MediumState::HandleInput(){
        sf::Event event;
        
        while(_data->window.pollEvent(event)){
            if(sf::Event::Closed == event.type){
                _data->window.close();
            }
            
            if(this->_data->input.IsSpriteClicked(this->_restart, sf::Mouse::Left, this->_data->window)){
                this->_data->machine.AddState(StateRef(new MainMenuState(_data)),true);
            }
            
            if(sf::Event::MouseButtonPressed == event.type){
                
            }
        }
    }
    void MediumState::Update(float dt){
        
    }
    void MediumState::Draw(float dt){
        _data->window.clear(sf::Color::Cyan);
        
        _data->window.draw(_restart);
        _data->window.draw(_hidden);
        _data->window.draw(_surface);
        _data->window.display();
    }
}


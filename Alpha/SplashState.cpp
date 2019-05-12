#include <sstream>
#include "SplashState.hpp"
#include "DEFINITIONS.hpp"
#include "MediumState.hpp"
#include "MainMenuState.hpp"

#include <iostream>

namespace Sarang{
    SplashState::SplashState(GameDataRef data) : _data(data){
        
    }
    
    void SplashState::Init(){
        _data->assets.LoadTexture("Splash State Screen", SPLASH_BACKGROUND_FILEPATH);
        
        _background.setTexture(this->_data->assets.GetTexture("Splash State Screen"));
		
		sf::Vector2f targetSize(630.0f, 350.0f);
	
		_background.setScale(
			targetSize.x / _background.getLocalBounds().width,
			targetSize.y / _background.getLocalBounds().height);

		_background.setPosition(-10, 200);
    }
    
    void SplashState::HandleInput(){
        sf::Event event;
        
        while(_data->window.pollEvent(event)){
            if(sf::Event::Closed == event.type){
                _data->window.close();
            }
        }
    }
    void SplashState::Update(float dt)
    {
        if(this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME){
            this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
        }
    }
    void SplashState::Draw(float dt){
        _data->window.clear();
        _data->window.draw(_background);
        _data->window.display();
    }
}


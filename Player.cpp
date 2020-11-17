#include "Player.h"

using namespace std;

Player::Player(){
	t.loadFromFile("player.png");
	s.setTexture(t);
	s.setPosition(175, 130);
	speed = Vector2f(0,0);
}

void Player::draw(sf::RenderTarget& w, sf::RenderStates states = RenderStates::Default) const{
	w.draw(s, states);
}

void Player::Update(){
	if(!landed){
		speed = Vector2f(speed.x, speed.y + 9.8f/60);
	}
	if(Keyboard::isKeyPressed(sf::Keyboard::Right)){
		speed.x = 2;
	}
	else if(Keyboard::isKeyPressed(sf::Keyboard::Left)){
		speed.x = -2;
	}
	else{
		speed.x = 0;
	}
}

void Player::Move(){
	s.move(speed);
}

void Player::Collision(Floor floor){
	FloatRect boxPlayer = s.getGlobalBounds();
	FloatRect boxFloor = floor.GetRect();
	if(boxPlayer.intersects(boxFloor)){
		// x
		//Si esta "adentro" no evalua
		if(!((boxPlayer.left + boxPlayer.width - boxFloor.left < 0) && (boxPlayer.left - boxFloor.left + boxFloor.width < 0))){
			if(fabs(boxPlayer.left + boxPlayer.width - boxFloor.left)
			   < fabs(boxPlayer.left - boxFloor.left + boxFloor.width)){
				if(boxPlayer.left + boxPlayer.width >= boxFloor.left){
					speed.x = 0;
				}
			} else {
				if(boxPlayer.left <= boxFloor.left + boxFloor.width){
					speed.x = 0;
				}
			}
		}
		
		// y
		if(boxPlayer.top + boxPlayer.height >= boxFloor.top){
				speed.y = 0;
				landed = true;
		}else{
			landed = false;
		}
	}
}

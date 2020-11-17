#include "Player.h"

using namespace std;

Player::Player(){
	t.loadFromFile("player.png");
	s.setTexture(t);
	s.setPosition(500, 130);
	speed = Vector2f(0,0);
	landed = false;
}

void Player::draw(sf::RenderTarget& w, sf::RenderStates states = RenderStates::Default) const{
	w.draw(s, states);
}

void Player::Update(){
	speed.y += 9.8f/60.f;
	
	Move();
}

void Player::Move(){
	prevPos = s.getPosition();
	s.move(speed);
}

void Player::MoveLeft(){
	speed.x = -2;
}

void Player::MoveRight(){
	speed.x = 2;
}

void Player::Jump(){
	if(landed){
		prevPos = s.getPosition();
		speed.y = -32;
	}
}

void Player::Collision(Floor floor){
	FloatRect boxPlayer = s.getGlobalBounds();
	FloatRect boxFloor = floor.GetRect();
	
	float PB = boxPlayer.top + boxPlayer.height;
	float PT = boxPlayer.top;
	float PR = boxPlayer.left + boxPlayer.width;
	float PL = boxPlayer.left;
	float FB = boxFloor.top + boxFloor.height;
	float FT = boxFloor.top;
	float FR = boxFloor.left + boxFloor.width;
	float FL = boxFloor.left;
	
	// Izquierda
	if(	PL + speed.x < FR &&
		PR + speed.x > FL &&
		PT <= FB &&
		PB >= FT
	  ){
		speed.x = 0;
	}
	// Derecha
	if(	PR + speed.x > FL &&
		PL + speed.x < FR &&
		PT <= FB &&
		PB >= FT
	  ){
		speed.x = 0;
	}
	// Abajo
	if( PB + speed.y > FT &&
		PT + speed.y < FB &&
		PL <= FR &&
		PR >= FL
	  ){
		s.setPosition(Vector2f(s.getPosition().x, prevPos.y));
		prevPos = s.getPosition();
		landed = true;
		speed.y = 0;
		speed.x *= 0.9f;
	}
	// Arriba
	if( PB + speed.y > FT &&
		PT + speed.y < FB &&
		PL <= FR &&
		PR >= FL
	  ){
		// Implementar golpear un techo
	}
	
}

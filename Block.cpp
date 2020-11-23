#include "Block.h"

Block::Block(float x, float y){
	t.loadFromFile("block.png");
	s.setTexture(t);
	s.setPosition(x, y);
}

void Block::draw(sf::RenderTarget& w, sf::RenderStates states = RenderStates::Default) const{
	w.draw(s, states);
}

void Block::Update() {
	//Movimiento
	speed.y = 1;
	
	//Colisiones (cancelan movimientos)
	ProcessCollisions();
	
	Move();
}

void Block::Move() {
	s.move(speed);
}

void Block::Collision(vector<vector<bool>>& gamestate){
	gameState = gamestate;
}

void Block::ProcessCollisions() {

	//Donde está el bloque en GameZone?
	FloatRect BoxBlock1 = s.getGlobalBounds();
	
	
//	if(colisionaAbajo){
//		landed = true;
//		speed.y = 0;
//	} else {
//		landed=false;
//	}
}

FloatRect Block::GetRect(){
	return s.getGlobalBounds();
}

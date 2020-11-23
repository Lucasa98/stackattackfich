#include "Block.h"

Block::Block(float x, float y){
	t.loadFromFile("block.png");
	s.setTexture(t);
	s.setPosition(x, y);
	prevx = (x-50)/50;
	prevy = (350 - y)/50;
}

Block::Block(const Block& b){
	t.loadFromFile("block.png");
	s.setTexture(t);
	s.setPosition(b.GetRect().left, b.GetRect().top);
	prevx = (s.getPosition().x-50)/50;
	prevy = (350 - s.getPosition().y)/50;
}

void Block::draw(sf::RenderTarget& w, sf::RenderStates states = RenderStates::Default) const{
	w.draw(s, states);
}

void Block::Update() {
	//Movimiento
	speed.y = 1.5f;
	
	//Colisiones (cancelan movimientos)
	ProcessCollisions();
	
	Move();
}

void Block::Move() {
	s.move(speed);
}

void Block::Collisions(vector<vector<bool>>* gamestate){
	gameState = gamestate;
}

void Block::ProcessCollisions() {

	//Donde está el bloque en GameZone?
	FloatRect Box = s.getGlobalBounds();
	int x = (Box.left-50)/50;
	int y = (350 - Box.top)/50;
	
	if(y == 0 || (*gameState)[x][y-1]){
		landed = true;
		speed.y = 0;
	} else {
		landed=false;
	}
	
	(*gameState)[x][y] = true;
	
	if(x != prevx && y != prevy){
		(*gameState)[prevx][prevy] = false;
	}else if(x != prevx){
		(*gameState)[prevx][y] = false;
	}else if(y != prevy){
		(*gameState)[x][prevy] = false;
	}
	prevx = x;
	prevy = y;
}

FloatRect Block::GetRect() const{
	return s.getGlobalBounds();
}

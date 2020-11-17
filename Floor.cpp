#include "Floor.h"

Floor::Floor(){
	t.loadFromFile("floor.png");
	s.setTexture(t);
	s.setPosition(0, 430);
}

void Floor::draw(sf::RenderTarget& w, sf::RenderStates states = RenderStates::Default) const{
	w.draw(s, states);
}

void Floor::SetPos(Vector2f pos){
	s.setPosition(pos);
}

FloatRect Floor::GetRect(){
	return s.getGlobalBounds();
}

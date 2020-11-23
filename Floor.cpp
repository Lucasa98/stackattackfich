#include "Floor.h"

Floor::Floor(float x, float y){
	t.loadFromFile("floor.png");
	s.setTexture(t);
	s.setPosition(x, y);
}

void Floor::draw(sf::RenderTarget& w, sf::RenderStates states = RenderStates::Default) const{
	w.draw(s, states);
}

void Floor::SetPos(Vector2f pos){
	s.setPosition(pos);
}

FloatRect Floor::GetRect() const{
	return s.getGlobalBounds();
}

#include "Wall.h"

Wall::Wall(float x, float y){
	t.loadFromFile("wall.png");
	s.setTexture(t);
	s.setPosition(x, y);
}

void Wall::draw(sf::RenderTarget& w, sf::RenderStates states = RenderStates::Default) const{
	w.draw(s, states);
}

void Wall::SetPos(Vector2f pos){
	s.setPosition(pos);
}

FloatRect Wall::GetRect() const{
	return s.getGlobalBounds();
}

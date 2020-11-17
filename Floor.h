#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Floor : public Drawable{
	Texture t;
	Sprite s;
public:
	Floor();
	virtual void draw(RenderTarget&, RenderStates) const;
	
	void SetPos(Vector2f);
	
	FloatRect GetRect();
};

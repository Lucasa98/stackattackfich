#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Scenario : public Drawable{
public:
	virtual void draw(RenderTarget&, RenderStates) const =0;
	virtual FloatRect GetRect() const =0;
};

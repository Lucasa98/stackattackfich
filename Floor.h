#pragma once

#include <SFML/Graphics.hpp>
#include "Scenario.h"

using namespace sf;

class Floor : public Scenario{
	Texture t;
	Sprite s;
public:
	Floor(float x, float y);
	virtual void draw(RenderTarget&, RenderStates) const;
	
	void SetPos(Vector2f);
	
	FloatRect GetRect() const override;
};

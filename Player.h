#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>
#include "Floor.h"

using namespace sf;

class Player : public Drawable{
	Texture t;
	Sprite s;
	Vector2f speed;
	bool landed;
public:
	Player();
	virtual void draw(RenderTarget&, RenderStates) const;
	
	void Update();
	void Move();
	
	void Collision(Floor);
};

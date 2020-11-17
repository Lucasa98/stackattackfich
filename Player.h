#pragma once

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Floor.h"

using namespace sf;

class Player : public Drawable{
	Texture t;
	Sprite s;
	Vector2f speed;
	bool landed;
	Vector2f prevPos;
public:
	Player();
	virtual void draw(RenderTarget&, RenderStates) const;
	
	void Update();
	void Move();
	
	void MoveLeft();
	void MoveRight();
	void Jump();
	
	void Collision(Floor);
};

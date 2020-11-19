#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Scenario.h"
#include "Floor.h"

using namespace std;
using namespace sf;

class Player : public Drawable{
	Texture t;
	Sprite s;
	Vector2f speed;
	Vector2f prevPos;
	vector<Scenario*> scenario;
	
	bool landed;
	bool leftFlag;
	bool rightFlag;
	bool leftWall;
	bool rightWall;
public:
	Player();
	virtual void draw(RenderTarget&, RenderStates) const;
	
	void Update();
	void ProcessCollision(Scenario*);
	void Move();
	
	void MoveLeft();
	void nMoveLeft();
	void MoveRight();
	void nMoveRight();
	void Jump();
	
	void Collisions(vector<Scenario*>&);
};

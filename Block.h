#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Scenario.h"

using namespace std;
using namespace sf;

class Block : public Scenario {
private:
	Texture t;
	Sprite s;
	
	Vector2f speed;
	
	vector<vector<bool>>* gameState;
	int prevx;
	int prevy;
	bool landed;
public:
	Block(float x, float y);
	Block(const Block&);
	virtual void draw(RenderTarget&, RenderStates) const;
	
	void Collisions(vector<vector<bool>>*);
	void ProcessCollisions();
	void Update();
	void Move();
	void Empujar();
	
	FloatRect GetRect() const override;
};

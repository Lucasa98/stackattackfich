#pragma once

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
	
	vector<vector<bool>> gameState;
	bool landed;
public:
	Block(float x, float y);
	virtual void draw(RenderTarget&, RenderStates) const;
	
	void Collision(vector<vector<bool>>&);
	void ProcessCollisions();
	void Update();
	void Move();
	void Empujar();
	
	FloatRect GetRect() override;
};

#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Scenario.h"

using namespace std;
using namespace sf;

class Block : public Scenario {
private:
	Texture t;
	Sprite s;
	
	Vector2f speed;
	
	vector<vector<bool>>* gameState;	//Posiciones ocupadas
	int prevx;
	int prevy;
	int movementc;	//Acumulador al ser empujado, [0, 20] suma 1 en cada frame (2.5*20=50)
	bool moving;	//T si fue empujado, F si no
	bool landed;	//T con contacto debajo, False caso contrario
public:
	enum direction{
		left, right
	};
	
	Block(float x, float y);
	Block(const Block&);
	virtual void draw(RenderTarget&, RenderStates) const;
	
	void Collisions(vector<vector<bool>>*);
	void ProcessCollisions();
	void Update();
	void Move();
	void erase();
	void Empujar(direction);
	
	pair<int, int> GetXY();
	FloatRect GetRect() const override;
	
	~Block();
};

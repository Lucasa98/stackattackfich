#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Scenario.h"
#include "Floor.h"
#include "Block.h"

using namespace std;
using namespace sf;

class Player : public Drawable{
	Clock clock;
	bool golpeado;
	int increment;
	
	Texture t;
	Sprite s;
	Vector2f speed;
	vector<Scenario*> scenario;
	vector<Block*> blocks;
	int lifes;
	
	bool vivo;
	bool landed;
	bool leftFlag;
	bool rightFlag;
	bool leftWall;
	bool rightWall;
	bool empujando;
public:
	Player(int);
	virtual void draw(RenderTarget&, RenderStates) const;
	int count_lifes();
	
	void Update();
	void ProcessBlock(Block*);
	void ProcessCollision(Scenario*);
	void Move();
	void Revive();
	bool Vive();
	void SumarVida(int x);
	
	void ChangeTexture(int x);
	void MoveLeft();
	void nMoveLeft();
	void MoveRight();
	void nMoveRight();
	void Jump();
	void Empujar();
	void nEmpujar();
	
	//Carga el escenario
	void Collisions(vector<Scenario*>&);
	void BlockCollisions(vector<Block*>&);
	
	FloatRect GetRect();
};

#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Scenario.h"
#include "Wall.h"
#include "Floor.h"
#include "Block.h"

using namespace sf;

class Game {
	RenderWindow w;
	Clock clock;
	
	///Cuadricula
	vector<VertexArray> cuadriculax;
	vector<VertexArray> cuadriculay;
	
//	vector<Block> Game_Zone;
	vector<vector<bool>> Pos_Matrix;
	Player player;
	vector<Scenario*> scenario;
public:
	Game();
	void Play();
	void ProcessEvents();
	void Update();
	void Draw();
};

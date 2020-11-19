#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Scenario.h"
#include "Wall.h"
#include "Floor.h"

using namespace sf;

class Game {
	RenderWindow w;
	Clock clock;
	
	Player player;
	vector<Scenario*> scenario;
public:
	Game();
	void Play();
	void ProcessEvents();
	void Update();
	void Draw();
};

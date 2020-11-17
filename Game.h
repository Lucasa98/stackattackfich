#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Floor.h"

using namespace sf;

class Game {
	RenderWindow w;
	Player player;
	Floor floor;
	Floor wall;
	Floor wall2;
public:
	Game();
	void Play();
	void ProcessEvents();
	void Update();
	void Draw();
};

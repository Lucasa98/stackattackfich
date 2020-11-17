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
public:
	Game();
	void Play();
	void ProcessEvents();
	void Update();
	void Draw();
};

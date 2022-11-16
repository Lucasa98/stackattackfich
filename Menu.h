#pragma once

#include "Game.h"
#include "Scene.h"

using namespace sf;

class Menu : public Scene{
	Texture Fondo_t;
	Sprite Fondo;
	
	bool score;
	bool enter;
public:
	Menu();
	
	void Update(Game&);
	void Draw(RenderWindow&);
	void ProcessEvents(RenderWindow&);
};

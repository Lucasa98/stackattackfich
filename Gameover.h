#pragma once

#include "Game.h"
#include "Scene.h"


using namespace sf;

class Gameover : public Scene{
private:
	Texture Fondo_t;
	Sprite Fondo;
	
	Clock clock;
	
	bool ready;
	int increment;
	bool rankea;
	int point;
	
	Text P_a;
	Text P_b;
	Text P_c;
	
	char a,b,c;
	Font m_font;
	Text m_titulo;
public:
	Gameover(int,bool);
	
	void Update(Game&);
	void Draw(RenderWindow&);
	void ProcessEvents(RenderWindow&);
};

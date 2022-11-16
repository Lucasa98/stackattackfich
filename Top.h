#pragma once

#include "Game.h"
#include "Scene.h"

#include <vector>
#include "Scores.h"
using namespace std;
using namespace sf;

class Top : public Scene{
	Texture Fondo_t;
	Sprite Fondo;
	Font font;
	vector<Text> P;
	
	Font m_font;
	Text m_titulo;
	int increment;
	
	vector<Score> puntajes;
	bool Menu;
public:
	Top(vector<Score>);
	
	void Textos();
	
	void Update(Game&);
	void Draw(RenderWindow&);
	void ProcessEvents(RenderWindow&);
};

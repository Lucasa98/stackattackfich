#pragma once

#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Menu.h"
#include "Top.h"
#include "Match.h"
#include "Scores.h"
#include "Gameover.h"

using namespace sf;

class Game {	
	RenderWindow w;
	Clock clock;
	
	Scene* m_scene;
	Scene* m_next_scene;
	
	
	Scores HighScores;
public:
	enum Escena{ s_menu, s_match, s_gameover, s_top };
	
	Game();
	
	void Play();
	
	void ChangeScene(Escena);
	void Restart(int);
	void Death(int);
	void NewScore(Score);
	vector<Score> view_scores();
	
	void Update();
	void ProcessEvents();
	void Draw();
	
	~Game();
};

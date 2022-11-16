#pragma once

#include <vector>
#include "Scene.h"
#include "Player.h"
#include "Scenario.h"
#include "Wall.h"
#include "Block.h"
#include "Game.h"
#include <SFML/Audio/Music.hpp>


using namespace sf;

class Match : public Scene{
private:
	float time_per_block;
	
	Clock timer;
	Texture Player_Life;
	Font font;
	Text point;
	Text lifes;
	Text cant_points;
	Text cant_lifes;
	
	Music Soundtrack;
	bool mute;
	
	Texture Heart_t;
	Sprite Heart;
	Music more_life;
	
	int cont_op;
	bool gain_life;
	bool aumentando;
	int points;
	int points_for_lifes;
	bool pause;
	
	///Cuadricula
	vector<VertexArray> cuadriculax;
	vector<VertexArray> cuadriculay;
	
	vector<Block*> Game_Zone;
	vector<vector<bool>> Pos_Matrix; //(0,0)=SW
	Player player;
	
	///Scenario
	vector<Scenario*> scenario;
	Texture Background_t;
	Sprite Background;
	Texture Scoreboard_t;
	Sprite Scoreboard;
	
public:
	Match(int);
	
	void Textos();
	void Limpiar_Mapa();
	void Restart(Game&);
	void CheckRow();
	
	void Update(Game&);
	void Draw(RenderWindow&);
	void ProcessEvents(RenderWindow&);
	
	//Helpers
	vector<Block*>::iterator XYtoIndex(size_t, size_t);
	
	~Match();
};

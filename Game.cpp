#include "Game.h"

Game::Game(): w(VideoMode(500, 400), "Stack Attack"),
	scenario(3),
	Pos_Matrix(8),
	cuadriculax(8),
	cuadriculay(6){
	
	///Cuadricula
	for(size_t i = 0; i < cuadriculax.size(); ++i){
		cuadriculax[i].setPrimitiveType(LineStrip);
		cuadriculax[i].resize(2);
		cuadriculax[i][0].position = Vector2f(50+(50*i), 350);
		cuadriculax[i][1].position = Vector2f(50+(50*i), 0);
	}
	for(size_t i = 0; i < cuadriculay.size(); ++i){
		cuadriculay[i].setPrimitiveType(LineStrip);
		cuadriculay[i].resize(2);
		cuadriculay[i][0].position = Vector2f(50, 100+(50*i));
		cuadriculay[i][1].position = Vector2f(450, 100+(50*i));
	}
	///----------
	
	scenario[0] = new Floor(0, 350);
	scenario[1] = new Wall(0, 0);
	scenario[2] = new Wall(450, 0);
	
	for(size_t i=0; i < Pos_Matrix.size(); i++) {
		Pos_Matrix[i].resize(5);
		for(size_t j = 0; j < Pos_Matrix.size(); ++j){
			Pos_Matrix[i][j] = false;
		}
	}
	
	Block b(200,50);
	Game_Zone.push_back(b);
}

void Game::Play(){
	while(w.isOpen()) {
		ProcessEvents();
		if(clock.getElapsedTime().asMilliseconds() >= 1000/60.f){
			Update();
			Draw();
			clock.restart();
		}
	}
}

void Game::ProcessEvents(){
	Event e;
	while(w.pollEvent(e)) {
		if(e.type == Event::Closed)
			w.close();
		if(e.type == Event::KeyPressed){
			if(e.key.code == Keyboard::Escape)
				w.close();
			if(e.key.code == Keyboard::Up)
				player.Jump();
			if(e.key.code == Keyboard::Left)
				player.MoveLeft();
			if(e.key.code == Keyboard::Right)
				player.MoveRight();
			if(e.key.code == Keyboard::Down)
				player.Empujar();
			if(e.key.code == Keyboard::Space){
				Block b(200, 50);
				Game_Zone.push_back(b);
			}
		}
		if(e.type == Event::KeyReleased){
			if(e.key.code == Keyboard::Up)
				player.Jump();
			if(e.key.code == Keyboard::Left)
				player.nMoveLeft();
			if(e.key.code == Keyboard::Right)
				player.nMoveRight();
			if(e.key.code == Keyboard::Down)
				player.nEmpujar();
		}
	}
}

void Game::Update(){
	player.Collisions(scenario);
	player.Update();
	for(size_t i = 0; i < Game_Zone.size(); ++i){
		Game_Zone[i].Collisions(&Pos_Matrix);
	}
	for(size_t i = 0; i < Game_Zone.size(); ++i){
		Game_Zone[i].Update();
	}
}

void Game::Draw(){
	w.clear();
	
	w.draw(player);
	
	for(size_t i = 0; i < Game_Zone.size(); ++i){
		w.draw(Game_Zone[i]);
	}
	
	for(size_t i = 0; i < scenario.size(); ++i){
		w.draw(*(scenario[i]));
	}
	
	for(size_t i = 0; i < cuadriculax.size(); ++i)
		w.draw(cuadriculax[i]);
	for(size_t i = 0; i < cuadriculay.size(); ++i)
		w.draw(cuadriculay[i]);
	
	w.display();
}

Game::~Game(){
	for(size_t i = 0; i < scenario.size(); ++i){
		delete scenario[i];
	}
}

#include "Game.h"

Game::Game(): w(VideoMode(640, 480), "Stack Attack"){
	w.setFramerateLimit(60);
	
	wall.SetPos(Vector2f(500, 380));
}

void Game::Play(){
	while(w.isOpen()) {
		ProcessEvents();
		Update();
		Draw();
	}
}

void Game::ProcessEvents(){
	Event e;
	while(w.pollEvent(e)) {
		if(e.type == Event::Closed)
			w.close();
	}
}

void Game::Update(){
	player.Update();
	player.Collision(floor);
	player.Collision(wall);
	player.Move();
}

void Game::Draw(){
	w.clear();
	w.draw(player);
	w.draw(floor);
	w.draw(wall);
	w.display();
}

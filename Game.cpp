#include "Game.h"

Game::Game(): w(VideoMode(640, 480), "Stack Attack"){
	w.setFramerateLimit(60);
	
	wall.SetPos(Vector2f(500, 380));
	wall2.SetPos(Vector2f(-400, 380));
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
		if(e.type == Event::KeyPressed){
			if(e.key.code == Keyboard::Left)
				player.MoveLeft();
			if(e.key.code == Keyboard::Right)
				player.MoveRight();
		}
		if(e.type == Event::KeyReleased){
			if(e.key.code == Keyboard::Up)
				player.Jump();
		}
	}
}

void Game::Update(){
	player.Collision(floor);
	player.Collision(wall);
	player.Collision(wall2);
	player.Update();
}

void Game::Draw(){
	w.clear();
	w.draw(player);
	w.draw(floor);
	w.draw(wall);
	w.draw(wall2);
	w.display();
}

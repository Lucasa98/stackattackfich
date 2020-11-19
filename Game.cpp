#include "Game.h"

Game::Game(): w(VideoMode(640, 480), "Stack Attack"), scenario(3){
	
	scenario[0] = new Floor(0, 430);
	scenario[1] = new Wall(500, 380);
	scenario[2] = new Wall(-400, 380);
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
			if(e.key.code == Keyboard::Left)
				player.MoveLeft();
			if(e.key.code == Keyboard::Right)
				player.MoveRight();
		}
		if(e.type == Event::KeyReleased){
			if(e.key.code == Keyboard::Up)
				player.Jump();
			if(e.key.code == Keyboard::Left)
				player.nMoveLeft();
			if(e.key.code == Keyboard::Right)
				player.nMoveRight();
		}
	}
}

void Game::Update(){
	player.Collisions(scenario);
	player.Update();
}

void Game::Draw(){
	w.clear();
	w.draw(player);
	
	for(size_t i = 0; i < scenario.size(); ++i){
		w.draw(*(scenario[i]));
	}
	
	w.display();
}

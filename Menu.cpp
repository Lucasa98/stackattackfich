#include "Menu.h"

Menu::Menu(){
	enter = false;
	score = false;
	
	Fondo_t.loadFromFile("Menu.png");
	Fondo.setTexture(Fondo_t);
	Fondo.setPosition(0,0);
}

void Menu::Update(Game& game){
	if(enter){
		game.ChangeScene(Game::s_match);
	}else if(score){
		game.ChangeScene(Game::s_top);
	}
}

void Menu::Draw(RenderWindow& w){
	w.clear();
	w.draw(Fondo);
	w.display();
}

void Menu::ProcessEvents(RenderWindow& w){
	Event e;
	while(w.pollEvent(e)) {
		if(e.type == Event::Closed)
			w.close();
		if(e.type == Event::KeyPressed){
			if(e.key.code == Keyboard::Escape)
				w.close();
			if(e.key.code == Keyboard::Return)
				enter = true;
			if(e.key.code == Keyboard::Space)
				enter = true;
			if(e.key.code == Keyboard::H)
				score = true;
		}
	}
}

#include "Game.h"
using namespace std;

Game::Game(): w(VideoMode(500, 400), "Stack Attack") {

	m_scene = new Menu;
	m_next_scene = NULL;
}

void Game::Play(){
	while(w.isOpen()) {
		m_scene->ProcessEvents(w);
		if(clock.getElapsedTime().asMilliseconds() >= 1000/60.f){
			m_scene->Update(*this);
			m_scene->Draw(w);
			
			clock.restart();
		}
		
		if(m_next_scene){
			delete m_scene;
			m_scene = m_next_scene;
			m_next_scene = NULL;
		}
	}
}

void Game::Restart(int playerLives){
	m_next_scene = new Match(playerLives);
};

void Game::NewScore(Score aux) {
	HighScores.Insert_Score(aux);
}

vector<Score> Game::view_scores() {
	return HighScores.return_scores();
}

void Game::Death(int points){
	if(m_next_scene){
		delete m_next_scene;
		m_next_scene = nullptr;
	}
	bool aux = HighScores.is_top(points);
	m_next_scene = new Gameover(points,aux);
}

void Game::ChangeScene(Escena escena){
	if(escena == Game::s_menu)
		m_next_scene = new Menu();
	else if(escena == Game::s_match)
		m_next_scene = new Match(3);
	else if(escena == Game::s_top)
		m_next_scene = new Top(HighScores.return_scores());
}

Game::~Game(){
	HighScores.SaveHighscore();
	delete m_scene;
	delete m_next_scene;
}

#include "Top.h"
#include <sstream>
using namespace std;

Top::Top(vector<Score> V){
	Menu = false;
	puntajes = V;
	
	increment = -5;
	m_font.loadFromFile("bahnschrift.ttf");
	m_titulo.setFont(m_font);
	m_titulo.setString("HIGHSCORES");
	m_titulo.setPosition(Vector2f((500-(m_titulo.getLocalBounds().width))/2.f, 30.f));
	m_titulo.setOutlineThickness(1.f);
	m_titulo.setFillColor(Color(255, 0, 0));
	
	Textos();
	Fondo_t.loadFromFile("Top.png");
	Fondo.setTexture(Fondo_t);
	Fondo.setPosition(0,0);
}

void Top::Textos(){
	font.loadFromFile("bahnschrift.ttf");
	
	for(int i=0;i<10;i++) { 
		string s;
		s += to_string(i+1);
		s.push_back('.');
		s.push_back(' ');
		for(int j=0;j<3;j++) { 
			s.push_back(puntajes[i].alias[j]);
		}
		s.push_back(' ');
		s += to_string(puntajes[i].points);
		cout << s;
		Text aux;
		aux.setString(s);
		aux.setFont(font);
		aux.setFillColor(Color::Black);
		aux.setOutlineColor(Color::White);
		aux.setOutlineThickness(2);
		if (i<5) {
			aux.setPosition(50,100+(50*i));
		} else {
			aux.setPosition(275,100+(50*(i-5)));
		}
		P.push_back(aux);
	}
}

void Top::Update(Game& game){
	Color color = m_titulo.getFillColor();
	if(color.b >= 255 || color.b <= 0) increment *= -1;
	m_titulo.setFillColor(Color(color.r, 0, color.b+increment));
	m_titulo.setOutlineColor(Color(color.b, color.r, 0));
	
	if(Menu) {
		game.ChangeScene(Game::s_menu);
	}
}

void Top::Draw(RenderWindow& w){
	w.clear();
	w.draw(Fondo);
	w.draw(m_titulo);
	for(int i=0;i<10;i++) { 
		w.draw(P[i]);
	}
	w.display();
}

void Top::ProcessEvents(RenderWindow& w){
	Event e;
	while(w.pollEvent(e)) {
		if(e.type == Event::Closed)
			w.close();
		if(e.type == Event::KeyPressed){
			if(e.key.code == Keyboard::Return)
				Menu = true;
			if(e.key.code == Keyboard::Escape)
				Menu = true;
		}
	}
}

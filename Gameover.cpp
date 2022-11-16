#include "Gameover.h"

Gameover::Gameover(int points,bool is_top){
	
	Fondo_t.loadFromFile("Gameover.png");
	Fondo.setTexture(Fondo_t);
	Fondo.setPosition(0,0);
	
	a=b=c='-';
	point = points;
	rankea = is_top;
	ready = false;
	increment = -5;
	
	P_a.setString(a);
	P_b.setString(b);
	P_c.setString(c);
	
	m_font.loadFromFile("bahnschrift.ttf");
	m_titulo.setFont(m_font);
	m_titulo.setString("Game Over");
	m_titulo.setPosition(Vector2f((500-(m_titulo.getLocalBounds().width))/2.f, 30.f));
	m_titulo.setOutlineThickness(1.f);
	m_titulo.setFillColor(Color(255, 0, 0));
	
	P_a.setString(a);
	P_a.setFont(m_font);
	P_a.setFillColor(Color::Black);
	P_a.setOutlineColor(Color::White);
	P_a.setOutlineThickness(2);
	P_a.setPosition(223,250);
	
	P_b.setString(b);
	P_b.setFont(m_font);
	P_b.setFillColor(Color::Black);
	P_b.setOutlineColor(Color::White);
	P_b.setOutlineThickness(2);
	P_b.setPosition(243,250);
	
	P_c.setString(c);
	P_c.setFont(m_font);
	P_c.setFillColor(Color::Black);
	P_c.setOutlineColor(Color::White);
	P_c.setOutlineThickness(2);
	P_c.setPosition(263,250);
	
}

void Gameover::Update(Game& game){
	Color color = m_titulo.getFillColor();
	if(color.b >= 255 || color.b <= 0) increment *= -1;
	m_titulo.setFillColor(Color(color.r, color.g, color.b+increment));
	m_titulo.setOutlineColor(Color(color.b, color.r, 0));
	
	if (rankea) {
		P_a.setString(a);
		P_b.setString(b);
		P_c.setString(c);
	}
	
	if(ready){
		Score aux;
		aux.alias[0] = a;
		aux.alias[1] = b;
		aux.alias[2] = c;
		aux.points = point;
		game.NewScore(aux);
		game.ChangeScene(Game::s_top);
	}
}

void Gameover::Draw(RenderWindow& w){
	w.clear(Color::Black);
	
	w.draw(Fondo);
	w.draw(m_titulo);
	
	int seconds = (clock.getElapsedTime().asSeconds())*3;
	
	if (rankea && seconds%3 == 1) {
		w.draw(P_a);
		w.draw(P_b);
		w.draw(P_c);
	}
	if(seconds%3 == 2) clock.restart();
	
	w.display();
}

void Gameover::ProcessEvents(RenderWindow& w){
	Event e;
	while(w.pollEvent(e)) {
		if(e.type == Event::Closed)
			w.close();
		if(e.type == Event::KeyPressed){
			if(e.key.code == Keyboard::Escape)
				w.close();
			if(e.key.code == Keyboard::Space)
				ready = true;
			if(e.key.code == Keyboard::Return)
				ready = true;
		}
		if (rankea) {
			if(e.type == Event::KeyReleased){
				if(e.key.code == Keyboard::A){
					if(a=='-'){a='A';}
					else if(b=='-'){b='A';}
					else if(c=='-'){c='A';}
				}
				else if(e.key.code == Keyboard::B){
					
					if(a=='-'){a='B';}
					else if(b=='-'){b='B';}
					else if(c=='-'){c='B';}
				}
				else if(e.key.code == Keyboard::C){
					
					if(a=='-'){a='C';}
					else if(b=='-'){b='C';}
					else if(c=='-'){c='C';}
				}
				else if(e.key.code == Keyboard::D){
					
					if(a=='-'){a='D';}
					else if(b=='-'){b='D';}
					else if(c=='-'){c='D';}
				}
				else if(e.key.code == Keyboard::E){
					
					if(a=='-'){a='E';}
					else if(b=='-'){b='E';}
					else if(c=='-'){c='E';}
				}
				else if(e.key.code == Keyboard::F){
					
					if(a=='-'){a='F';}
					else if(b=='-'){b='F';}
					else if(c=='-'){c='F';}
				}
				else if(e.key.code == Keyboard::G){
					
					if(a=='-'){a='G';}
					else if(b=='-'){b='G';}
					else if(c=='-'){c='G';}
				}
				else if(e.key.code == Keyboard::H){
					
					if(a=='-'){a='H';}
					else if(b=='-'){b='H';}
					else if(c=='-'){c='H';}
				}
				else if(e.key.code == Keyboard::I){
					
					if(a=='-'){a='I';}
					else if(b=='-'){b='I';}
					else if(c=='-'){c='I';}
				}
				else if(e.key.code == Keyboard::J){
					
					if(a=='-'){a='J';}
					else if(b=='-'){b='J';}
					else if(c=='-'){c='J';}
				}
				else if(e.key.code == Keyboard::K){
					
					if(a=='-'){a='K';}
					else if(b=='-'){b='K';}
					else if(c=='-'){c='K';}
				}
				else if(e.key.code == Keyboard::L){
					
					if(a=='-'){a='L';}
					else if(b=='-'){b='L';}
					else if(c=='-'){c='L';}
				}
				else if(e.key.code == Keyboard::M){
					
					if(a=='-'){a='M';}
					else if(b=='-'){b='M';}
					else if(c=='-'){c='M';}
				}
				else if(e.key.code == Keyboard::N){
					
					if(a=='-'){a='N';}
					else if(b=='-'){b='N';}
					else if(c=='-'){c='N';}
				}
				else if(e.key.code == Keyboard::O){
					
					if(a=='-'){a='O';}
					else if(b=='-'){b='O';}
					else if(c=='-'){c='O';}
				}
				else if(e.key.code == Keyboard::P){
					
					if(a=='-'){a='P';}
					else if(b=='-'){b='P';}
					else if(c=='-'){c='P';}
				}
				else if(e.key.code == Keyboard::Q){
					
					if(a=='-'){a='Q';}
					else if(b=='-'){b='Q';}
					else if(c=='-'){c='Q';}
				}
				else if(e.key.code == Keyboard::R){
					
					if(a=='-'){a='R';}
					else if(b=='-'){b='R';}
					else if(c=='-'){c='R';}
				}
				else if(e.key.code == Keyboard::S){
					
					if(a=='-'){a='S';}
					else if(b=='-'){b='S';}
					else if(c=='-'){c='S';}
				}
				else if(e.key.code == Keyboard::T){
					
					if(a=='-'){a='T';}
					else if(b=='-'){b='T';}
					else if(c=='-'){c='T';}
				}
				else if(e.key.code == Keyboard::U){
					
					if(a=='-'){a='U';}
					else if(b=='-'){b='U';}
					else if(c=='-'){c='U';}
				}
				else if(e.key.code == Keyboard::V){
					
					if(a=='-'){a='V';}
					else if(b=='-'){b='V';}
					else if(c=='-'){c='V';}
				}
				else if(e.key.code == Keyboard::W){
					
					if(a=='-'){a='W';}
					else if(b=='-'){b='W';}
					else if(c=='-'){c='W';}
				}
				else if(e.key.code == Keyboard::X){
					
					if(a=='-'){a='X';}
					else if(b=='-'){b='X';}
					else if(c=='-'){c='X';}
				}
				else if(e.key.code == Keyboard::Y){
					
					if(a=='-'){a='Y';}
					else if(b=='-'){b='Y';}
					else if(c=='-'){c='Y';}
				}
				else if(e.key.code == Keyboard::Z){
					
					if(a=='-'){a='Z';}
					else if(b=='-'){b='Z';}
					else if(c=='-'){c='Z';}
				}
			}
		}
		
	}
}

#include "Match.h"

Match::Match(int lifes) : scenario(3),
	Pos_Matrix(8),
	cuadriculax(8),
	cuadriculay(6),
	player(lifes){
	time_per_block = 4;
	
	points = 0;
	points_for_lifes = 0;
	pause = false;
	Textos();
	
	gain_life = false;
	aumentando = true;
	cont_op=0;
	more_life.openFromFile("gain_life.ogg");
	more_life.setVolume(35);
	
	Heart_t.loadFromFile("heart.png");
	Heart.setTexture(Heart_t);
	Heart.setPosition(375,25);
	
	
	Soundtrack.openFromFile("match.ogg");
	Soundtrack.play();
	Soundtrack.setVolume(20);
	mute = false;
	
	///Cuadricula (DEBUG)---------------
//	for(size_t i = 0; i < cuadriculax.size(); ++i){
//		cuadriculax[i].setPrimitiveType(LineStrip);
//		cuadriculax[i].resize(2);
//		cuadriculax[i][0].position = Vector2f(50+(50*i), 350);
//		cuadriculax[i][1].position = Vector2f(50+(50*i), 0);
//	}
//	for(size_t i = 0; i < cuadriculay.size(); ++i){
//		cuadriculay[i].setPrimitiveType(LineStrip);
//		cuadriculay[i].resize(2);
//		cuadriculay[i][0].position = Vector2f(50, 100+(50*i));
//		cuadriculay[i][1].position = Vector2f(450, 100+(50*i));
//	}
	///---------------------------------
	
	scenario[0] = new Wall(0, 0);
	scenario[1] = new Wall(450, 0);
	scenario[2] = new Floor(0, 350);
	
	Background_t.loadFromFile("Background.png");
	Background.setTexture(Background_t);
	Background.setPosition(Vector2f(0,0));
	
	for(size_t i=0; i < Pos_Matrix.size(); i++) {
		Pos_Matrix[i].resize(5);
		for(size_t j = 0; j < Pos_Matrix.size(); ++j){
			Pos_Matrix[i][j] = false;
		}
	}
	
	Scoreboard_t.loadFromFile("scoreboard.png");
	Scoreboard.setTexture(Scoreboard_t);
	Scoreboard.setPosition(0,0);
}

void Match::Update(Game& game){
	///genera un nuevo bloque en una posicion random cada 4 seg
	///entre las posiciones validas de la matriz a una altura determinada
	
	if(timer.getElapsedTime().asSeconds() >= time_per_block){
		int pos = rand()%400;
		pos = ((pos/50)+1)*50;
		Block* x = new Block(pos,5);
		Game_Zone.push_back(x);
		timer.restart();
		points += 10;
		points_for_lifes += 10;
		if (points_for_lifes-1000 >= 0) {
			gain_life = true;
			more_life.play();
			points_for_lifes = points_for_lifes-1000;
			player.SumarVida(1);
		}
	}
	
	if (!player.Vive()) {
		Restart(game);
	}
	
	this->CheckRow();
	
	player.Collisions(scenario);
	player.BlockCollisions(Game_Zone);
	player.Update();
	
	for(size_t i = 0; i < Game_Zone.size(); ++i){
		Game_Zone[i]->Collisions(&Pos_Matrix);
	}
	for(size_t i = 0; i < Game_Zone.size(); ++i){
		Game_Zone[i]->Update();
	}
	
	///vidas del jugador
	cant_lifes.setString(to_string(player.count_lifes()));
	
	///contador de puntos
	cant_points.setString(to_string(points));
	
	///pausa
	if(pause){
		Soundtrack.stop();
		game.ChangeScene(Game::s_menu);
	}
}

void Match::ProcessEvents(RenderWindow& w){
	Event e;
	while(w.pollEvent(e)) {
		if(e.type == Event::Closed){
			Soundtrack.stop();
			w.close();
		}
		if(e.type == Event::KeyPressed){
			if(e.key.code == Keyboard::Escape){
				Soundtrack.stop();
				pause = true;
			}
			if(e.key.code == Keyboard::Up)
				player.Jump();
			if(e.key.code == Keyboard::Left)
				player.MoveLeft();
			if(e.key.code == Keyboard::Right)
				player.MoveRight();
			if(e.key.code == Keyboard::Down)
				player.Empujar();
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
			if(e.key.code == Keyboard::M){
				mute = !mute;
				if(mute)
					Soundtrack.setVolume(0);
				else
					Soundtrack.setVolume(20);
			}
		}
	}
}

void Match::Draw(RenderWindow& w){
	w.clear();
	
	w.draw(Background);
	
	w.draw(player);
	
	for(size_t i = 0; i < Game_Zone.size(); ++i){
		w.draw(*(Game_Zone[i]));
	}
	
	for(size_t i = 0; i < scenario.size(); ++i){
		w.draw(*(scenario[i]));
	}
	
	///Cuadricula (Debug)--------------
	//	for(size_t i = 0; i < cuadriculax.size(); ++i)
	//		w.draw(cuadriculax[i]);
	//	for(size_t i = 0; i < cuadriculay.size(); ++i)
	//		w.draw(cuadriculay[i]);
	///--------------------------------
	
	w.draw(Scoreboard);
	w.draw(point);
	w.draw(lifes);
	w.draw(cant_lifes);
	w.draw(cant_points);
	
	///animacion ganar vida
	if (gain_life) {
		if (aumentando) {
			cont_op+=8;
			Heart.setColor(Color(255,255,255,cont_op));
			w.draw(Heart);
			if (cont_op>=255) {
				aumentando = false;
			}
		} else {
			cont_op-=8;
			Heart.setColor(Color(255,255,255,cont_op));
			w.draw(Heart);
			if (cont_op<=0) {
				gain_life=false;
				aumentando = true;
			}
		}
	}
	
	///Position matrix (Debug)------------
//	for(size_t x = 0; x < Pos_Matrix.size(); ++x){
//		for(size_t y = 0; y < Pos_Matrix[x].size(); ++y){
//			if(Pos_Matrix[x][y]){
//				VertexArray line;
//				
//				line.setPrimitiveType(LineStrip);
//				line.resize(2);
//				line[0].position = Vector2f(50+(x*50), 350-(y*50));
//				line[1].position = Vector2f(100+(x*50), 300-(y*50));
//				w.draw(line);
//			}
//		}
//	}
	///-----------------------------------
	
	w.display();
}

void Match::CheckRow(){
	bool full = true;
	for(size_t x=0; x < Pos_Matrix.size(); ++x){
		if(!Pos_Matrix[x][0]){
			full = false;
			break;
		}
	}
	if(full){
		points += 100;
		points_for_lifes += 100;
		if (points_for_lifes-1000 >= 0) {
			gain_life = true;
			more_life.play();
			points_for_lifes = points_for_lifes-1000;
			player.SumarVida(1);
		}
		for(size_t x=0; x < Pos_Matrix.size(); ++x){
			vector<Block*>::iterator it = XYtoIndex(x, 0);
			delete *it;
			Game_Zone.erase(it);
		}
		if(time_per_block > 1)
			time_per_block -= 0.5;
	}
}

void Match::Textos() {
	font.loadFromFile("bahnschrift.ttf");
	
	///points
	point.setString("Points:");
	point.setFont(font);
	point.setFillColor(Color::Black);
	point.setOutlineColor(Color::White);
	point.setOutlineThickness(2);
	point.setPosition(100,5);
	
	
	///player lifes
	lifes.setString("Lifes:");
	
	lifes.setFont(font);
	lifes.setFillColor(Color::Black);
	
	lifes.setOutlineColor(Color::White);
	lifes.setOutlineThickness(2);
	
	lifes.setPosition(385,5);
	
	
	///cant_lifes
	cant_lifes.setFont(font);
	cant_lifes.setFillColor(Color::Black);
	
	cant_lifes.setOutlineColor(Color::White);
	cant_lifes.setOutlineThickness(2);
	
	cant_lifes.setPosition(462,5);
	
	
	///cant_points
	cant_points.setFont(font);
	cant_points.setFillColor(Color::Black);
	
	cant_points.setOutlineColor(Color::White);
	cant_points.setOutlineThickness(2);
	
	cant_points.setPosition(195,5);

}

void Match::Limpiar_Mapa() {
	for(size_t y=0; y < Pos_Matrix[0].size(); ++y){
		for(size_t x=0; x < Pos_Matrix.size(); ++x){
			if(!Pos_Matrix[x][y]){
			} else {
				vector<Block*>::iterator it = XYtoIndex(x, y);
				delete *it;
				Game_Zone.erase(it);
			}
		}
	}
}

void Match::Restart(Game& game) {
	if (player.count_lifes() > 0) {
		Limpiar_Mapa();
		player.Revive();
		
	} else {
		Soundtrack.stop();
		game.Death(points);
	}
}

vector<Block*>::iterator Match::XYtoIndex(size_t x, size_t y){
	for(vector<Block*>::iterator it=Game_Zone.begin(); it != Game_Zone.end(); ++it){
		pair<int, int> xy = (*it)->GetXY();
		if(xy.first == x && xy.second == y) return it;
	}
	return Game_Zone.begin();
}
Match::~Match(){
	for(size_t i = 0; i < scenario.size(); ++i){
		delete scenario[i];
	}
	for(size_t i = 0; i < Game_Zone.size(); ++i){
		delete Game_Zone[i];
	}
}

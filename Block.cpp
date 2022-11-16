#include "Block.h"
using namespace std;

Block::Block(float x, float y){
	if(rand()%2 == 0)
		t.loadFromFile("block1.png");
	else
		t.loadFromFile("block2.png");
	s.setTexture(t);
	s.setPosition(x, y);
	prevx = (x-50)/50;
	prevy = (350 - y)/50;
	moving = false;
}

Block::Block(const Block& b){
	t.loadFromFile("block.png");
	s.setTexture(t);
	s.setPosition(b.GetRect().left, b.GetRect().top);
	prevx = (s.getPosition().x-50)/50;
	prevy = (350 - s.getPosition().y)/50;
}

void Block::draw(sf::RenderTarget& w, sf::RenderStates states = RenderStates::Default) const{
	w.draw(s, states);
	
	///TopBound (Debug)------------
//	FloatRect rect = GetRect();
//	VertexArray top_bound;
//	top_bound.setPrimitiveType(LineStrip);
//	top_bound.resize(2);
//	top_bound[0].position = Vector2f(rect.left, rect.top);
//	top_bound[1].position = Vector2f(rect.left+rect.width, rect.top);
//	
//	w.draw(top_bound);
	///----------------------------
}

void Block::Update() {
	//Movimiento
	if(!landed)
		speed.y = 1.5f;
	
	//Colisiones (cancelan movimientos)
	// No procesa colisiones durante el movimiento al ser empujado
	if(!moving){
		ProcessCollisions();
		movementc = 0;
	}
	else{
		if(speed.x > 0)		//Al ser empujado, pasa a ocupar el siguiente lugar en gameState
			(*gameState)[prevx+1][prevy] = true;
		else if(speed.x < 0)
			(*gameState)[prevx-1][prevy] = true;
		
		if(movementc == 20){
			speed.x = 0;
			moving = false;
		}else
		   ++movementc;
	}
	
	Move();
}

void Block::Move() {
	s.move(speed);
}

void Block::Empujar(direction d){
	// d: hacia dónde se lo quiere empujar
	
	// Posición en GameZone
	FloatRect Box = s.getGlobalBounds();
	int x = (Box.left-50)/50.f;
	int y = (350 - Box.top)/50;
	
	if(d == Block::left && x > 0 && !(*gameState)[x-1][y] && landed && (y == (*gameState)[0].size()-1 || !(*gameState)[x][y+1])){
		speed.x = -2.5f;
		moving = true;
	}
	if(d == Block::right && x < gameState->size()-1 && !(*gameState)[x+1][y] && landed && (y == (*gameState)[0].size()-1 || !(*gameState)[x][y+1])){
		speed.x = 2.5f;
		moving = true;
	}
}

void Block::Collisions(vector<vector<bool>>* gamestate){
	gameState = gamestate;
}

void Block::ProcessCollisions() {

	//Donde está el bloque en GameZone?
	FloatRect Box = s.getGlobalBounds();
	int x = (Box.left-50)/50.f;
	int y = (350 - Box.top)/50;
	
	// Izquierda
	if( speed.x < 0 && (x == 0 || (*gameState)[x-1][y]) ){
		speed.x = 0;
	}
	// Derecha
	if( speed.x > 0 && (x == gameState->size()-1 || (*gameState)[x+1][y])){
		speed.x = 0;
	}
	// Abajo
	if(y == 0 || (*gameState)[x][y-1]){
		landed = true;
		speed.y = 0;
	} else {
		landed=false;
	}
	
	(*gameState)[x][y] = true;
	
	if(x != prevx && y != prevy){		//Libera la posición anterior
		(*gameState)[prevx][prevy] = false;
	}else if(x != prevx){
		(*gameState)[prevx][y] = false;
	}else if(y != prevy){
		(*gameState)[x][prevy] = false;
	}
	prevx = x;
	prevy = y;
}

pair<int, int> Block::GetXY(){
	if(moving){		//Al ser empujado, pasa a ocupar el siguiente lugar en gameState
		if(speed.x > 0)
			return pair<int, int>(prevx+1, prevy);
		if(speed.x < 0)
			return pair<int, int>(prevx-1, prevy);
	}
	return pair<int, int>(prevx, prevy);
}

FloatRect Block::GetRect() const{
	FloatRect Rect = s.getGlobalBounds();
	if(moving){			//Al ser empujado, ocupa además el siguiente bloque
		if(speed.x > 0){
			Rect.width = ((prevx*50+150))-Rect.left;
		}
		if(speed.x < 0){
			Rect.left = (prevx)*50;
			Rect.width = s.getGlobalBounds().left + s.getGlobalBounds().width - Rect.left;
		}
	}
	return Rect;
}

Block::~Block(){
	//Donde está el bloque en GameZone?
	FloatRect Box = s.getGlobalBounds();
	int x = (Box.left-50)/50.f;
	int y = (350 - Box.top)/50;
	
	(*gameState)[x][y] = false;
}

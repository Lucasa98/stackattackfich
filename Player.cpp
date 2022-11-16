#include "Player.h"

using namespace std;

Player::Player(int Lifes = 3){
	t.loadFromFile("player_right.png");
	s.setTexture(t);
	s.setPosition(250, 100);
	speed = Vector2f(0,0);
	s.setColor(Color(255, 255, 255, 255));
	
	increment = 17;
	lifes = Lifes;
	golpeado = false;
	vivo = true;
	landed = false;
	leftFlag = false;
	rightFlag = false;
	empujando = false;
}

void Player::draw(sf::RenderTarget& w, sf::RenderStates states = RenderStates::Default) const{
	w.draw(s, states);
}

void Player::Update(){
	
	if(golpeado){
		Color color = s.getColor();
		if(color.a >= 255 || color.a <= 0) increment *= -1;
		s.setColor(Color(255, 255, 255, color.a+increment));
		
		if(clock.getElapsedTime().asSeconds() >= 3){
			golpeado = false;
			s.setColor(Color(255, 255, 255, 255));
		}
	}
	
	//Movimiento
	speed.y += 9.8f/60.f;
	if(landed)
		speed.x *= 0.9f;
	else
		speed.x *= 0.95f;
	
	if(leftFlag && !rightFlag){
		speed.x = -2;
	}
	else if(rightFlag && !leftFlag){
		speed.x = 2;
	}
	else
		speed.x = 0;
	
	//Colisiones (cancelan movimientos)
	for(size_t i = 0; i < blocks.size(); ++i){
		ProcessBlock(blocks[i]);
	}
	for(size_t i = 0; i < scenario.size(); ++i){
		ProcessCollision(scenario[i]);
	}
	
	Move();
}

void Player::Move(){
	s.move(speed);
}

void Player::MoveLeft(){
	ChangeTexture(0);
	leftFlag = true;
}

void Player::nMoveLeft(){
	leftFlag = false;
}

void Player::MoveRight(){
	ChangeTexture(1);
	rightFlag = true;
}

void Player::nMoveRight(){
	rightFlag = false;
}

void Player::Jump(){
	if(landed){
		speed.y = -5;
		landed = false;
	}
}
void Player::Empujar(){
	empujando = true;
}

void Player::nEmpujar(){
	empujando = false;
	if (rightFlag) {
		ChangeTexture(1);
	} else if(leftFlag){
		ChangeTexture(0);
	}
}

void Player::Collisions(vector<Scenario*>& scenarioAux){
	scenario = scenarioAux;
}

void Player::BlockCollisions(vector<Block*>& b){
	blocks = b;
}

void Player::ChangeTexture(int x){
	if (x==0) {
		t.loadFromFile("player_left.png");
	} else if (x==1) {
		t.loadFromFile("player_right.png");
	} else if (x==2) {
		t.loadFromFile("player_push_left.png");
	} else {
		t.loadFromFile("player_push_right.png");
	}
}

void Player::ProcessBlock(Block* b){
	FloatRect boxPlayer = s.getGlobalBounds();
	FloatRect block = b->GetRect();
	
	float PB = boxPlayer.top + boxPlayer.height;
	float PT = boxPlayer.top;
	float PR = boxPlayer.left + boxPlayer.width;
	float PL = boxPlayer.left;
	float FB = block.top + block.height;
	float FT = block.top;
	float FR = block.left + block.width;
	float FL = block.left;
	
	// Izquierda
	if(	PL + speed.x < FR &&
	   PR + speed.x > FL &&
	   PT < FB &&
	   PB > FT &&
	   speed.x < 0
	   ){
		speed.x = 0;
		
		if(landed && (PB-FB <= 1 && PB-FB >= -1) && empujando && leftFlag){	//Solo puede empujar bloques a su altura
			b->Empujar(Block::left);
			ChangeTexture(2);
		}
	}
	// Derecha
	if(	PR + speed.x > FL &&
	   PL + speed.x < FR &&
	   PT < FB &&
	   PB > FT
	   ){
		speed.x = 0;
		
		if(landed && (PB-FB <= 1 && PB-FB >= -1) && empujando && rightFlag){	//Solo puede empujar bloques a su altura
			b->Empujar(Block::right);
			ChangeTexture(3);
		}
	}
	// Abajo
	if( PB + speed.y > FT &&
	   PT + speed.y < FB &&
	   PL < FR &&
	   PR > FL
	   ){
		landed = true;
		speed.y = 0;
		speed.x *= 0.9f;
	}
	// Arriba
	if( PB + speed.y > FT &&
	   PT + speed.y < FB &&
	   PL < FR &&
	   PR > FL
	   ){
		--lifes;
		vivo = false;
		golpeado = true;
		clock.restart();
	}
}

void Player::ProcessCollision(Scenario* object){
	
	FloatRect boxPlayer = s.getGlobalBounds();
	FloatRect boxFloor = object->GetRect();
	
	float PB = boxPlayer.top + boxPlayer.height;
	float PT = boxPlayer.top;
	float PR = boxPlayer.left + boxPlayer.width;
	float PL = boxPlayer.left;
	float FB = boxFloor.top + boxFloor.height;
	float FT = boxFloor.top;
	float FR = boxFloor.left + boxFloor.width;
	float FL = boxFloor.left;
	
	// Izquierda
	if(	PL + speed.x < FR &&
		PR + speed.x > FL &&
		PT <= FB &&
		PB >= FT
	  ){
		speed.x = 0;
	}
	// Derecha
	if(	PR + speed.x > FL &&
		PL + speed.x < FR &&
		PT <= FB &&
		PB >= FT
	  ){
		speed.x = 0;
	}
	// Abajo
	if( PB + speed.y > FT &&
		PT + speed.y < FB &&
		PL <= FR &&
		PR >= FL
	  ){
		landed = true;
		speed.y = 0;
		speed.x *= 0.9f;
	}
	// Arriba
	if( PB + speed.y > FT &&
		PT + speed.y < FB &&
		PL <= FR &&
		PR >= FL
	  ){
		// ---------------
		
	}
}

bool Player::Vive(){
	return vivo;
}

void Player::SumarVida(int x) {
	lifes += x;
}

void Player::Revive(){
	vivo = true;
}

int Player::count_lifes() {
	return lifes;
}

FloatRect Player::GetRect(){
	return s.getGlobalBounds();
}

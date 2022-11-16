#include "Game.h"
#include <ctime>
using namespace std;
using namespace sf;

int main(){
	srand(time(0));
	Game game;
	game.Play();
	return 0;
}


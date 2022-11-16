#include "Scores.h"

Scores::Scores() : highscores(10) {
	LoadHighscore();
}

void Scores::LoadHighscore(){
	ifstream ifile("highscore.dat", ios::binary);
	if(!ifile.is_open()){		//Si no existe, se crea
		ofstream ofile("highscore.dat", ios::binary);
		ofile.close();
		return;
	}
	
	Score aux;
	for(int i=0;i<10;i++) { 
		ifile.read(reinterpret_cast<char*>(&aux),sizeof(Score));
		highscores[i] = aux;
	}
	ifile.close();
}


bool Scores::Mayor (Score &A, Score &B) {
	if (A.points>B.points) {
		return true;
	} else {
		return false;
	}
}

void Scores::Insert_Score(Score A) {
	vector<Score> High;
	vector<Score>::iterator it = highscores.begin();
	while(Mayor(*it, A) && it != highscores.end()){
		High.push_back(*it);
		++it;
	}
	
	High.push_back(A);
	while(it != highscores.end()){
		High.push_back(*it);
		++it;
	}
	
	highscores = High;
	
	highscores.resize(10);
}

void Scores::SaveHighscore(){
	ofstream ofile("highscore.dat", ios::binary|ios::trunc);
	
	for(size_t i = 0; i < highscores.size(); ++i){
		ofile.write(reinterpret_cast<char*>(&(highscores[i])), sizeof(highscores[i]));
	}
	ofile.close();
}

bool Scores::is_top(int points) {
	for(int i=0;i<10;i++) { 
		if (points>=(highscores[i].points)){
			return true;
		}
	}
	return false;
}

vector<Score> Scores::return_scores() {
	return highscores;
}


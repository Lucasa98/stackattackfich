#pragma once

#include <vector>
#include <fstream>

using namespace std;

struct Score{
	char alias[3] = {'-','-','-'};
	int points = 0;
};

class Scores{
private:
	vector<Score> highscores;
public:
	Scores();
	void LoadHighscore();
	vector<Score> return_scores();
	bool Mayor (Score&,Score&);
	bool is_top(int);
	void SaveHighscore();
	void Insert_Score(Score);
};

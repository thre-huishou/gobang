#pragma once
#include"Chess.h"
class AI
{
public:
	void go();

	void init(Chess* chess);

private:
	Chess* chess;
	vector<vector<int>> ValueMap;

	void calculateValue();

	ChessPos think();
};


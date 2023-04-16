#include "ChessGame.h"

ChessGame::ChessGame(Man * man, AI * ai, Chess * chess)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;
	this->man->init(chess);
	this->ai->init(chess);
}

void ChessGame::play()
{
	chess->init();
	while (1) {
		//先由棋手落子
		man->go();
		if (chess->IsEnd())
		{
			chess->init();
			continue;
		}
		//ai 走
		
		ai->go();
		if (chess->IsEnd())
		{
			chess->init();
			continue;
		}
	}
}

/*
  ������־��
  1��������Ŀ�������ز�
  2�������Ŀ�Ŀ�ܣ������Щ�ࣩ
*/

#include<iostream>
using namespace std;
#include"ChessGame.h"


int main() {

	Man man;

	//Chess chess;
	Chess chess(13,0,0,49.7);
	AI ai;
	ChessGame game(&man, &ai, &chess);
	game.play();
	return 0;
}

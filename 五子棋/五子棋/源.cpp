/*
  开发日志：
  1、创建项目、导入素材
  2、设计项目的框架（设计哪些类）
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

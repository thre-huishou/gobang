#include "Man.h"

void Man::init(Chess * chess)
{
	this->chess = chess;
}

void Man::go()
{
	MOUSEMSG msg;

	ChessPos pos;
	

	while (1) {
		//获取鼠标点集信息
		msg=GetMouseMsg();
		//通过chess对象判断落子是否有效，以及落子功能
		if (msg.uMsg == WM_LBUTTONDOWN&& chess->clickboard(msg.x,msg.y,&pos)) {
			break;
		}
	}

	printf("%d,%d\n", pos.row, pos.col);
	//落子
	chess->ChessDown(&pos, CHESS_BLACK);
	
}

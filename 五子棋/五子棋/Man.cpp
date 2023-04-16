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
		//��ȡ���㼯��Ϣ
		msg=GetMouseMsg();
		//ͨ��chess�����ж������Ƿ���Ч���Լ����ӹ���
		if (msg.uMsg == WM_LBUTTONDOWN&& chess->clickboard(msg.x,msg.y,&pos)) {
			break;
		}
	}

	printf("%d,%d\n", pos.row, pos.col);
	//����
	chess->ChessDown(&pos, CHESS_BLACK);
	
}

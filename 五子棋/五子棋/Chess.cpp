#include "Chess.h"
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include<conio.h>

Chess::Chess(int gradeSize, int margin_x, int margin_y, float chessSize)
{
	this->gradeSize = gradeSize;
	this->margin_x = margin_x;
	this->margin_y = margin_y;
	this->chessSize = chessSize;
	playerFlag = CHESS_BLACK;
	
	for (int i = 0; i < gradeSize; i++)
	{
		vector<int> row;
		for (int j = 0; j < gradeSize; j++)
		{
			row.push_back(0);
		}
		chessMap.push_back(row);
	}
}

void Chess::ChessDown(ChessPos * pos, chess_kind_t val)
{
	int x = chessSize * pos->col-chessSize*0.5;
	int y = chessSize * pos->row - chessSize * 0.5;
	if (val == CHESS_WHITE)
	{
		//�°���
		putimage(x, y, &chessWriteImg);
	}
	else
	{
		//�º���
		putimage(x, y, &chessBlackImg);
	}
	updataGameMap(pos);
}

bool Chess::clickboard(int x, int y, ChessPos * pos)
{
	//���ϵ�����������
	int leftup_x = x / int(chessSize);
	int leftup_y = y / int(chessSize);
	
	int distance_x = x - leftup_x*chessSize;
	int distance_y = y - leftup_y*chessSize;

	if (distance_x <= chessSize *0.4)
	{
		pos->col = leftup_x;
	}
	else if (distance_x >= chessSize * 0.6)
	{
		pos->col = leftup_x+1;
	}
	else
	{
		return false;
	}
	if (distance_y <= chessSize * 0.4)
	{
		pos->row = leftup_y;
	}
	else if (distance_x >= chessSize *0.6)
	{
		pos->row = leftup_y + 1;
	}
	else
	{
		return false;
	}
	if (chessMap[pos->row][pos->col] != 0)
	{
		return false;
	}
	return true;
}

void Chess::init()
{
	//������Ϸ����
	initgraph(596, 596, EX_SHOWCONSOLE);

	//����ͼƬ��ʾ
	loadimage(0, L"./chess.jpg");
	//���ſ�ʼ��ʾ��
	//mciSendString("", 0, 0, 0);

	//���غ���Ͱ���ͼƬ
	loadimage(&chessBlackImg, L"./black.jpg");
	loadimage(&chessWriteImg, L"./write.jpg");

	//�������
	for (int i = 0; i < gradeSize; i++)
	{
		for (int j = 0; j < gradeSize; j++)
		{
			chessMap[i][j] = 0;
		}
	}

	playerFlag = true;

}

int Chess::getGradeSize()
{
	return this->gradeSize;
}

bool Chess::IsEnd()
{
	if (checkwin()) {
		Sleep(1500);
		if (playerFlag==false) {
			//�ղ�������Ǻڷ�
			std::cout << "��ϲ���ʤ����������ʼ��һ��" << endl;
			IMAGE win;
			loadimage(&win, L"./���ʤ��.jpg");
			putimage(0,250, &win);
			Sleep(1000);
		}
		else
		{
			std::cout << "���ϧ�ܣ�������ʼ��һ��" << endl;
			IMAGE loss;
			loadimage(&loss, L"./���ʧ��.jpg");
			putimage(0, 250, &loss);
			Sleep(1000);
		}
		//_getch();//��ͣ
		return true;
	}
	return false;
}

void Chess::updataGameMap(ChessPos * pos)
{
	chessMap[pos->row][pos->col] = playerFlag ? CHESS_BLACK : CHESS_WHITE;
	playerFlag = !playerFlag;
	lastpos = *pos;
}

bool Chess::checkwin()
{
	int row = lastpos.row;
	int col = lastpos.col;
	int continueNumRow = 1;
	int continueNumCol = 1;
	int continueNumupright = 1;
	int continueNumdownright = 1;
	int size = gradeSize;
	//ˮƽ�������Ƿ񹹳�������
	for (int i = 1; i <= 4; i++) {
		if (row + i < size)
		{
			if (chessMap[row][col] == chessMap[row + i][col])//��ʾ��ͬ
			{
				continueNumRow++;
			}
			else break;
		}
	}
	for (int i = 1; i <= 4; i++) {
		if (row - i >= 0)
		{
			if (chessMap[row][col] == chessMap[row - i][col])//��ʾ��ͬ
			{
				continueNumRow++;
			}
			else break;
		}
	}
	//��ֱ�������Ƿ񹹳�������
	for (int i = 1; i <= 4; i++) {
		if (col + i < size)
		{
			if (chessMap[row][col] == chessMap[row][col + i])//��ʾ��ͬ
			{
				continueNumCol++;
			}
			else break;
		}
	}
	for (int i = 1; i <= 4; i++) {
		if (col - i >= 0)
		{
			if (chessMap[row][col] == chessMap[row][col - i])//��ʾ��ͬ
			{
				continueNumCol++;
			}
			else break;
		}
	}
	//���ϵ����·������Ƿ񹹳�������
	for (int i = 1; i <= 4; i++) {
		if (row + i < size&&col + i < size)
		{
			if (chessMap[row][col] == chessMap[row + i][col + i])//��ʾ��ͬ
			{
				continueNumupright++;
			}
			else break;
		}
	}
	for (int i = 1; i <= 4; i++) {
		if (row - i >= 0 && col - i >= 0)
		{
			if (chessMap[row][col] == chessMap[row - i][col - i])//��ʾ��ͬ
			{
				continueNumupright++;
			}
			else break;
		}
	}
	//���µ����Ϸ������Ƿ񹹳�������
	for (int i = 1; i <= 4; i++) {
		if (row + i < size&&col - i >= 0)
		{
			if (chessMap[row][col] == chessMap[row + i][col - i])//��ʾ��ͬ
			{
				continueNumdownright++;
			}
			else break;
		}
	}
	for (int i = 1; i <= 4; i++) {
		if (row - i >= 0 && col + i < size)
		{
			if (chessMap[row][col] == chessMap[row - i][col + i])//��ʾ��ͬ
			{
				continueNumdownright++;
			}
			else break;
		}
	}

	if (continueNumRow >= 5 || continueNumCol >= 5 || continueNumupright >= 5 || continueNumdownright >= 5)
	{
		cout << "����Ӯ�ˣ���" << endl;
		return true;
	}
	return false;
}

int Chess::getchessData(int row, int col)
{

	return chessMap[row][col];
}

int Chess::getchessData(ChessPos * pos)
{
	return chessMap[pos->row][pos->col];
}

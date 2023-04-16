#pragma once
#include<graphics.h>//easyxͼ�ο��ͷ�ļ�
#include<vector>
#include<iostream>
using namespace std;

//��ʾ����λ��
struct ChessPos {
	int row;
	int col;
	ChessPos(int r=0,int c=0):row(r),col(c){}
};

typedef enum
{
	CHESS_WHITE =-1,//����
	CHESS_BLACK =1
}chess_kind_t;

class Chess
{
public:
	Chess(int gradeSize, int margin_x, int margin_y, float chessSize);
	void ChessDown(ChessPos *pos, chess_kind_t val);
	bool clickboard(int x, int y, ChessPos* pos);
	void init();
	int getGradeSize();//��ȡ���̴�С
	bool IsEnd();//�������Ƿ����
	int getchessData(int row, int col);
	int getchessData(ChessPos*pos);
	ChessPos lastpos;
private:
	IMAGE chessBlackImg;
	IMAGE chessWriteImg;
	
	int gradeSize;//���̴�С
	int margin_x;//���̵����߽�
	int margin_y;//���̵Ķ����߽�
	float chessSize;
	vector<vector<int>> chessMap;//�洢��ǰ������ӷֲ���� 0��ʾ�հף�1�Ǻ��� -1�ǰ���

	bool playerFlag;//��ʾ���ڸ�˭�£�true��ʾ�ڣ�flase��ʾ����

	void updataGameMap(ChessPos* pos);
	bool checkwin();//����������ͷ���true

	
};


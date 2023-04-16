#pragma once
#include<graphics.h>//easyx图形库的头文件
#include<vector>
#include<iostream>
using namespace std;

//表示棋盘位置
struct ChessPos {
	int row;
	int col;
	ChessPos(int r=0,int c=0):row(r),col(c){}
};

typedef enum
{
	CHESS_WHITE =-1,//白棋
	CHESS_BLACK =1
}chess_kind_t;

class Chess
{
public:
	Chess(int gradeSize, int margin_x, int margin_y, float chessSize);
	void ChessDown(ChessPos *pos, chess_kind_t val);
	bool clickboard(int x, int y, ChessPos* pos);
	void init();
	int getGradeSize();//获取棋盘大小
	bool IsEnd();//检查棋局是否结束
	int getchessData(int row, int col);
	int getchessData(ChessPos*pos);
	ChessPos lastpos;
private:
	IMAGE chessBlackImg;
	IMAGE chessWriteImg;
	
	int gradeSize;//棋盘大小
	int margin_x;//棋盘的左侧边界
	int margin_y;//棋盘的顶部边界
	float chessSize;
	vector<vector<int>> chessMap;//存储当前棋局棋子分布情况 0表示空白，1是黑子 -1是白子

	bool playerFlag;//表示现在该谁下，true表示黑，flase表示白子

	void updataGameMap(ChessPos* pos);
	bool checkwin();//如果结束，就返回true

	
};


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
		//下白棋
		putimage(x, y, &chessWriteImg);
	}
	else
	{
		//下黑棋
		putimage(x, y, &chessBlackImg);
	}
	updataGameMap(pos);
}

bool Chess::clickboard(int x, int y, ChessPos * pos)
{
	//左上的行列像素数
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
	//创建游戏窗口
	initgraph(596, 596, EX_SHOWCONSOLE);

	//棋盘图片显示
	loadimage(0, L"./chess.jpg");
	//播放开始提示音
	//mciSendString("", 0, 0, 0);

	//加载黑棋和白棋图片
	loadimage(&chessBlackImg, L"./black.jpg");
	loadimage(&chessWriteImg, L"./write.jpg");

	//清理棋局
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
			//刚才走棋的是黑方
			std::cout << "恭喜玩家胜利！！！开始下一局" << endl;
			IMAGE win;
			loadimage(&win, L"./玩家胜利.jpg");
			putimage(0,250, &win);
			Sleep(1000);
		}
		else
		{
			std::cout << "玩家惜败！！！开始下一局" << endl;
			IMAGE loss;
			loadimage(&loss, L"./玩家失败.jpg");
			putimage(0, 250, &loss);
			Sleep(1000);
		}
		//_getch();//暂停
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
	//水平方向上是否构成了五子
	for (int i = 1; i <= 4; i++) {
		if (row + i < size)
		{
			if (chessMap[row][col] == chessMap[row + i][col])//表示相同
			{
				continueNumRow++;
			}
			else break;
		}
	}
	for (int i = 1; i <= 4; i++) {
		if (row - i >= 0)
		{
			if (chessMap[row][col] == chessMap[row - i][col])//表示相同
			{
				continueNumRow++;
			}
			else break;
		}
	}
	//垂直方向上是否构成了五子
	for (int i = 1; i <= 4; i++) {
		if (col + i < size)
		{
			if (chessMap[row][col] == chessMap[row][col + i])//表示相同
			{
				continueNumCol++;
			}
			else break;
		}
	}
	for (int i = 1; i <= 4; i++) {
		if (col - i >= 0)
		{
			if (chessMap[row][col] == chessMap[row][col - i])//表示相同
			{
				continueNumCol++;
			}
			else break;
		}
	}
	//左上到右下方向上是否构成了五子
	for (int i = 1; i <= 4; i++) {
		if (row + i < size&&col + i < size)
		{
			if (chessMap[row][col] == chessMap[row + i][col + i])//表示相同
			{
				continueNumupright++;
			}
			else break;
		}
	}
	for (int i = 1; i <= 4; i++) {
		if (row - i >= 0 && col - i >= 0)
		{
			if (chessMap[row][col] == chessMap[row - i][col - i])//表示相同
			{
				continueNumupright++;
			}
			else break;
		}
	}
	//左下到右上方向上是否构成了五子
	for (int i = 1; i <= 4; i++) {
		if (row + i < size&&col - i >= 0)
		{
			if (chessMap[row][col] == chessMap[row + i][col - i])//表示相同
			{
				continueNumdownright++;
			}
			else break;
		}
	}
	for (int i = 1; i <= 4; i++) {
		if (row - i >= 0 && col + i < size)
		{
			if (chessMap[row][col] == chessMap[row - i][col + i])//表示相同
			{
				continueNumdownright++;
			}
			else break;
		}
	}

	if (continueNumRow >= 5 || continueNumCol >= 5 || continueNumupright >= 5 || continueNumdownright >= 5)
	{
		cout << "有人赢了！！" << endl;
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

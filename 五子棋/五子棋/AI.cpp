#include "AI.h"

void AI::go()
{
	ChessPos pos = think();
	Sleep(1000);
	chess->ChessDown(&pos, CHESS_WHITE);

}

void AI::init(Chess * chess)
{
	this->chess = chess;
	int size = chess->getGradeSize();
	for (int i =0; i < size; i++)
	{
		vector<int> row;
		for (int j = 0; j < size; j++)
		{
			row.push_back(0);
		}
		ValueMap.push_back(row);
	}
}

void AI::calculateValue()
{
	int personNum = 0;
	int ainum = 0;
	int emptynum = 0;
	int size = ValueMap.size();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			ValueMap[i][j] = 0;
		}
	}
	int size1 = chess->getGradeSize();
	for (int row = 0; row < size1; row++) {
		for (int col = 0; col < size1; col++) {
			/*personNum = 0;
			ainum = 0;
			emptynum = 0;*/
			//对每一个点进行计算
			if (chess->getchessData(row, col))continue;
			
			//计算8个方向的价值
			for (int y = -1; y <= 0; y++) {
				for (int x = -1; x <= 1; x++) {
					if (y == 0 && x == 0)continue;
					if (y == 0 && x != 1)continue;
					personNum = 0;
					ainum = 0;
					emptynum = 0;
					//假设黑子在该位置落子，会构成什么棋型
					for (int i = 1; i <= 4; i++) {
						int curRow = row + i * y;
						int curCol = col + i * x;
						if (curRow >= 0 && curRow < size1&&curCol >= 0 && curCol < size&&chess->getchessData(curRow,curCol)==1) {
							personNum++;
						}
						else if (curRow >= 0 && curRow < size1&&curCol >= 0 && curCol < size&&chess->getchessData(curRow, curCol) == 0) {
							emptynum++;
							break;
						}
						else
						{
							break;
						}
					}
					//反向继续计算
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row - i * y;
						int curCol = col - i * x;
						if (curRow >= 0 && curRow < size1&&curCol >= 0 && curCol < size&&chess->getchessData(curRow, curCol) == 1) {
							personNum++;
						}
						else if (curRow >= 0 && curRow < size1&&curCol >= 0 && curCol < size&&chess->getchessData(curRow, curCol) == 0) {
							emptynum++;
							break;
						}
						else
						{
							break;
						}
					}

					if (personNum == 1) {//连2
						ValueMap[row][col] += 10;
					}
					else if (personNum == 2) {
						if (emptynum == 1) {
							ValueMap[row][col] += 30;
						}
						else if (emptynum == 2) {
							ValueMap[row][col] += 40;
						}
					}
					else if (personNum == 3) {
						if (emptynum == 1) {
							ValueMap[row][col] = 60;
						}
						else if (emptynum == 2) {
							ValueMap[row][col] = 200;
						}
					}
					else if (personNum == 4) {
						ValueMap[row][col] = 20000;
					}

					//假设白棋在该位置落子，会构成什么棋型
					emptynum = 0;
					for (int i = 1; i <= 4; i++) {
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size&&curCol >= 0 && curCol < size&&chess->getchessData(curRow, curCol) == -1) {
							ainum++;
						}
						else if (curRow >= 0 && curRow < size&&curCol >= 0 && curCol < size&&chess->getchessData(curRow, curCol) == 0) {
							emptynum++;
							break;
						}
						else {
							break;
						}
					}

					for (int i = 1; i <= 4; i++) {
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 && curRow < size&&curCol >= 0 && curCol < size&&chess->getchessData(curRow, curCol) == -1) {
							ainum++;
						}
						else if (curRow >= 0 && curRow < size&&curCol >= 0 && curCol < size&&chess->getchessData(curRow, curCol) == 0) {
							emptynum++;
							break;
						}
						else {
							break;
						}
					}

					if (ainum == 0) {
						ValueMap[row][col] += 5;
					}
					else if (ainum == 1) {
						ValueMap[row][col] += 10;
					}
					else if (ainum == 2) {
						if (emptynum == 1) {
							ValueMap[row][col] += 25;
						}
						else if (emptynum == 2) {
							ValueMap[row][col] += 50;
						}
					}
					else if (ainum == 3) {
						if (emptynum == 1) {
							ValueMap[row][col] += 55;
						}
						else if (emptynum == 2) {
							ValueMap[row][col] += 10000;
						}
					}
					else if (ainum == 4) {
						ValueMap[row][col] = 30000;
					}
				}
			}
		}
	}
}

ChessPos AI::think()
{
	calculateValue();
	int maxvalue = 0;
	vector<ChessPos> maxpoints;
	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			if (chess->getchessData(row, col) == 0) {
				if (ValueMap[row][col] > maxvalue) {
					maxvalue = ValueMap[row][col];
					maxpoints.clear();
					maxpoints.push_back(ChessPos(row, col));
				}
				else if (ValueMap[row][col] == maxvalue) {
					maxpoints.push_back(ChessPos(row, col));
				}
			}
		}
	}
	int index = rand() % maxpoints.size();
	return maxpoints[index];
}

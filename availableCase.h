#pragma once
#define vertical_max 19
#define horizontal_max 19
#define stonetype 3
#include <iostream>
#include <string.h>
using namespace std;
enum stone { EMPTY = 0, BLACK = 1, WHITE = 2, RANDOM = 3 };
enum direction {HORIZONTAL=0, VERTICAL=1, DIAG_TOPLEFT=2, DIAG_TOPRIGHT=3};

class caseID
{
private:
	int startX;//경우의수 시작 x좌표
	int startY;//경우의수 시작 y좌표
	int direction;//경우의수의 방향
	bool valid;
public:
	caseID(int x, int y, int dir)
	{
		valid = false;
		if (dir==HORIZONTAL)
		{
			if (x >= 0 && x <= horizontal_max - 6 && y >= 0 && y<=vertical_max)
			{
				startX = x;
				startY = y;
				direction = dir;
				valid = true;
			}
		}
		else if (dir == VERTICAL)
		{
			if (x >= 0 && x <= horizontal_max  && y >= 0 && y<=vertical_max-6)
			{
				startX = x;
				startY = y;
				direction = dir;
				valid = true;
			}
		}
		else if (dir == DIAG_TOPLEFT)
		{
			if (x >= 0 && x <= horizontal_max - 6 && y >= 0 && y<=vertical_max - 6)
			{
				startX = x;
				startY = y;
				direction = dir;
				valid = true;
			}
		}
		else if (dir == DIAG_TOPRIGHT)
		{
			if (x >= 5 && x <= horizontal_max && y >= 0 && y<=vertical_max - 6)
			{
				startX = x;
				startY = y;
				direction = dir;
				valid = true;
			}
		}

		if (!valid)
		{
			cout << "생성실패 - 잘못된 시작점 정보" << endl;
			startX = -1;
			startY = -1;
			direction = -1;
		}
	}
	int getX()
	{
		return startX;
	}
	int getY()
	{
		return startY;
	}
	int getDirection()
	{
		return direction;
	}
	bool isvalid()
	{
		return valid;
	}
};
class CaseInfo : public  caseID
{
private:
	const caseID ID;

	int stoneinfo[6];
	CaseInfo(int x, int y, int dir)
		: ID(x, y, dir)
	{
		stoneinfo[0] = EMPTY;
		stoneinfo[1] = EMPTY;
		stoneinfo[2] = EMPTY;
		stoneinfo[3] = EMPTY;
		stoneinfo[4] = EMPTY;
		stoneinfo[5] = EMPTY;
	}
	bool setStone(int loc, int type)
	{
		if (stoneinfo[loc] == EMPTY && type>=BLACK && type<=RANDOM)
		{
			stoneinfo[loc] = type;
			return true;
		}
	}
	bool isMydomain(int x, int y)
	{
		switch (ID.getDirection)
		{
		case HORIZONTAL:
			break;
		case VERTICAL:
			break;
		case DIAG_TOPLEFT:
			break;
		case DIAG_TOPRIGHT:
			break;
		}
	}
};
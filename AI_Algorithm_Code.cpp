// Samsung Go Tournament Form C (g++-4.8.3)

/*
[AI �ڵ� �ۼ� ���]

1. char info[]�� �迭 �ȿ�					"TeamName:�ڽ��� ����,Department:�ڽ��� �Ҽ�"					������ �ۼ��մϴ�.
( ���� ) Teamname:�� Department:�� �� ���� �մϴ�.
"�ڽ��� ����", "�ڽ��� �Ҽ�"�� �����ؾ� �մϴ�.

2. �Ʒ��� myturn() �Լ� �ȿ� �ڽŸ��� AI �ڵ带 �ۼ��մϴ�.

3. AI ������ �׽�Ʈ �Ͻ� ���� "���� �˰����ȸ ��"�� ����մϴ�.

4. ���� �˰��� ��ȸ ���� �����ϱ⿡�� �ٵϵ��� ���� ��, �ڽ��� "����" �� �� �˰����� �߰��Ͽ� �׽�Ʈ �մϴ�.



[���� �� �Լ�]
myturn(int cnt) : �ڽ��� AI �ڵ带 �ۼ��ϴ� ���� �Լ� �Դϴ�.
int cnt (myturn()�Լ��� �Ķ����) : ���� �� �� �־��ϴ��� ���ϴ� ����, cnt�� 1�̸� ���� ���� ��  �� ����  �δ� ��Ȳ(�� ��), cnt�� 2�̸� �� ���� ���� �δ� ��Ȳ(�� ��)
int  x[0], y[0] : �ڽ��� �� ù �� ° ���� x��ǥ , y��ǥ�� ����Ǿ�� �մϴ�.
int  x[1], y[1] : �ڽ��� �� �� �� ° ���� x��ǥ , y��ǥ�� ����Ǿ�� �մϴ�.
void domymove(int x[], int y[], cnt) : �� ������ ��ǥ�� �����ؼ� ���


//int board[BOARD_SIZE][BOARD_SIZE]; �ٵ��� �����Ȳ ��� �־� �ٷλ�� ������. ��, ���������ͷ� ���� �������
// ������ ���� ��ġ�� �ٵϵ��� ������ �ǰ��� ó��.

boolean ifFree(int x, int y) : ���� [x,y]��ǥ�� �ٵϵ��� �ִ��� Ȯ���ϴ� �Լ� (������ true, ������ false)
int showBoard(int x, int y) : [x, y] ��ǥ�� ���� ���� �����ϴ��� �����ִ� �Լ� (1 = �ڽ��� ��, 2 = ����� ��, 3 = ��ŷ)


<-------AI�� �ۼ��Ͻ� ��, ���� �̸��� �Լ� �� ���� ����� �������� �ʽ��ϴ�----->
*/

#include <stdio.h>
#include <stdarg.h>
#include <Windows.h>
#include <time.h>
#include "Connect6Algo.h"
#include <iostream>
#include <string.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <list>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <iomanip>
#include <Windows.h>
using namespace std;
//CLASS START

#define vertical_max 19
#define horizontal_max 19
#define stonetype 3
void myLog(const char* tag, const char* content, ...);
enum stone { EMPTY = 0, BLACK = 1, WHITE = 2, RANDOM = 3 };
enum direction { HORIZONTAL = 0, VERTICAL = 1, DIAG_TOPLEFT = 2, DIAG_TOPRIGHT = 3 };

struct coord
{
	int x;
	int y;
};
class CaseID
{
private:
	int startX;//����Ǽ� ���� x��ǥ
	int startY;//����Ǽ� ���� y��ǥ
	int direction;//����Ǽ��� ����
				  //int priority;//
	bool valid;
	int stoneinfo[6];
	int stone_count;//�Լ� �����
	int past_stone_count;
	int case_dominant;//���� ����(EMPTY=0 / BLACK=1 : �� �������� / WHITE=2 : �� �������� / RANDOM=3 : �������� -> invalid)
public:
	CaseID(int x, int y, int dir)
	{
		valid = false;
		//priority = -1;
		stoneinfo[0] = EMPTY;
		stoneinfo[1] = EMPTY;
		stoneinfo[2] = EMPTY;
		stoneinfo[3] = EMPTY;
		stoneinfo[4] = EMPTY;
		stoneinfo[5] = EMPTY;
		stone_count = EMPTY;
		case_dominant = EMPTY;

		if (dir == HORIZONTAL)
		{
			if (x >= 0 && x < horizontal_max - 5 && y >= 0 && y < vertical_max)
			{
				startX = x;
				startY = y;
				direction = dir;
				valid = true;
			}
		}
		else if (dir == VERTICAL)
		{
			if (x >= 0 && x < horizontal_max && y >= 0 && y < vertical_max - 5)
			{
				startX = x;
				startY = y;
				direction = dir;
				valid = true;
			}
		}
		else if (dir == DIAG_TOPLEFT)
		{
			if (x >= 0 && x < horizontal_max - 5 && y >= 0 && y < vertical_max - 5)
			{
				startX = x;
				startY = y;
				direction = dir;
				valid = true;
			}
		}
		else if (dir == DIAG_TOPRIGHT)
		{
			if (x >= 5 && x < horizontal_max && y >= 0 && y < vertical_max - 5)
			{
				startX = x;
				startY = y;
				direction = dir;
				valid = true;
			}
		}

		if (!valid)
		{
			startX = -1;
			startY = -1;
			direction = -1;
		}
	}
	int getPriority_diff()
	{
		return stone_count - past_stone_count;
	}
	int getX() const
	{
		return startX;
	}
	int getY() const
	{
		return startY;
	}
	int getDirection() const
	{
		return direction;
	}
	int getPriority() const
	{
		return getStone_count();
	}
	bool isvalid() const
	{
		return valid;
	}
	bool setstone(int loc, int type)//�浹 Ȥ�� �鵹 ������
	{
		if (stoneinfo[loc] != 0 && type == EMPTY)
		{
			stoneinfo[loc] = type;
			stone_count--;
			int black_count = 0;
			int white_count = 0;
			int random_count = 0;
			for (int i = 0; i < 6; i++)
			{
				if (stoneinfo[i] == BLACK)
					black_count++;
				else if (stoneinfo[i] == WHITE)
					white_count++;
				else if (stoneinfo[i] == RANDOM)
					random_count++;
			}
			if (black_count > 0 && white_count == 0)
			{
				case_dominant = BLACK;
				return true;
			}
			else if (black_count == 0 && white_count > 0)
			{
				case_dominant = WHITE;
				return true;
			}
			else if (black_count == 0 && white_count == 0)
			{
				case_dominant = EMPTY;
				return true;
			}
			else if (black_count > 0 && white_count > 0)
			{
				case_dominant = RANDOM;
				return true;
			}
			return false;
		}
		if (stoneinfo[loc] == 0)
		{
			stoneinfo[loc] = type;
			past_stone_count = stone_count++;
			//cout << "�����Ϸ� : x=" << startX << " y=" << startY << " Direction=" << direction << endl;
			if (case_dominant == EMPTY)//����ִ� ���¿��� ������ ���
			{
				case_dominant = type;
			}
			else if (case_dominant == type)//�������϶� �鵹,�������ϋ� �浹�� ������ ���
			{
			}
			else if (case_dominant != EMPTY && case_dominant != type)//�������϶� �浹, �������϶� �鵹�� ������ ���
			{
				case_dominant = RANDOM;
			}
			return true;
		}
		else
		{
			//cout << "�̹� ���� ��ġ���ִ� �� " << endl;
			return false;
		}
	}

	int setstone2(int loc, int type)//��ȭ�� Ȯ�ο�
	{
		if (stoneinfo[loc] != 0 && type == EMPTY)
		{
			stoneinfo[loc] = type;
			stone_count--;
			int black_count = 0;
			int white_count = 0;
			int random_count = 0;
			for (int i = 0; i < 6; i++)
			{
				if (stoneinfo[i] == BLACK)
					black_count++;
				else if (stoneinfo[i] == WHITE)
					white_count++;
				else if (stoneinfo[i] == RANDOM)
					random_count++;
			}
			if (black_count > 0 && white_count == 0)
			{
				case_dominant = BLACK;
				return 0;
			}
			else if (black_count == 0 && white_count > 0)
			{
				case_dominant = WHITE;
				return 0;
			}
			else if (black_count == 0 && white_count == 0)
			{
				case_dominant = EMPTY;
				return 0;
			}
			else if (black_count > 0 && white_count > 0)
			{
				case_dominant = RANDOM;
				return 0;
			}
			return 0;
		}
		if (stoneinfo[loc] == 0)
		{
			stoneinfo[loc] = type;
			past_stone_count = stone_count++;
			//cout << "�����Ϸ� : x=" << startX << " y=" << startY << " Direction=" << direction << endl;
			if (case_dominant == EMPTY)//����ִ� ���¿��� ������ ���
			{
				case_dominant = type;
				return 1 * (past_stone_count + 1);//���ο� ������ ����Ͽ��� ��� ����ġ 1
			}
			else if (case_dominant == type)//�������϶� �鵹,�������ϋ� �浹�� ������ ���
			{
				return 1 * (past_stone_count + 1);//���� ������ �����Ͽ��� ��� ����ġ 1
			}
			else if (case_dominant != EMPTY && case_dominant != type)//�������϶� �浹, �������϶� �鵹�� ������ ���
			{
				case_dominant = RANDOM;
				return 1 * (past_stone_count + 1);//���� ������ �ƴѰ��� ���� ��ȿȭ ��Ų ��� ����ġ 1
			}
		}
		else
		{
			//cout << "�̹� ���� ��ġ���ִ� �� " << endl;
			return -1000;
		}
	}

	bool setstone(int loc, bool isRandom)//Block �� ������
	{
		if (stoneinfo[loc] == 0)
		{
			stoneinfo[loc] = RANDOM;
			past_stone_count = stone_count++;
			//cout << "�����Ϸ� : x=" << startX << " y=" << startY << " Direction=" << direction << endl;
			//if (case_dominant == EMPTY)//����ִ� ���¿��� ������ ���
			//{
			//	case_dominant = type;
			//}
			//else if (case_dominant == type)//�������϶� �鵹,�������ϋ� �浹�� ������ ���
			//{
			//}
			//else if (case_dominant != EMPTY && case_dominant != type)//�������϶� �浹, �������϶� �鵹�� ������ ���
			//{
			//	case_dominant = RANDOM;
			//}
			case_dominant = EMPTY;
			return true;
		}
		else
		{
			//cout << "�̹� ���� ��ġ���ִ� �� " << endl;
			return false;
		}
	}

	int getStoneinfo(int idx)
	{
		return stoneinfo[idx];
	}
	int getStone_count() const
	{
		int ret = 0;
		for (int i = 0; i < 6; i++)
		{
			if (stoneinfo[i] != EMPTY)
				ret++;
		}
		//return stone_count;
		return ret;
	}
	int getCase_dominant()
	{
		int black = 0;
		int white = 0;
		int random = 0;
		for (int i = 0; i < 6; i++)
		{
			if (stoneinfo[i] == BLACK)
			{
				black++;
			}
			else if (stoneinfo[i] == WHITE)
			{
				white++;
			}
			else if (stoneinfo[i] == RANDOM)
			{
				random++;
			}
		}
		if (black > 0 && white > 0)
			return RANDOM;
		else if (black == 0 && white > 0)
			return WHITE;
		else if (black > 0 && white == 0)
			return BLACK;
		else
			return EMPTY;
		//return case_dominant;
	}


	coord changeToCoordinate(int loc)
	{
		coord ret;
		switch (direction)
		{
		case HORIZONTAL:
			ret.x = startX + loc;
			ret.y = startY;
			break;
		case VERTICAL:
			ret.x = startX;
			ret.y = startY + loc;
			break;
		case DIAG_TOPLEFT:
			ret.x = startX + loc;
			ret.y = startY + loc;
			break;
		case DIAG_TOPRIGHT:
			ret.x = startX - loc;
			ret.y = startY + loc;
			break;
		}
		return ret;
	}
};

class CaseInfo
{
private:
	int startX;//����Ǽ� ���� x��ǥ
	int startY;//����Ǽ� ���� y��ǥ
	vector<CaseID> vector_case;
	int direction_count;

public:
	CaseInfo(int x, int y)
	{
		startX = x;
		startY = y;
		direction_count = 0;
		for (int i = 0; i <= DIAG_TOPRIGHT; i++)
		{
			CaseID temp(x, y, i);
			if (temp.isvalid())
			{
				vector_case.push_back(temp);
				direction_count++;
			}
		}
	}
	int setStone(int x, int y, int type)
	{
		if (type == EMPTY)
		{
			int count = 0;
			for (int i = 0; i<direction_count; i++)
			{
				int loc = isMydomain(x, y, vector_case[i].getDirection());
				if (loc != -1)
				{
					if (vector_case[i].setstone(loc, EMPTY))
						count--;
				}
			}
		}
		else
		{
			int count = 0;
			for (int i = 0; i < direction_count; i++)
			{
				int loc = isMydomain(x, y, vector_case[i].getDirection());
				if (loc != -1)
				{
					if (vector_case[i].setstone(loc, type))
						count++;
				}
			}
			return count;
		}
	}

	int setStone2(int x, int y, int type)//��ȭ�� Ȯ�ο�
	{
		if (type == EMPTY)
		{
			int count = 0;
			for (int i = 0; i<direction_count; i++)
			{
				int loc = isMydomain(x, y, vector_case[i].getDirection());
				if (loc != -1)
				{
					if (vector_case[i].setstone2(loc, EMPTY))
						count--;
				}
			}
		}
		else
		{
			int count = 0;
			for (int i = 0; i < direction_count; i++)
			{
				int loc = isMydomain(x, y, vector_case[i].getDirection());
				if (loc != -1)
				{
					int temp = vector_case[i].setstone2(loc, type);
					if (temp > 0)
						count += temp;
				}
			}
			return count;
		}
	}
	int setStone(int x, int y, bool isRandom)
	{
		int count = 0;
		for (int i = 0; i < direction_count; i++)
		{
			int loc = isMydomain(x, y, vector_case[i].getDirection());
			if (loc != -1)
			{
				if (vector_case[i].setstone(loc, true))
					count++;
			}
		}
		return count;
	}
	int isMydomain(int x, int y, int dir)
	{
		switch (dir)
		{
		case HORIZONTAL:
			if (startY == y && (x <= startX + 5 && x >= startX))
			{
				return x - startX;
			}
			else
				return -1;
			break;
		case VERTICAL:
			if (startX == x && (y <= startY + 5 && y >= startY))
			{
				return y - startY;
			}
			else
				return -1;
			break;
		case DIAG_TOPLEFT:
			if ((x <= startX + 5 && x >= startX) && (y <= startY + 5 && y >= startY))
			{
				return ((x - startX == y - startY) ? x - startX : -1);
			}
			else
				return -1;
			break;
		case DIAG_TOPRIGHT:
			if ((x >= startX - 5 && x <= startX) && (y <= startY + 5 && y >= startY))
			{
				return ((startX - x == y - startY) ? startX - x : -1);
			}
			else
				return -1;
			break;
		default:
			return -1;
		}
	}
	int findcase(int dir)
	{
		for (int i = 0; i < vector_case.size(); i++)
		{
			if (vector_case[i].getDirection() == dir)
				return i;
		}
		return -1;
	}

	void printStoneState(int dir)
	{
		if (findcase(dir) != -1)
		{
			switch (dir)
			{
			case HORIZONTAL:
				for (int i = 0; i < 6; i++)
					printf("[%d]", vector_case[findcase(dir)].getStoneinfo(i));
				cout << endl;
				cout << "DOMINANT : " << vector_case[findcase(dir)].getCase_dominant() << endl;;
				cout << endl;
				break;
			case VERTICAL:
				for (int i = 0; i < 6; i++)
					printf("[%d]\n", vector_case[findcase(dir)].getStoneinfo(i));
				cout << endl;
				cout << "DOMINANT : " << vector_case[findcase(dir)].getCase_dominant() << endl;;
				break;
			case DIAG_TOPLEFT:
				for (int i = 0; i < 6; i++)
				{
					for (int j = 0; j < i; j++)
						printf("   ");
					printf("[%d]\n", vector_case[findcase(dir)].getStoneinfo(i));
				}
				cout << "DOMINANT : " << vector_case[findcase(dir)].getCase_dominant() << endl;;
				cout << endl;
				break;
			case DIAG_TOPRIGHT:
				for (int i = 0; i < 6; i++)
				{
					for (int j = 5 - i; j > 0; j--)
						printf("   ");
					printf("[%d]\n", vector_case[findcase(dir)].getStoneinfo(i));
				}
				cout << "DOMINANT : " << vector_case[findcase(dir)].getCase_dominant() << endl;;
				cout << endl;
				break;
			}
		}
	}

	int getX(int dir) const
	{
		if (vector_case.size() < dir)
			return vector_case[dir].getX();
		else
			return -1;
	}
	int getY(int dir) const
	{
		if (vector_case.size() < dir)
			return vector_case[dir].getY();
		else
			return -1;
	}
	int getDirection(int dir) const
	{
		if (vector_case.size() < dir)
			return vector_case[dir].getDirection();
		else
			return -1;
	}
	int getPriority(int dir) const
	{
		if (vector_case.size() < dir)
			return vector_case[dir].getPriority();
		else
			return -1;
	}
	bool isvalid(int dir) const
	{
		if (vector_case.size() < dir)
			return vector_case[dir].isvalid();
		else
			return -1;
	}
	int getDirectioncount()
	{
		return direction_count;
	}
	CaseID getCaseID(int idx)
	{
		return vector_case[idx];
	}
	int getStartX()
	{
		return startX;
	}
	int getStartY()
	{
		return startY;
	}
};

//CLASS END
//int seed = 1;


int MyBoard[19][19] = { 0 };


int showMyBoard(int x, int y)
{
	return MyBoard[x][y];
}

int deleteStoneOnEachCase(vector<vector<CaseInfo>>& vector_case, int x, int y)
{
	if (x >= 0 && y >= 0 && x <= 18 && y <= 18)
	{
		MyBoard[x][y] = EMPTY;
		int counter = 0;
		if (x < vector_case.size() && y < vector_case[x].size() && x >= 0 && y >= 0)
		{
			counter = counter + vector_case[x][y].setStone(x, y, EMPTY);//Center
		}
		for (int i = 1; i < 6; i++)//HORIZONTAL case
		{
			if (x - i < vector_case.size() && y < vector_case[x - i].size() && x - i >= 0 && y >= 0)
			{
				counter = counter + vector_case[x - i][y].setStone(x, y, EMPTY);
			}
		}

		for (int i = 1; i < 6; i++)//VERTICAL case
		{
			if (x < vector_case.size() && y - i < vector_case[x].size() && x >= 0 && y - i >= 0)
			{
				counter = counter + vector_case[x][y - i].setStone(x, y, EMPTY);
			}
		}

		for (int i = 1; i < 6; i++)//DIAG_TOPLEFT case
		{
			if (x - i < vector_case.size() && y - i < vector_case[x - i].size() && x - i >= 0 && y - i >= 0)
			{
				counter = counter + vector_case[x - i][y - i].setStone(x, y, EMPTY);
			}
		}

		for (int i = 1; i < 6; i++)//DIAG_TOPRIGHT case
		{
			if (x + i < vector_case.size() && y - i < vector_case[x + i].size() && x + i >= 0 && y - i >= 0)
			{
				counter = counter + vector_case[x + i][y - i].setStone(x, y, EMPTY);
			}
		}
		return counter;
	}
	else
	{
		return 0;
	}
}

int setStoneOnEachCase2(vector<vector<CaseInfo>>& vector_case, int x, int y, int type)//1���� ������ ���� �ش��ϴ� ��� ����� ���� ���� �����Ѵ�.
{
	if (x >= 0 && y >= 0 && x <= 18 && y <= 18)
	{
		MyBoard[x][y] = type;
		int counter = 0;
		if (x < vector_case.size() && y < vector_case[x].size() && x >= 0 && y >= 0)
		{
			counter += vector_case[x][y].setStone2(x, y, type);//Center
		}
		for (int i = 1; i < 6; i++)//HORIZONTAL case
		{
			if (x - i < vector_case.size() && y < vector_case[x - i].size() && x - i >= 0 && y >= 0)
			{
				counter += vector_case[x - i][y].setStone2(x, y, type);
			}
		}

		for (int i = 1; i < 6; i++)//VERTICAL case
		{
			if (x < vector_case.size() && y - i < vector_case[x].size() && x >= 0 && y - i >= 0)
			{
				counter += vector_case[x][y - i].setStone2(x, y, type);
			}
		}

		for (int i = 1; i < 6; i++)//DIAG_TOPLEFT case
		{
			if (x - i < vector_case.size() && y - i < vector_case[x - i].size() && x - i >= 0 && y - i >= 0)
			{
				counter += vector_case[x - i][y - i].setStone2(x, y, type);
			}
		}

		for (int i = 1; i < 6; i++)//DIAG_TOPRIGHT case
		{
			if (x - i < vector_case.size() && y + i < vector_case[x - i].size() && x - i >= 0 && y + i >= 0)
			{
				counter += vector_case[x - i][y + i].setStone2(x, y, type);
			}
		}
		return counter;
	}
	else
	{
		return 0;
	}
}

int setStoneOnEachCase(vector<vector<CaseInfo>>& vector_case, int x, int y, int type)//1���� ������ ���� �ش��ϴ� ��� ����� ���� ���� �����Ѵ�.
{
	if (x >= 0 && y >= 0 && x <= 18 && y <= 18)
	{
		MyBoard[x][y] = type;
		int counter = 0;
		if (x < vector_case.size() && y < vector_case[x].size() && x >= 0 && y >= 0)
		{
			counter = counter + vector_case[x][y].setStone(x, y, type);//Center
		}
		for (int i = 1; i < 6; i++)//HORIZONTAL case
		{
			if (x - i < vector_case.size() && y < vector_case[x - i].size() && x - i >= 0 && y >= 0)
			{
				counter = counter + vector_case[x - i][y].setStone(x, y, type);
			}
		}

		for (int i = 1; i < 6; i++)//VERTICAL case
		{
			if (x < vector_case.size() && y - i < vector_case[x].size() && x >= 0 && y - i >= 0)
			{
				counter = counter + vector_case[x][y - i].setStone(x, y, type);
			}
		}

		for (int i = 1; i < 6; i++)//DIAG_TOPLEFT case
		{
			if (x - i < vector_case.size() && y - i < vector_case[x - i].size() && x - i >= 0 && y - i >= 0)
			{
				counter = counter + vector_case[x - i][y - i].setStone(x, y, type);
			}
		}

		for (int i = 1; i < 6; i++)//DIAG_TOPRIGHT case
		{
			if (x + i < vector_case.size() && y - i < vector_case[x + i].size() && x + i >= 0 && y - i >= 0)
			{
				counter = counter + vector_case[x + i][y - i].setStone(x, y, type);
			}
		}
		return counter;
	}
	else
	{
		return 0;
	}
}

int setRANDOMOnEachCase(vector<vector<CaseInfo>>& vector_case, int x, int y)//1���� ������ ���� �ش��ϴ� ��� ����� ���� ���� �����Ѵ�.
{
	MyBoard[x][y] = RANDOM;
	if (x >= 0 && y >= 0 && x <= 18 && y <= 18)
	{
		int counter = 0;
		if (x < vector_case.size() && y < vector_case[x].size() && x >= 0 && y >= 0)
		{
			counter = counter + vector_case[x][y].setStone(x, y, true);//Center
		}
		for (int i = 1; i < 6; i++)//HORIZONTAL case
		{
			if (x - i < vector_case.size() && y < vector_case[x - i].size() && x - i >= 0 && y >= 0)
			{
				counter = counter + vector_case[x - i][y].setStone(x, y, true);
			}
		}

		for (int i = 1; i < 6; i++)//VERTICAL case
		{
			if (x < vector_case.size() && y - i < vector_case[x].size() && x >= 0 && y - i >= 0)
			{
				counter = counter + vector_case[x][y - i].setStone(x, y, true);
			}
		}

		for (int i = 1; i < 6; i++)//DIAG_TOPLEFT case
		{
			if (x - i < vector_case.size() && y - i < vector_case[x - i].size() && x - i >= 0 && y - i >= 0)
			{
				counter = counter + vector_case[x - i][y - i].setStone(x, y, true);
			}
		}

		for (int i = 1; i < 6; i++)//DIAG_TOPRIGHT case
		{
			if (x + i < vector_case.size() && y - i < vector_case[x + i].size() && x + i >= 0 && y - i >= 0)
			{
				counter = counter + vector_case[x + i][y - i].setStone(x, y, true);
			}
		}
		return counter;
	}
	else
	{
		return 0;
	}
}

struct coordinate
{
	int x[2];
	int y[2];
};

struct caseLocation
{
	int startX;
	int startY;
	int direction;
	int real_direction;
};

bool isValidPutLocation(int x, int y)
{
	if (0 <= x && 0 <= y && x <= 18 && y <= 18)
	{
		if (MyBoard[x][y] == 0)
			return true;
		else
			return false;
	}
	else
		return false;
}

int getBestCase(vector<vector<CaseInfo>>& vector_case, vector<caseLocation>& vector_Maxweight/*return ����*/)
{
	int max_weight = vector_case[0][0].getCaseID(0).getPriority();
	for (int i = 0; i < vector_case.size(); i++)
	{
		for (int j = 0; j < vector_case[i].size(); j++)
		{
			for (int k = 0; k < vector_case[i][j].getDirectioncount(); k++)
			{
				if (vector_case[i][j].getCaseID(k).getCase_dominant() != RANDOM)
				{
					if (max_weight == vector_case[i][j].getCaseID(k).getPriority())
					{
						caseLocation temp;
						temp.startX = i;
						temp.startY = j;
						temp.direction = k;
						temp.real_direction = vector_case[i][j].getCaseID(k).getDirection();
						vector_Maxweight.push_back(temp);
					}
					else if (max_weight < vector_case[i][j].getCaseID(k).getPriority())
					{
						vector_Maxweight.clear();
						caseLocation temp;
						max_weight = vector_case[i][j].getCaseID(k).getPriority();
						temp.startX = i;
						temp.startY = j;
						temp.direction = k;
						temp.real_direction = vector_case[i][j].getCaseID(k).getDirection();
						vector_Maxweight.push_back(temp);

					}
				}
			}
		}
	}
	return max_weight;
}

coordinate put_next_stones(vector<vector<CaseInfo>>& vector_case, bool isFirst, int mystone)//������ ��ġ�� �����ִ� �Լ�
{
	coordinate ret;
	if (isFirst)//�浹�� �����Ͽ� ù���� 1���� ���� ���
	{
		vector<int*> Random_loc;
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				if (showMyBoard(i, j) == RANDOM)
				{
					int* temp = new int[2];
					temp[0] = i;
					temp[1] = j;
					Random_loc.push_back(temp);
				}
			}
		}//block�� ã��
		if (Random_loc.size() == 0)
		{
			coordinate ret;
			ret.x[0] = 9;
			ret.y[0] = 9;
			return ret;
		}
		else
		{
			srand(time(NULL));

			//srand(seed);
			int direction = rand() % 8;//�ݽð�������� 
			int* std_Random = Random_loc[rand() % Random_loc.size()];
			for (int i = direction; i < direction + 8; i++)
			{
				if (i % 8 == 0)
				{
					if (isValidPutLocation(std_Random[0] + 1, std_Random[1]))
					{
						ret.x[0] = std_Random[0] + 1;
						ret.y[0] = std_Random[1];
						break;
					}
				}
				else if (i % 8 == 1)
				{

					if (isValidPutLocation(std_Random[0] + 1, std_Random[1] + 1))
					{
						ret.x[0] = std_Random[0] + 1;
						ret.y[0] = std_Random[1] + 1;
						break;
					}
				}
				else if (i % 8 == 2)
				{

					if (isValidPutLocation(std_Random[0], std_Random[1] + 1))
					{
						ret.x[0] = std_Random[0];
						ret.y[0] = std_Random[1] + 1;
						break;
					}
				}
				else if (i % 8 == 3)
				{
					if (isValidPutLocation(std_Random[0] - 1, std_Random[1] + 1))
					{
						ret.x[0] = std_Random[0] - 1;
						ret.y[0] = std_Random[1] + 1;
						break;
					}
				}
				else if (i % 8 == 4)
				{

					if (isValidPutLocation(std_Random[0] - 1, std_Random[1]))
					{
						ret.x[0] = std_Random[0] - 1;
						ret.y[0] = std_Random[1];
						break;
					}
				}
				else if (i % 8 == 5)
				{
					if (isValidPutLocation(std_Random[0] - 1, std_Random[1] - 1))
					{
						ret.x[0] = std_Random[0] - 1;
						ret.y[0] = std_Random[1] - 1;
						break;
					}
				}
				else if (i % 8 == 6)
				{

					if (isValidPutLocation(std_Random[0], std_Random[1] - 1))
					{
						ret.x[0] = std_Random[0];
						ret.y[0] = std_Random[1] - 1;
						break;
					}
				}
				else if (i % 8 == 7)
				{

					if (isValidPutLocation(std_Random[0] + 1, std_Random[1] - 1))
					{
						ret.x[0] = std_Random[0] + 1;
						ret.y[0] = std_Random[1] - 1;
						break;
					}
				}
			}
			return ret;
		}
	}
	else//2���� �������� ���ϴ� ���
	{
		
		vector<caseLocation> vector_Maxweight;
		vector<int> myDominant;
		vector<int> cpDominant;
		int max_weight = getBestCase(vector_case, vector_Maxweight);
		for (int i = 0; i < vector_Maxweight.size(); i++)
		{
			int dominant = vector_case[vector_Maxweight[i].startX][vector_Maxweight[i].startY].getCaseID(vector_Maxweight[i].direction).getCase_dominant();
			if (dominant == mystone)
				myDominant.push_back(i);
			else if (dominant != EMPTY && dominant != RANDOM && dominant != mystone)
				cpDominant.push_back(i);
		}

		vector<coord> candidate_point;
		//���� �ĺ��� ���ϱ�
		int isChecked[19][19] = { 0 };
		for (int i = 0; i < vector_Maxweight.size(); i++)
		{
			for (int j = 0; j < 6; j++)
			{
				coord temp = vector_case[vector_Maxweight[i].startX][vector_Maxweight[i].startY].getCaseID(vector_Maxweight[i].direction).changeToCoordinate(j);
				if (showMyBoard(temp.x, temp.y) == EMPTY && isChecked[temp.x][temp.y] == EMPTY)
				{
					candidate_point.push_back(temp);
					isChecked[temp.x][temp.y] = -1;
				}

			}
		}

		//���� �����غ���
		vector<coordinate> candidate_return;
		int changed_Max = -1;
		int changed_Min = 999999;
		int max_case_change = -1;




		if (max_weight == 4)//���赵�� 4�� ��� �� ����Ǽ��� �� 2�� ����
		{
			for (int i = 0; i < candidate_point.size(); i++)
			{
				for (int j = i + 1; j < candidate_point.size(); j++)
				{
					int test_x[2], test_y[2];
					test_x[0] = candidate_point[i].x;
					test_x[1] = candidate_point[j].x;
					test_y[0] = candidate_point[i].y;
					test_y[1] = candidate_point[j].y;

					setStoneOnEachCase(vector_case, test_x[0], test_y[0], mystone);
					setStoneOnEachCase(vector_case, test_x[1], test_y[1], mystone);

					vector<caseLocation> changed_Maxweight;
					int temp_Max = getBestCase(vector_case, changed_Maxweight);

					if (myDominant.size() > 0)
					{
						if (changed_Max < temp_Max)
						{
							changed_Max = temp_Max;
							candidate_return.clear();
							coordinate temp;
							temp.x[0] = candidate_point[i].x;
							temp.y[0] = candidate_point[i].y;
							temp.x[1] = candidate_point[j].x;
							temp.y[1] = candidate_point[j].y;
							candidate_return.push_back(temp);
						}
						else if (changed_Max == temp_Max)
						{
							coordinate temp;
							temp.x[0] = candidate_point[i].x;
							temp.y[0] = candidate_point[i].y;
							temp.x[1] = candidate_point[j].x;
							temp.y[1] = candidate_point[j].y;
							candidate_return.push_back(temp);
						}
					}
					else
					{
						if (changed_Min > temp_Max)
						{
							changed_Min = temp_Max;
							candidate_return.clear();
							coordinate temp;
							temp.x[0] = candidate_point[i].x;
							temp.y[0] = candidate_point[i].y;
							temp.x[1] = candidate_point[j].x;
							temp.y[1] = candidate_point[j].y;
							candidate_return.push_back(temp);
						}
						else if (changed_Min == temp_Max)
						{
							coordinate temp;
							temp.x[0] = candidate_point[i].x;
							temp.y[0] = candidate_point[i].y;
							temp.x[1] = candidate_point[j].x;
							temp.y[1] = candidate_point[j].y;
							candidate_return.push_back(temp);
						}
					}

					deleteStoneOnEachCase(vector_case, test_x[0], test_y[0]);
					deleteStoneOnEachCase(vector_case, test_x[1], test_y[1]);
				}
			}
		}

		else if (max_weight >= 5)
		{
			coordinate return_coord;
		
			if (candidate_point.size() != 0)
			{
				return_coord.x[0] = candidate_point[0].x;
				return_coord.y[0] = candidate_point[0].y;

				setStoneOnEachCase(vector_case, return_coord.x[0], return_coord.y[0], mystone);


				vector<caseLocation> changed_Maxweight;
				int temp_max = getBestCase(vector_case, changed_Maxweight);
				candidate_point.clear();
				for (int i = 0; i < 19; i++)
				{
					for (int j = 0; j < 19; j++)
						isChecked[i][j] = 0;
				}
				for (int i = 0; i < changed_Maxweight.size(); i++)
				{
					for (int j = 0; j < 6; j++)
					{
						coord temp = vector_case[changed_Maxweight[i].startX][changed_Maxweight[i].startY].getCaseID(changed_Maxweight[i].direction).changeToCoordinate(j);
						if (showMyBoard(temp.x, temp.y) == EMPTY && isChecked[temp.x][temp.y] == EMPTY)
						{
							candidate_point.push_back(temp);
							isChecked[temp.x][temp.y] = -1;
						}
					}
				}


				if (temp_max >= 4)
				{
					candidate_point.clear();
					for (int i = 0; i < changed_Maxweight.size(); i++)
					{
						for (int j = 0; j < 6; j++)
						{
							coord temp = vector_case[changed_Maxweight[i].startX][changed_Maxweight[i].startY].getCaseID(changed_Maxweight[i].direction).changeToCoordinate(j);
							if (showMyBoard(temp.x, temp.y) == EMPTY && isChecked[temp.x][temp.y] == EMPTY)
							{
								candidate_point.push_back(temp);
								isChecked[temp.x][temp.y] = -1;
							}
						}
					}
					return_coord.x[1] = candidate_point[0].x;
					return_coord.y[1] = candidate_point[0].y;

					deleteStoneOnEachCase(vector_case, return_coord.x[0], return_coord.y[0]);
					deleteStoneOnEachCase(vector_case, return_coord.x[1], return_coord.y[1]);

					return return_coord;
				}
				else
				{
					for (int i = 0; i < candidate_point.size(); i++)
					{
						int case_change_counter = 0;
						max_case_change = -1;
						int test_x = candidate_point[i].x, test_y = candidate_point[i].y;
						case_change_counter += setStoneOnEachCase2(vector_case, test_x, test_y, mystone);
						if (max_case_change < case_change_counter)
						{
							max_case_change = case_change_counter;
							candidate_return.clear();
							coordinate temp;
							temp.x[0] = return_coord.x[0];
							temp.y[0] = return_coord.y[0];
							temp.x[1] = test_x;
							temp.y[1] = test_y;
							candidate_return.push_back(temp);
						}
						else if (max_case_change == case_change_counter)
						{
							coordinate temp;
							temp.x[0] = return_coord.x[0];
							temp.y[0] = return_coord.y[0];
							temp.x[1] = test_x;
							temp.y[1] = test_y;
							candidate_return.push_back(temp);
						}
						deleteStoneOnEachCase(vector_case, test_x, test_y);
					}
					deleteStoneOnEachCase(vector_case, return_coord.x[0], return_coord.y[0]);
				}
			}
		}
		else if (max_weight < 4)//���赵��  4 �̸��� ��� ���� ���� �ٸ� ����Ǽ��� ������
		{

			for (int i = 0; i < candidate_point.size(); i++)
			{
				for (int j = i + 1; j < candidate_point.size(); j++)
				{
					int case_change_counter = 0;
					int test_x[2], test_y[2];
					test_x[0] = candidate_point[i].x;
					test_x[1] = candidate_point[j].x;
					test_y[0] = candidate_point[i].y;
					test_y[1] = candidate_point[j].y;
					case_change_counter += setStoneOnEachCase2(vector_case, test_x[0], test_y[0], mystone);
					case_change_counter += setStoneOnEachCase2(vector_case, test_x[1], test_y[1], mystone);

					if (max_case_change < case_change_counter)
					{
						max_case_change = case_change_counter;
						candidate_return.clear();
						coordinate temp;
						temp.x[0] = candidate_point[i].x;
						temp.y[0] = candidate_point[i].y;
						temp.x[1] = candidate_point[j].x;
						temp.y[1] = candidate_point[j].y;
						candidate_return.push_back(temp);
					}
					else if (max_case_change == case_change_counter)
					{
						coordinate temp;
						temp.x[0] = candidate_point[i].x;
						temp.y[0] = candidate_point[i].y;
						temp.x[1] = candidate_point[j].x;
						temp.y[1] = candidate_point[j].y;
						candidate_return.push_back(temp);
					}


					deleteStoneOnEachCase(vector_case, test_x[0], test_y[0]);
					deleteStoneOnEachCase(vector_case, test_x[1], test_y[1]);
				}
			}
		}
		if (candidate_return.size() == 0)
		{
			coordinate ret;
			for (int i = rand()%19; i < i + 19; i++)
			{
				for (int j = rand() % 19; j < j + 19; j++)
				{
					if (showMyBoard(i, j) == EMPTY)
					{
						MyBoard[i][j] = mystone;
						ret.x[0] = i;
						ret.y[0] = j;
					}
				}
			}
			for (int i = rand() % 19; i < i + 19; i++)
			{
				for (int j = rand() % 19; j < j + 19; j++)
				{
					if (showMyBoard(i, j) == EMPTY)
					{
						MyBoard[i][j] = mystone;
						ret.x[1] = i;
						ret.y[1] = j;
					}
				}
			}
			return ret;
		}

		else
			return candidate_return[rand() % candidate_return.size()];

	}
}





// "�����ڵ�[C]"  -> �ڽ��� ���� (����)
// "AI�μ�[C]"  -> �ڽ��� �Ҽ� (����)
// ����� ���������� �ݵ�� �������� ����!
char info[] = { "TeamName: ������_test,Department:���ϴ��б� ������Ű��а�" };

//My Variables and Functions.
char*buf = new char[1024];//Log��¿� ����
void myLog(char*, char*, ...);//Log�� ������ִ� �Լ�
void myLinkinfo();

bool isBlockLoaded = false;
bool isCaseLoaded = false;
vector<vector<CaseInfo>> vector_case;
void myturn(int cnt) {
	int x[2], y[2];
	int horizontal_loc = 0;
	int vertical_loc = 0;

	// �� �κп��� �˰��� ���α׷�(AI)�� �ۼ��Ͻʽÿ�. �⺻ ������ �ڵ带 ���� �Ǵ� �����ϰ� ������ �ڵ带 ����Ͻø� �˴ϴ�.
	// ���� Sample code�� AI�� Random���� ���� ���� Algorithm�� �ۼ��Ǿ� �ֽ��ϴ�.



	if (!isCaseLoaded)
	{
		int directioncount = 0;
		for (int x = 0; x < 19; x++)
		{
			vector<CaseInfo> hor_line;
			vector_case.push_back(hor_line);
			for (int y = 0; y < 19; y++)
			{
				CaseInfo temp(x, y);
				if (temp.getDirectioncount() != 0)
				{
					vector_case[x].push_back(temp);
				}
				directioncount += temp.getDirectioncount();
			}
		}
	}
	if (!isBlockLoaded)
	{
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				if (showMyBoard(i, j) == RANDOM)
					setRANDOMOnEachCase(vector_case, i, j);
			}
		}
	}
	//������ �ε� �Ϸ�

	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (showBoard(i, j) != showMyBoard(i, j))
			{
				int board_info = showBoard(i, j);
				MyBoard[i][j] = board_info;
				if (board_info == WHITE)
				{
					setStoneOnEachCase(vector_case, i, j, WHITE);
				}
			}
		}
	}
	//���� ������� �ε�Ϸ�


	if (cnt == 1)
	{
		coordinate output = put_next_stones(vector_case, true, BLACK);
		x[0] = output.x[0];
		y[0] = output.y[0];
		setStoneOnEachCase(vector_case, x[0], y[0], BLACK);
	}
	else
	{
		//myLog("���� ����?", "%s", (cnt == 2 ? "����" : "����"));
		coordinate output = put_next_stones(vector_case, false, BLACK);
		x[0] = output.x[0];
		y[0] = output.y[0];
		x[1] = output.x[1];
		y[1] = output.y[1];
		setStoneOnEachCase(vector_case, x[0], y[0], BLACK);
		setStoneOnEachCase(vector_case, x[1], y[1], BLACK);
	}
	//myLog("---- ���� ���� ��ġ :", "x1=%d y1=%d    x2=%d y2=%d", x[0], y[0], x[1], y[1]);
	domymove(x, y, cnt);

	//Implementation End

	// �� �κп��� �ڽ��� ���� ���� ����Ͻʽÿ�.
	// �ʼ� �Լ� : domymove(x�迭,y�迭,�迭ũ��)
	// ���⼭ �迭ũ��(cnt)�� myturn()�� �Ķ���� cnt�� �״�� �־���մϴ�.
	//domymove(x, y, cnt);
}

void myLog(const char* tag, const char* content, ...)
{
	va_list ap;

	sprintf(buf, "TAG = %s : ", tag);
	va_start(ap, content);
	vsprintf(buf + strlen(buf), content, ap);
	va_end(ap);
	sprintf(buf + strlen(buf), "\n");
	writeLog(buf);
}

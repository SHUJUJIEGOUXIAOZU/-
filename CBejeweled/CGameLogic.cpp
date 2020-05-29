#include "pch.h"
#include "CGameLogic.h"
#include<ctime>
#include<cstdlib>
#include <iostream>

PICELEM CGameLogic::GetPicElem(int nRow, int nCol)
{
	PICELEM picElem;
	picElem.nRow = nRow;
	picElem.nCol = nCol;
	return picElem;
}
void CGameLogic::GetPicElem()
{
	for (int i = 0; i < GAME_ROW; i++)
	{
		for (int j = 0; j < GAME_COL; j++)
		{
			m_aMap[i][j] = rand() % ELEM_NUM;
			m_aRemove[i * GAME_COL - 1 + j].nPicNum = m_aMap[i][j];
		}
	}
}
void CGameLogic::CGamelogic()
{
	for (int i = 0; i < GAME_ROW; i++)
	{
		for (int j = 0; j < GAME_COL; j++)
		{
			m_aMap[i][j] = 0;
		}
	}

	srand((unsigned)time(NULL));//设置随机数种子
	memset(m_aRemove, NULL, sizeof(PICELEM) * GAME_ROW * GAME_COL);//为棋盘的每个节点分配空间
	m_nRemoveNum = 0;
	m_nTotalScore = 0;
}

int CGameLogic::GetPicNum(int nRow, int nCol)
{
	return m_aMap[nRow][nCol];
}

//创造地图
void CGameLogic::BuildMap()
{
	while (!IsChange())
	{
		aa++;
		GetPicElem();
	}

	/*for (int i = 0; i < GAME_ROW; i++)
	{
		for (int j = 0; j < GAME_COL; j++)
		{
			std::cout << m_aMap[i][j] << " ";
		}
		std::cout << "\n ";
	}*/

}

//判断地图中是否存在三联,是返回false，不是返回true
bool  CGameLogic::IsChange()
{
	if (ChangeRow() && ChangeCol())
		return true;
	else
		return false;
}

//横向判断,不存在返回true
bool CGameLogic::ChangeRow()
{
	for (int i = 0; i < GAME_ROW; i++)
	{
		row = 0;
		for (int j = 0; j < GAME_COL; j++)
		{
			if (j + 1 < GAME_COL && m_aMap[i][j] == m_aMap[i][j + 1]) row++;
			else  row = 0;

			if (row >= 2)
				return false;
		}
	}

	return true;
}

//纵向判断
bool CGameLogic::ChangeCol()
{
	for (int j = 0; j < GAME_COL; j++)
	{
		col = 0;
		for (int i = 0; i < GAME_ROW; i++)
		{
			if (i + 1 < GAME_COL && m_aMap[i][j] == m_aMap[i + 1][j]) col++;
			else  col = 0;

			if (col >= 2)
				return false;
		}
	}

	return true;
}
int CGameLogic::GetRemoveNum()
{
	return m_nRemoveNum;
}
PICELEM CGameLogic::GetRemoveElem(int nIndex)
{
	return m_aRemove[nIndex];
}
//交换棋子，接受的是两个棋子的位置------(x,y)(m,n)
void CGameLogic::ExChange(int x, int y, int m, int n)
{
	int ntem = m_aMap[x][y];
	//将结构体的更换
	m_aRemove[x * GAME_COL + y].nPicNum = m_aRemove[m * GAME_COL + n].nPicNum;
	m_aRemove[m * GAME_COL + n].nPicNum = ntem;
	//将数组的更换
	m_aMap[x][y] = m_aMap[m][n];
	m_aMap[m][n] = ntem;
}
//	//消子
//消子 主函数
void CGameLogic::Action(int a, int b, int p, int q)
{
	if (IsNeighbour(a, b, p, q))//选择的是不是两个相邻的格子
	{
		ExChange(a, b, p, q);//，是两个相邻的，进行更换 更换要链接动画
		if (ActionBefore(a, b, p, q))//是否构成三联
		{
			while (ActionDo())//是，消子
				ReFlash();
		}
		else
			ExChange(a, b, p, q);//不构成三联，换回去
	}
	else//不是相邻的，不交换
	{
		//要错误的反馈
	}
}

//判断是否相邻，接受的是两个棋子的位置------(x,y)(m,n)
BOOL CGameLogic::IsNeighbour(int x, int y, int m, int n)
{
	//行相等时
	if (x == m && abs(y - n) == 1)
		return TRUE;
	//列相等
	if (y == n && abs(x - m) == 1)
		return TRUE;

	return FALSE;
}

//寻找一个点周围是否组成三联，如果是找到另一端---
//直接使用了BOOL CGameLogic::ChangeCol()和BOOL CGameLogic::ChangeROW（）两个函数，之所以重写是不必全部引用，可能可以节省一点空间，希望后期得到算法改进
BOOL CGameLogic::FindCheck(int x, int y)
{
	int is = 0;//判断是否有

	//横向
	row = 0;
	for (int j = 0; j < GAME_COL; j++)
	{
		if (j + 1 < GAME_COL && m_aMap[x][j] == m_aMap[x][j + 1])	row++;
		else  row = 0;

		if (row >= 2)
			is = 1;
	}

	//纵向
	col = 0;
	for (int i = 0; i < GAME_ROW; i++)
	{
		if (i + 1 < GAME_COL && m_aMap[i][y] == m_aMap[i + 1][y])	col++;
		else  col = 0;

		if (col >= 2)
			is = 1;
	}


	if (is == 1)
		return TRUE;
	else
		return FALSE;
}


bool CGameLogic::Tip() {//提示
	PICELEM picElem1;
	PICELEM picElem2;
	for (int j = 0; j < GAME_COL; j++)
	{
		for (int i = 0; i < GAME_ROW; i++)
		{
			picElem1 = GetPicElem(i, j);
			picElem2 = GetPicElem(i, j + 1);
			if (ActionBefore(i,j,i,j+1))
			{
				m_aTip[0] = picElem1;
				m_aTip[1] = picElem2;
				return true;
			}
		}
	}
	for (int y = 0; y < GAME_COL - 1; y++)
	{
		for (int x = 0; x < GAME_ROW - 1; x++)
		{
			picElem1 = GetPicElem(x, y);
			picElem2 = GetPicElem(x + 1, y);
			if (ActionBefore(x, y, x+1,y))
			{
				m_aTip[0] = picElem1;
				m_aTip[1] = picElem2;
				return true;
			}
		}
	}
	return false;
}
//消子检查，接受的是两个棋子的位置------(x,y)(m,n)，返回true即为交换后有可消项
BOOL CGameLogic::ActionBefore(int x, int y, int m, int n)
{
	if (FindCheck(x, y) || FindCheck(m, n))
		return TRUE;
	else  return FALSE;
}

//消子操作，//有消子操作，返回真
BOOL CGameLogic::ActionDo()
{
	int sym = 0, x0 = 0, y0 = 0, x1 = -1, y1 = -1;
	row = 0, col = 0;

	//横向
	for (int i = 0; i < GAME_COL; i++)
	{
		row = 0;
		for (int j = 0; j < GAME_ROW - 1; j++)
		{
			if (j + 1 < GAME_COL && m_aMap[i][j] == m_aMap[i][j + 1])	row++;
			else   y0 = j + 1;

			if (row >= 2)
			{
				y1 = j + 1;
				sym = 1;
				for (int k = y0; k <= y1; k++)//添加消失动画
					m_aMap[i][k] = -1;
			}
		}
	}

	//纵向
	for (int j = 0; j < GAME_COL; j++)
	{
		col = 0;
		for (int i = 0; i < GAME_ROW - 1; i++)
		{
			if (i + 1 < GAME_COL && m_aMap[i][j] == m_aMap[i + 1][j])	col++;
			else  x0 = i + 1;

			if (col >= 2)
			{
				x1 = i + 1;
				sym = 1;
				for (int k = x0; k <= x1; k++)//添加消失动画
					m_aMap[k][j] = -1;
			}
		}
	}

	if (sym == 1)//有消子操作，返回真
	{
		sym = 0;
		return TRUE;
	}
	else
		return FALSE;
}

//更新操作
void CGameLogic::ReFlash()
{
	int xPosition = -1, yPosition = -1;//记录两个位置

		//办法----纵向逆(即从下到上)检索
	for (int j = 0; j < GAME_COL; j++)
	{
		col = 0; xPosition = -1, yPosition = -1;
		for (int i = GAME_ROW - 1; i >= 0; i--)
		{
			if (m_aMap[i][j] == -1)
			{
				if (xPosition == -1)
				{
					xPosition = i;
					yPosition = i;
				}
				else    yPosition = i;
			}
		}

		for (int i = yPosition - 1; i >= 0; i--)//下移
		{
			m_aMap[xPosition][j] = m_aMap[i][j];
			xPosition--;
		}
		for (int i = xPosition; i >= 0; i--)//填充
		{
			m_aMap[i][j] = rand() % ELEM_NUM;
			m_aRemove[i * GAME_COL + j].nPicNum = m_aMap[i][j];
		}
	}
}

//检查是否存在二联，并记录位置
void CGameLogic::Remove()
{
	//横向
	for (int i = 0; i < GAME_COL; i++)
	{
		for (int j = 0; j < GAME_ROW - 1; j++)
		{
			if (m_aMap[i][j] == m_aMap[i][j + 1])
			{

			}

		}
	}
	//纵向
	for (int j = 0; j < GAME_COL; j++)
	{
		for (int i = 0; i < GAME_ROW - 1; i++)
		{

		}
	}
}
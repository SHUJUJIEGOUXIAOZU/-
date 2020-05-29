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

	srand((unsigned)time(NULL));//�������������
	memset(m_aRemove, NULL, sizeof(PICELEM) * GAME_ROW * GAME_COL);//Ϊ���̵�ÿ���ڵ����ռ�
	m_nRemoveNum = 0;
	m_nTotalScore = 0;
}

int CGameLogic::GetPicNum(int nRow, int nCol)
{
	return m_aMap[nRow][nCol];
}

//�����ͼ
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

//�жϵ�ͼ���Ƿ��������,�Ƿ���false�����Ƿ���true
bool  CGameLogic::IsChange()
{
	if (ChangeRow() && ChangeCol())
		return true;
	else
		return false;
}

//�����ж�,�����ڷ���true
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

//�����ж�
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
//�������ӣ����ܵ����������ӵ�λ��------(x,y)(m,n)
void CGameLogic::ExChange(int x, int y, int m, int n)
{
	int ntem = m_aMap[x][y];
	//���ṹ��ĸ���
	m_aRemove[x * GAME_COL + y].nPicNum = m_aRemove[m * GAME_COL + n].nPicNum;
	m_aRemove[m * GAME_COL + n].nPicNum = ntem;
	//������ĸ���
	m_aMap[x][y] = m_aMap[m][n];
	m_aMap[m][n] = ntem;
}
//	//����
//���� ������
void CGameLogic::Action(int a, int b, int p, int q)
{
	if (IsNeighbour(a, b, p, q))//ѡ����ǲ����������ڵĸ���
	{
		ExChange(a, b, p, q);//�����������ڵģ����и��� ����Ҫ���Ӷ���
		if (ActionBefore(a, b, p, q))//�Ƿ񹹳�����
		{
			while (ActionDo())//�ǣ�����
				ReFlash();
		}
		else
			ExChange(a, b, p, q);//����������������ȥ
	}
	else//�������ڵģ�������
	{
		//Ҫ����ķ���
	}
}

//�ж��Ƿ����ڣ����ܵ����������ӵ�λ��------(x,y)(m,n)
BOOL CGameLogic::IsNeighbour(int x, int y, int m, int n)
{
	//�����ʱ
	if (x == m && abs(y - n) == 1)
		return TRUE;
	//�����
	if (y == n && abs(x - m) == 1)
		return TRUE;

	return FALSE;
}

//Ѱ��һ������Χ�Ƿ����������������ҵ���һ��---
//ֱ��ʹ����BOOL CGameLogic::ChangeCol()��BOOL CGameLogic::ChangeROW��������������֮������д�ǲ���ȫ�����ã����ܿ��Խ�ʡһ��ռ䣬ϣ�����ڵõ��㷨�Ľ�
BOOL CGameLogic::FindCheck(int x, int y)
{
	int is = 0;//�ж��Ƿ���

	//����
	row = 0;
	for (int j = 0; j < GAME_COL; j++)
	{
		if (j + 1 < GAME_COL && m_aMap[x][j] == m_aMap[x][j + 1])	row++;
		else  row = 0;

		if (row >= 2)
			is = 1;
	}

	//����
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


bool CGameLogic::Tip() {//��ʾ
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
//���Ӽ�飬���ܵ����������ӵ�λ��------(x,y)(m,n)������true��Ϊ�������п�����
BOOL CGameLogic::ActionBefore(int x, int y, int m, int n)
{
	if (FindCheck(x, y) || FindCheck(m, n))
		return TRUE;
	else  return FALSE;
}

//���Ӳ�����//�����Ӳ�����������
BOOL CGameLogic::ActionDo()
{
	int sym = 0, x0 = 0, y0 = 0, x1 = -1, y1 = -1;
	row = 0, col = 0;

	//����
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
				for (int k = y0; k <= y1; k++)//�����ʧ����
					m_aMap[i][k] = -1;
			}
		}
	}

	//����
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
				for (int k = x0; k <= x1; k++)//�����ʧ����
					m_aMap[k][j] = -1;
			}
		}
	}

	if (sym == 1)//�����Ӳ�����������
	{
		sym = 0;
		return TRUE;
	}
	else
		return FALSE;
}

//���²���
void CGameLogic::ReFlash()
{
	int xPosition = -1, yPosition = -1;//��¼����λ��

		//�취----������(�����µ���)����
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

		for (int i = yPosition - 1; i >= 0; i--)//����
		{
			m_aMap[xPosition][j] = m_aMap[i][j];
			xPosition--;
		}
		for (int i = xPosition; i >= 0; i--)//���
		{
			m_aMap[i][j] = rand() % ELEM_NUM;
			m_aRemove[i * GAME_COL + j].nPicNum = m_aMap[i][j];
		}
	}
}

//����Ƿ���ڶ���������¼λ��
void CGameLogic::Remove()
{
	//����
	for (int i = 0; i < GAME_COL; i++)
	{
		for (int j = 0; j < GAME_ROW - 1; j++)
		{
			if (m_aMap[i][j] == m_aMap[i][j + 1])
			{

			}

		}
	}
	//����
	for (int j = 0; j < GAME_COL; j++)
	{
		for (int i = 0; i < GAME_ROW - 1; i++)
		{

		}
	}
}
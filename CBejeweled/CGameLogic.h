#pragma once
#define GAME_ROW 8 //游戏行数
#define GAME_COL 8 //游戏列数
#define ELEM_NUM 4 //花色数量
typedef struct PICTIREELEMENT
{
	int nRow;//行号
	int nCol;//列号
	int nPicNum;//图片编号
}PICELEM;
class CGameLogic
{

public:
	void CGamelogic();
	//	//创造地图
	void BuildMap();//创造地图主函数
	void GetPicElem();//初始化地图
	bool IsChange();
	bool ChangeRow();
	bool ChangeCol();

	//	//消子
	void Action(int a, int b, int p, int q);//消子 主函数
	BOOL IsNeighbour(int x, int y, int m, int n);//是否相邻
	void ExChange(int x, int y, int m, int n);//交换棋子
	BOOL ActionBefore(int x, int y, int m, int n);//消子检查
	BOOL FindCheck(int x, int y);//寻找一个点周围是否组成三联
	BOOL ActionDo();//执行消子
	void ReFlash();
	bool Tip();
	//更新
	PICELEM GetRemoveElem(int nIndex);
	int GetRemoveNum();
	PICELEM GetPicElem(int nRow, int nCol);
	int GetPicNum(int nRow, int nCol);
	int m_aMap[GAME_ROW][GAME_COL];//游戏地图数组
	PICELEM m_aRemove[GAME_ROW * GAME_COL];
	PICELEM m_aTip[2];
	int m_nRemoveNum;
	int aa = 0;
	//	//检查是否存在能够消除的格子
	void Remove();

protected:
	int col = 0, row = 0;
	int m_nTotalScore;//总分

};


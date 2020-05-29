#pragma once
#define GAME_ROW 8 //��Ϸ����
#define GAME_COL 8 //��Ϸ����
#define ELEM_NUM 4 //��ɫ����
typedef struct PICTIREELEMENT
{
	int nRow;//�к�
	int nCol;//�к�
	int nPicNum;//ͼƬ���
}PICELEM;
class CGameLogic
{

public:
	void CGamelogic();
	//	//�����ͼ
	void BuildMap();//�����ͼ������
	void GetPicElem();//��ʼ����ͼ
	bool IsChange();
	bool ChangeRow();
	bool ChangeCol();

	//	//����
	void Action(int a, int b, int p, int q);//���� ������
	BOOL IsNeighbour(int x, int y, int m, int n);//�Ƿ�����
	void ExChange(int x, int y, int m, int n);//��������
	BOOL ActionBefore(int x, int y, int m, int n);//���Ӽ��
	BOOL FindCheck(int x, int y);//Ѱ��һ������Χ�Ƿ��������
	BOOL ActionDo();//ִ������
	void ReFlash();
	bool Tip();
	//����
	PICELEM GetRemoveElem(int nIndex);
	int GetRemoveNum();
	PICELEM GetPicElem(int nRow, int nCol);
	int GetPicNum(int nRow, int nCol);
	int m_aMap[GAME_ROW][GAME_COL];//��Ϸ��ͼ����
	PICELEM m_aRemove[GAME_ROW * GAME_COL];
	PICELEM m_aTip[2];
	int m_nRemoveNum;
	int aa = 0;
	//	//����Ƿ�����ܹ������ĸ���
	void Remove();

protected:
	int col = 0, row = 0;
	int m_nTotalScore;//�ܷ�

};


#ifndef __PC_AI_H__
#define __PC_AI_H__
#include "manager\GameManager.h"
#include "cocos2d.h"
USING_NS_CC;

class PcAi
{
public:
	PcAi();
	~PcAi();
	static int startAi(int opponentType);
	static int getDirection() {return _direction;};
	static int getNextDirectionIndex(int index, int dir, int num);
	static int clearOrFindChessIndex(int index, bool isFind = false);//��������ظ���λ��
	static void initChessIndex();
	static void reset();
private:
	static std::vector<int> leftAi(int index);//����߲鿴
	static std::vector<int> rightAi(int index);//���ұ߲鿴
	static std::vector<int> topAi(int index);//���ϲ鿴
	static std::vector<int> bottomAi(int index);//���²鿴
	static int changeDirection(const int dir,int index);//�������Լ��������
	static bool isChangeDirection(const int dir, int index);//�������Լ��������
	static std::vector<int> ai(int index,int key, int dir);
	static bool inDepth(int index, int chessmanType, const int dir);
	static int _direction;
	static std::vector<Node*> _allChessman;
	static std::vector<int> _chessIndexs;
};


#endif
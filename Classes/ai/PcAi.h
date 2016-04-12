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
	static int getNextIndex() {return _nextIndex;};
	static void initChessIndex();
private:
	static std::vector<int> leftAi(int index);//����߲鿴
	static std::vector<int> rightAi(int index);//���ұ߲鿴
	static std::vector<int> topAi(int index);//���ϲ鿴
	static std::vector<int> bottomAi(int index);//���²鿴
	static std::vector<int> ai(int index,int key,int dir);
	static int clearOrFindChessIndex(int index,bool isFind = false);//��������ظ���λ��
	static int getNextDirectionIndex(int index, int dir,int num);
	static int _nextIndex;
	static std::vector<int> _chessIndexs;
};


#endif
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
	static std::vector<int> leftAi(int index);//往左边查看
	static std::vector<int> rightAi(int index);//往右边查看
	static std::vector<int> topAi(int index);//往上查看
	static std::vector<int> bottomAi(int index);//往下查看
	static std::vector<int> ai(int index,int key,int dir);
	static int clearOrFindChessIndex(int index,bool isFind = false);//避免出现重复的位置
	static int getNextDirectionIndex(int index, int dir,int num);
	static int _nextIndex;
	static std::vector<int> _chessIndexs;
};


#endif
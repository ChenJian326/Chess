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
	static int clearOrFindChessIndex(int index, bool isFind = false);//避免出现重复的位置
	static void initChessIndex();
	static void reset();
private:
	static std::vector<int> leftAi(int index);//往左边查看
	static std::vector<int> rightAi(int index);//往右边查看
	static std::vector<int> topAi(int index);//往上查看
	static std::vector<int> bottomAi(int index);//往下查看
	static int changeDirection(const int dir,int index);//遇到比自己大的逃跑
	static bool isChangeDirection(const int dir, int index);//遇到比自己大的逃跑
	static std::vector<int> ai(int index,int key, int dir);
	static bool inDepth(int index, int chessmanType, const int dir);
	static int _direction;
	static std::vector<Node*> _allChessman;
	static std::vector<int> _chessIndexs;
};


#endif
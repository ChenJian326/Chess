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
private:
	static int leftAi(int index);
	static int rightAi(int index);
	static int topAi(int index);
	static int bottomAi(int index);
	static int _nextIndex;
};


#endif
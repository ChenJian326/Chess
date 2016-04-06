#ifndef __CHESSMAN_NODE_H__
#define __CHESSMAN_NODE_H__
#include "cocos2d.h"


USING_NS_CC;

class ChessmanNode :public Node
{
public:
	ChessmanNode();
	~ChessmanNode();
	static ChessmanNode* createChessman(const std::string &name);
	void setChessType(int value1, int value2);

	int getOpponentType() const { return _opponentType; };
	int getChessmanType() const { return _chessmanType; };
	void countdown(float dt);//pc走完以后启动一个倒计时
	void clearChessman();
	CREATE_FUNC(ChessmanNode);
private:
	bool virtual init();
	void MoveOrSelect(bool isPc);
	int _opponentType;
	int _chessmanType;//-1表示被吃掉了
	int colorID;
	int labelID;
	bool isOpen;
	int _countdown;
	Color4B cc4Pl = Color4B(30, 144, 255, 255);
	Color3B cc3Pl = Color3B(0, 0, 0);
	Color4B	cc4Pc = Color4B(144, 238, 144, 255);
	Color3B cc3Pc = Color3B(255, 10, 0);

};

#endif // !__CHESSMAN_NODE_H__


#ifndef __CHESSMAN_NODE_H__
#define __CHESSMAN_NODE_H__
#include "cocos2d.h"
#include "config\Config.h"
#include "manager\TouchManager.h"
#include "manager\GameManager.h"

USING_NS_CC;

class ChessmanNode :public Node
{
public:
	ChessmanNode();
	~ChessmanNode();
	static ChessmanNode* createChessman(const std::string &name);
	//opponent chessman  index
	void setChessType(int value1, int value2, int index);
	void countdown(float dt);//pc走完以后启动一个倒计时
	void clearChessman(int index = -1);
	void MoveOrSelect(bool isPc);

	int getOpponentType() const { return _opponentType; };
	int getChessmanType() const { return _chessmanType; };
	int getIndex() { return _index; }
	bool isOpen() { return _isOpen; }
	bool isEat();
	CREATE_FUNC(ChessmanNode);
private:
	bool virtual init();
	int _opponentType;
	int _chessmanType;//-1表示被吃掉了
	int colorID;
	int labelID;
	bool _isOpen;
	int _countdown;
	int _index;
	void setChessStatus();
	//选中了闪
	void setSelectStatus(bool isSelect);
	GameManager* _gameManager;
	Color4B cc4Pl = Color4B(30, 144, 255, 255);
	Color3B cc3Pl = Color3B(0, 0, 0);
	Color4B	cc4Pc = Color4B(144, 238, 144, 255);
	Color3B cc3Pc = Color3B(255, 10, 0);

};

#endif // !__CHESSMAN_NODE_H__


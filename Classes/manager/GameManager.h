#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__
#include "cocos2d.h"
USING_NS_CC;

class GameManager
{
public:
	GameManager();
	~GameManager();
	static GameManager* GetIns();
	void setCurrentOpponent(int value);
	void setCurrentSelectChessman(int chessmanType);
	void setCurrentMoveChessman(int chessmanType);
	void startTime();
	void moveChessman(int opponentType);
	bool isEatOrMove(int opponentType);
	int getCurrentOpponent() { return _currentOpponent; };
	int getCurrentSelectChessman() { return _currentSelectChessman; };
	int getCurrentMoveChessman() { return _currentMoveChessman; };
private:
	int _currentOpponent;
	int _currentMoveChessman;
	int _currentSelectChessman;
	Director *_director;
};
#endif
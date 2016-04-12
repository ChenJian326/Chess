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
	//用来初始化游戏的一些东西
	void starGame(int opponentType);
	void endGame(int opponentType);
	void setCurrentOpponent(int value);
	void setCurrentSelectChessman(int chessmanType);
	void setCurrentMoveChessman(int chessmanType);
	void startTime();
	void moveChessman(int opponentType);
	bool isEatOrMove(int opponentType);
	void pushChessman(Node* node);
	void pushMoveChessmens(Node* node);
	int getCurrentOpponent() { return _currentOpponent; };
	int getCurrentSelectChessman() { return _currentSelectChessman; };
	int getCurrentMoveChessman() { return _currentMoveChessman; };
	int getSelectChessOpponent();

	std::vector<Node*> getChessmans(int opponentType);
	std::vector<Node*> getAllChessmans() { return _allChessmans; };
private:
	int _currentOpponent;
	int _currentMoveChessman;
	int _currentSelectChessman;
	std::vector<Node*> _pcChessmans;
	std::vector<Node*> _playerChessmans;
	std::vector<Node*> _allChessmans;
	std::vector<Node*> _moveChessmens;
	Director *_director;
};
#endif
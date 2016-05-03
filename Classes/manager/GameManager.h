#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__
#include "cocos2d.h"
#include "config\Config.h"
USING_NS_CC;

class GameManager
{
public:
	GameManager();
	~GameManager();
	static GameManager* GetIns();
	//用来初始化游戏的一些东西
	void starGame(int opponentType);
	void endGame(int opponentType = -1);
	void checkIsEndGame(int opponentType);
	void setCurrentOpponent(int value);
	void setCurrentSelectChessman(int chessmanType);
	void setCurrentMoveChessman(int chessmanType);
	void moveChessman(int opponentType);
	void pushChessman(Node* node);
	void pushMoveChessmens(Node* node);
	bool isEatOrMove(int opponentType, int index);
	void cancelSelectChess();
	int removeOrFindChess(int index, bool isRemove = false, int opponentType = Config::pc);
	int getCurrentOpponent() { return _currentOpponent; };
	int getCurrentSelectChessman() { return _currentSelectChessman; };
	int getCurrentMoveChessman() { return _currentMoveChessman; };
	int getSelectChessType(int type);
	int getSelectChessIndex();
	int getWinType() { return _winType; };
	std::vector<Node*> getChessmans(int opponentType);
	std::vector<Node*> getAllChessmans() { return _allChessmans; };
private:
	int _currentOpponent;
	int _currentMoveChessman;
	int _currentSelectChessman;
	int _winType;
	std::vector<Node*> _pcChessmans;
	std::vector<Node*> _playerChessmans;
	std::vector<Node*> _allChessmans;
	std::vector<Node*> _moveChessmens;
	Director *_director;
	bool isConnect(int index);
};
#endif
#include "GameMap.h"
#include "config\Config.h"
#include "config\VisibleRect.h"
#include "ChessmanNode.h"
#include "manager\GameManager.h"

GameMap::GameMap()
	:nodeId(10)
{
	chessmans = {
		Config::handsome ,Config::handsome ,
		Config::finishing ,Config::finishing ,Config::finishing ,Config::finishing ,
		Config::phase ,Config::phase ,Config::phase ,Config::phase ,
		Config::horse,Config::horse,Config::horse,Config::horse,
		Config::car,Config::car,Config::car,Config::car,
		Config::cannon,Config::cannon,Config::cannon,Config::cannon,
		Config::soldiers,Config::soldiers,Config::soldiers,Config::soldiers,Config::soldiers,Config::soldiers,Config::soldiers,Config::soldiers,Config::soldiers,Config::soldiers
	};
	opponets = {
		Config::player ,Config::player ,Config::player ,Config::player ,Config::player ,Config::player ,Config::player ,Config::player ,
		Config::player ,Config::player ,Config::player ,Config::player ,Config::player ,Config::player ,Config::player ,Config::player,
		Config::pc,Config::pc,Config::pc,Config::pc,Config::pc,Config::pc,Config::pc,Config::pc,Config::pc,Config::pc,Config::pc,Config::pc,Config::pc,Config::pc,Config::pc,Config::pc
	};
}

GameMap::~GameMap()
{
}

bool GameMap::init()
{
	if (!Node::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto lineNode = Node::create();
	lineNode->setContentSize(CCSize(Config::MAP_SIZE::w, Config::MAP_SIZE::h));
	lineNode->setAnchorPoint(Vec2(0.5, 0.5));
	lineNode->setPosition(VisibleRect::center());
	this->addChild(lineNode, 0, nodeId);
	int space = Config::CHESS_SIZE::width;
	int i, j;
	for (i = 0; i < Config::MAP_SIZE::row + 1; i++)
	{
		auto line = DrawNode::create();
		line->setLineWidth(5);
		line->drawLine(Vec2(0, i * space), Vec2(Config::MAP_SIZE::w, i * space), Color4F(0.5, 0.5, 0.2, 1));
		lineNode->addChild(line);
	}
	for (j = 0; j < Config::MAP_SIZE::column + 1; j++)
	{
		auto line = DrawNode::create();
		line->setLineWidth(5);
		line->drawLine(Vec2(j * space, 0), Vec2(j * space, Config::MAP_SIZE::h), Color4F(0.5, 0.5, 0.2, 1));
		lineNode->addChild(line);
	}
	this->initChess();
	return true;
}

void GameMap::initChess()
{
	int i, j, index = 0,type1,type2;
	auto manager = GameManager::GetIns();
	int space = Config::CHESS_SIZE::width;
	auto node = this->getChildByTag(nodeId);
	std::vector<int>::iterator it1 ;
	std::vector<int>::iterator it2 ;
	for (i = 0; i < Config::MAP_SIZE::row; i++)
	{
		for (j = 0; j < Config::MAP_SIZE::column; j++)
		{
			index++;
			std::string str = StringUtils::toString(index);
			auto chessman = ChessmanNode::createChessman(str);
			type1 =random(0, (int)opponets.size() - 1);
			type2 = random(0, (int)chessmans.size() - 1);
			chessman->setChessType(opponets.at(type1), chessmans.at(type2), index);
			it1 = opponets.begin() + type1;
			it2 = chessmans.begin() + type2;
			opponets.erase(it1);
			chessmans.erase(it2);
			chessman->setPosition(Vec2(j * space, i * space));
			node->addChild(chessman);
			manager->pushChessman(chessman);
		}
	}
	//默认为玩家先下
	manager->starGame(Config::player);
}

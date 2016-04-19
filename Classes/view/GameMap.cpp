#include "GameMap.h"
#include "config\Config.h"
#include "config\VisibleRect.h"
#include "ChessmanNode.h"
#include "manager\GameManager.h"

GameMap::GameMap()
	:nodeId(10)
{
	_chessmans = {};
	std::function<void(int, int)> func = [=](int num, int chess) {
		int k = num * 0.5;
		int type = Config::pc;
		for (int i = 0; i < num; i++)
		{
			if (i >= k)
			{
				type = Config::player;
			}
			_chessmans.push_back({ type ,chess });
		}
	};
	func(2, Config::handsome);
	func(4, Config::finishing);
	func(4, Config::phase);
	func(4, Config::horse);
	func(4, Config::car);
	func(4, Config::cannon);
	func(10, Config::soldiers);
	//随机打乱顺序
	std::random_shuffle(_chessmans.begin(), _chessmans.end() ,[=](int vec) {
		return random(0,10) % vec;
	});
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
	int i, j, index = 0,randIndex;
	std::vector<int> randVec;
	auto manager = GameManager::GetIns();
	int space = Config::CHESS_SIZE::width;
	auto node = this->getChildByTag(nodeId);
	for (i = 0; i < Config::MAP_SIZE::row; i++)
	{
		for (j = 0; j < Config::MAP_SIZE::column; j++)
		{
			index++;
			std::string str = StringUtils::toString(index);
			auto chessman = ChessmanNode::createChessman(str);
			randIndex = random(0, (int)_chessmans.size() - 1);
			randVec = _chessmans.at(randIndex);
			chessman->setChessType(randVec.at(0), randVec.at(1), index - 1);
			chessman->setPosition(Vec2(j * space, i * space));
			node->addChild(chessman);
			manager->pushChessman(chessman);
			_chessmans.erase(_chessmans.begin() + randIndex);
		}
	}
	//默认为玩家先下
	manager->starGame(Config::player);
}

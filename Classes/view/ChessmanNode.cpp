#include "ChessmanNode.h"
#include "config\Config.h"
#include "manager\TouchManager.h"
#include "manager\GameManager.h"

ChessmanNode::ChessmanNode()
	:_opponentType(0),
	_chessmanType(0),
	colorID(1),
	labelID(2),
	isOpen(false),
	_countdown(0)
{
}

ChessmanNode::~ChessmanNode()
{
}

ChessmanNode * ChessmanNode::createChessman(const std::string &name)
{
	ChessmanNode *chessman = ChessmanNode::create();
	chessman->setName(name);
	return chessman;
}

void ChessmanNode::setChessType(int value1, int value2)
{
	_opponentType = value1;
	_chessmanType = value2;
	auto color = dynamic_cast<LayerColor*>(this->getChildByTag(colorID));
	auto label = dynamic_cast<Label*>(this->getChildByTag(labelID));
	if (_opponentType == Config::OPPONENT::pc)
	{
		//需要设置宽高，不能回以屏幕大小为准，即时初始化的时候设置也无效
		color->initWithColor(cc4Pc, Config::CHESS_SIZE::width - 5, Config::CHESS_SIZE::height - 5);
		label->setColor(cc3Pc);
	}
	else
	{
		color->initWithColor(cc4Pl, Config::CHESS_SIZE::width - 5, Config::CHESS_SIZE::height - 5);
		label->setColor(cc3Pl);
	}
	label->setString(Config::GetChessmanName(_chessmanType, _opponentType));
	TouchManager::getIns()->addTouchNode(this, [=]() {
		if (GameManager::GetIns()->getCurrentOpponent() == Config::player) {
			this->MoveOrSelect(false);
		}
	});
	CCLOG("_opponentType = %d _chessmanType = %d", _opponentType, _chessmanType);
}

//棋子被吃了
void ChessmanNode::clearChessman()
{
	this->removeChildByTag(colorID);
	this->removeChildByTag(labelID);
	_chessmanType = Config::nullChessman;
}

bool ChessmanNode::init()
{
	if (!Node::init()) {
		return false;
	}
	auto colorLayer = LayerColor::create();
	colorLayer->setPosition(Vec2(2.5, 2.5));
	this->addChild(colorLayer, 0, colorID);

	auto label = Label::createWithSystemFont(Config::GetChessmanName(_chessmanType, _opponentType), "微软雅黑", 24);
	label->setColor(cc3Pl);
	label->setPosition(Vec2(Config::CHESS_SIZE::width * .5, Config::CHESS_SIZE::height * .5));
	label->setVisible(false);
	this->addChild(label, 0, labelID);
	this->setContentSize(Size(Config::CHESS_SIZE::width, Config::CHESS_SIZE::height));
	return true;
}

void ChessmanNode::MoveOrSelect(bool isPc)
{
	CCLOG("touch end name = %s  %d", Config::GetChessmanName(_chessmanType, _opponentType), _chessmanType);
	if (isOpen)
	{
		if (_chessmanType != Config::nullChessman && GameManager::GetIns()->getCurrentMoveChessman() == Config::nullChessman)
		{
			GameManager::GetIns()->setCurrentMoveChessman(_chessmanType);
		}
		else if (_chessmanType != Config::nullChessman && GameManager::GetIns()->getCurrentSelectChessman() == Config::nullChessman)
		{
			GameManager::GetIns()->setCurrentSelectChessman(_chessmanType);
			bool isEat = GameManager::GetIns()->isEatOrMove(_opponentType);
			if (isEat)
			{
				GameManager::GetIns()->moveChessman(_opponentType);
			}
		}
	}
	else
	{
		this->getChildByTag(labelID)->setVisible(true);
	}
	GameManager::GetIns()->setCurrentOpponent(isPc ? Config::player : Config::pc);
	isOpen = true;
	if (!isPc) {
		/*_countdown = 10;
		this->schedule(CC_SCHEDULE_SELECTOR(ChessmanNode::countdown), 1);*/
	}
}

void ChessmanNode::countdown(float dt)
{
	/*_countdown--;
	if (_countdown <= 0)
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(ChessmanNode::countdown));
	}*/
	CCLOG("_countdown = %d", _countdown);
}
#include "ChessmanNode.h"
#include "tips\TipsManager.h"
#include "ui\UIRichText.h"
ChessmanNode::ChessmanNode()
	:_opponentType(0),
	_chessmanType(0),
	colorID(1),
	labelID(2),
	_isOpen(false),
	_countdown(0),
	_gameManager(GameManager::GetIns())
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

void ChessmanNode::setChessType(int value1, int value2, int index)
{
	_opponentType = value1;
	_chessmanType = value2;
	_index = --index;
	auto label = dynamic_cast<Label*>(this->getChildByTag(labelID));
	this->setChessStatus();
	label->setString(Config::GetChessmanName(_chessmanType, _opponentType));
	TouchManager::getIns()->addTouchNode(this, [=]() {
		if (_gameManager->getCurrentOpponent() == Config::player) {
			this->MoveOrSelect(false);
		}
	});
	label->setVisible(_isOpen);
}

//棋子被吃了
void ChessmanNode::clearChessman(int index)
{
	this->getChildByTag(labelID)->setVisible(false);
	_chessmanType = Config::nullChessman;
	_opponentType = Config::nullChessman;
	if (index >= 0)
	{
		_index = index;
	}
	this->setChessStatus();
}

bool ChessmanNode::isEat()
{
	return _chessmanType == Config::nullChessman;
}

bool ChessmanNode::init()
{
	if (!Node::init()) {
		return false;
	}
	auto colorLayer = LayerColor::create(Color4B::BLUE, Config::CHESS_SIZE::width - 5, Config::CHESS_SIZE::height - 5);
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

void ChessmanNode::setChessStatus()
{
	auto color = dynamic_cast<LayerColor*>(this->getChildByTag(colorID));
	auto label = dynamic_cast<Label*>(this->getChildByTag(labelID));
	if (_isOpen)
	{
		if (_chessmanType != Config::nullChessman) {
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
		}
		else {
			color->initWithColor(Color4B::WHITE, Config::CHESS_SIZE::width - 5, Config::CHESS_SIZE::height - 5);
		}
	}
	else
	{
		color->initWithColor(Color4B::BLUE, Config::CHESS_SIZE::width - 5, Config::CHESS_SIZE::height - 5);
	}
	auto rich = ui::RichText::create();
	rich->ignoreContentAdaptWithSize(false);
}

void ChessmanNode::MoveOrSelect(bool isPc)
{
	if (_isOpen)
	{
		int currentMoveChessman = _gameManager->getCurrentMoveChessman();
		int currentSelectChessman = _gameManager->getCurrentSelectChessman();
		int selectChessOpponent = _gameManager->getSelectChessOpponent();
		if (_chessmanType != Config::nullChessman && currentMoveChessman == Config::nullChessman)
		{
			_gameManager->setCurrentMoveChessman(_chessmanType);
			_gameManager->pushMoveChessmens(this);
			this->setSelectStatus(true);
			CCLOG("[MoveOrSelect] push one chessman");
		}
		else if (_opponentType == selectChessOpponent)
		{
			_gameManager->setCurrentMoveChessman(Config::nullChessman);
			TipsManager::showTips("取消了您本次操作，请重新操作");
			CCLOG("[MoveOrSelect] touch");
		}
		else if (currentSelectChessman == Config::nullChessman && currentMoveChessman != Config::nullChessman)
		{
			_gameManager->setCurrentSelectChessman(_chessmanType);
			bool isEat = _gameManager->isEatOrMove(_opponentType);
			CCLOG("[MoveOrSelect] isEat yes or no");
			if (isEat)
			{
				_gameManager->pushMoveChessmens(this);
				_gameManager->moveChessman(_opponentType);
				this->setSelectStatus(false);
				CCLOG("[MoveOrSelect] isEat yes");
			}
		}
	}
	else
	{
		this->getChildByTag(labelID)->setVisible(true);
		_gameManager->setCurrentOpponent(isPc ? Config::player : Config::pc);
	}
	_isOpen = true;
	this->setChessStatus();
}

void ChessmanNode::setSelectStatus(bool isSelect)
{
	if (isSelect)
	{
		this->runAction(RepeatForever::create(Sequence::create(FadeOut::create(1),FadeIn::create(1),nullptr)));
	}
	else
	{
		this->stopAllActions();
		this->setOpacity(255);
	}
}


void ChessmanNode::countdown(float dt)
{

}
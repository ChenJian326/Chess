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

ChessmanNode * ChessmanNode::createChessman()
{
	ChessmanNode *chessman = ChessmanNode::create();
	return chessman;
}

void ChessmanNode::setChessType(int value1, int value2, int index)
{
	_opponentType = value1;
	_chessmanType = value2;
	_index = index;
	auto label = dynamic_cast<Label*>(this->getChildByTag(labelID));
	this->setChessStatus();
	label->setString(Config::GetChessmanName(_chessmanType, _opponentType));
	label->setVisible(_isOpen);
	this->setSelectStatus(false);
}

//棋子被吃了
void ChessmanNode::clearChessman(int index)
{
	_chessmanType = Config::nullChessman;
	_opponentType = Config::nullChessman;
	_index = index;
	this->getChildByTag(labelID)->setVisible(false);
	this->setChessStatus();
	this->setSelectStatus(false);
	//	CCLOG("_chessmanType = %d _opponentType = %d index = %d", _chessmanType, _opponentType, _index);
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
	this->addChild(label, 0, labelID);
	this->setContentSize(Size(Config::CHESS_SIZE::width, Config::CHESS_SIZE::height));
	this->setCascadeOpacityEnabled(true);
	//this->setOnEnterCallback();
	return true;
}

void ChessmanNode::onEnter()
{
	Node::onEnter();
}

void ChessmanNode::onEnterTransitionDidFinish()
{
	Node::onEnterTransitionDidFinish();
	TouchManager::getIns()->addTouchNode(this, [=]() {
		if (_gameManager->getCurrentOpponent() == Config::player) {
			this->MoveOrSelect(false);
		}
	});
	CCLOG("%s", Config::GBKToUTF8(this->getName().c_str()));
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
}

void ChessmanNode::MoveOrSelect(bool isPc)
{
	if (_isOpen)
	{
		int currentSelectChessman = _gameManager->getCurrentSelectChessman();
		int currentMoveChessman = _gameManager->getSelectChessType(Config::TYPE_CHESS);
		int selectChessOpponent = _gameManager->getSelectChessType(Config::TYPE_OPPONENT);
		if (!isPc && currentMoveChessman == Config::nullChessman && _opponentType == Config::pc)
		{
			return;
		}
		if (currentMoveChessman == Config::nullChessman && _chessmanType != Config::nullChessman)
		{
			_gameManager->setCurrentMoveChessman(_chessmanType);
			_gameManager->pushMoveChessmens(this);
			this->setSelectStatus(true);
			CCLOG("[MoveOrSelect 1]  _index = %d  _chessmanType = %d", _index, _chessmanType);
		}
		else if (currentSelectChessman == Config::nullChessman && currentMoveChessman != Config::nullChessman)
		{
			if (_gameManager->isConnect(_index))
			{
				_gameManager->setCurrentSelectChessman(_chessmanType);
				bool isEat = _gameManager->isEatOrMove(_opponentType);
				//		CCLOG("[MoveOrSelect 2]  _index = %d _chessmanType = %d", _index, _chessmanType);
				if (isEat)
				{
					_gameManager->pushMoveChessmens(this);
					_gameManager->moveChessman(selectChessOpponent);
				}
				else {
					//不能吃，不能走，重置这次的选择
					_gameManager->setCurrentSelectChessman(Config::nullChessman);
				}
			}
		}
		else
		{
			TipsManager::showRedTips("选择的棋子无效");
			CCLOG("currentSelectChessman = %d _index = %d currentMoveChessman = %d", currentSelectChessman, _index, currentMoveChessman);
		}
	}
	else
	{
		_isOpen = true;
		this->getChildByTag(labelID)->setVisible(true);
		if (_opponentType == Config::pc)
		{
			_gameManager->removeOrFindChess(_index, false, Config::pc);
		}
		_gameManager->cancelSelectChess();
		_gameManager->setCurrentOpponent(isPc ? Config::player : Config::pc);
	}
	this->setChessStatus();
}

void ChessmanNode::setSelectStatus(bool isSelect)
{
	if (isSelect)
	{
		this->runAction(RepeatForever::create(Sequence::create(FadeOut::create(0.4), FadeIn::create(0.4), nullptr)));
	}
	else
	{
		this->stopAllActions();
		this->setOpacity(255);
	}
}
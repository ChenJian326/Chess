#include "ChessmanNode.h"
#include "tips\TipsManager.h"

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
	if (index > 0)
		_index = index - 1;
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
		if (_gameManager->getCurrentOpponent() == Config::player) {
			this->MoveOrSelect(false);
		}
	});
	label->setVisible(_isOpen);
	color->setVisible(true);
}

//棋子被吃了
void ChessmanNode::clearChessman()
{
	this->getChildByTag(colorID)->setVisible(false);
	this->getChildByTag(labelID)->setVisible(false);
	_chessmanType = Config::nullChessman;
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
	if (_isOpen)
	{
		if (_chessmanType != Config::nullChessman && _gameManager->getCurrentMoveChessman() == Config::nullChessman)
		{
			_gameManager->setCurrentMoveChessman(_chessmanType);
			_gameManager->pushMoveChessmens(this);
		}
		else if (_chessmanType != Config::nullChessman && _chessmanType == _gameManager->getCurrentMoveChessman())
		{
			_gameManager->setCurrentMoveChessman(Config::nullChessman);
			TipsManager::showTips("取消了您本次操作，请重新操作");
		}
		else if (_gameManager->getCurrentSelectChessman() == Config::nullChessman)
		{
			_gameManager->setCurrentSelectChessman(_chessmanType);
			bool isEat = _gameManager->isEatOrMove(_opponentType);
			if (isEat)
			{
				_gameManager->pushMoveChessmens(this);
				_gameManager->moveChessman(_opponentType);
			}
			_gameManager->setCurrentOpponent(isPc ? Config::player : Config::pc);
		}
	}
	else
	{
		this->getChildByTag(labelID)->setVisible(true);
		_gameManager->setCurrentOpponent(isPc ? Config::player : Config::pc);
	}
	_isOpen = true;
}

void ChessmanNode::countdown(float dt)
{

}
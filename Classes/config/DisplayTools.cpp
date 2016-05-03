#include "DisplayTools.h"
#include "config\Config.h"
DisplayTools::DisplayTools()
{
}

DisplayTools::~DisplayTools()
{
}

Label * DisplayTools::createLabel(const char * str, int fontSize, Vec2 pos, Vec2 apos, Color3B color, TextVAlignment va, TextHAlignment ha)
{
	auto label = Label::createWithSystemFont(str, GAME_FONE_NAME,fontSize,Size::ZERO);
	label->setColor(color);
	label->setPosition(pos);
	label->setAnchorPoint(apos);
	label->setVerticalAlignment(va);
	label->setHorizontalAlignment(ha);
	return label;
}

Node * DisplayTools::createNode(Vec2 pos, Vec2 apos )
{
	auto node = Node::create();
	node->setPosition(pos);
	node->setAnchorPoint(apos);
	return node;
}

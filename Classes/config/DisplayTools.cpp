#include "DisplayTools.h"

DisplayTools::DisplayTools()
{
}

DisplayTools::~DisplayTools()
{
}

Label * DisplayTools::createLabel(const char * str, int fontSize, Vec2 pos, Vec2 apos, Color3B color)
{
	auto label = Label::createWithSystemFont(str,"Î¢ÈíÑÅºÚ",fontSize,Size::ZERO);
	label->setColor(color);
	label->setPosition(pos);
	label->setAnchorPoint(pos);
	label->setVerticalAlignment(TextVAlignment::CENTER);
	label->setHorizontalAlignment(TextHAlignment::CENTER);
	return label;
}

Node * DisplayTools::createNode()
{
	return nullptr;
}

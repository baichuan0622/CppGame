#include "Block.h"


__Array* Block::array = NULL;
Block* Block::Create(Size size, Color3B color, __String  str, float str_strSize, Color3B strColor)
{
	if(array == NULL) {
		array = __Array::create();
		array->retain();	
	}
	Block * pret = new Block();
	if (pret && pret->init(size, color, str, str_strSize, strColor))
	{
		pret->autorelease();
		array->addObject(pret);
	}
	else
	{
		delete pret;
		pret = NULL;
	}
	return pret;
}

bool Block::init(Size size, Color3B color, __String  str, float str_strSize, Color3B strColor)
{
	Sprite::init();
	setContentSize(size);
	setTextureRect(Rect(0, 0, size.width-1, size.height-1));
	this->setAnchorPoint(Vec2(0, 0));
	this->setColor(color);
	
	LabelTTF* label = LabelTTF::create();
	label->setString(str.getCString());
	label->setFontSize(str_strSize);
	label->setColor(strColor);
	label->setPosition(Vec2(size.width / 2, size.height / 2));
	this->addChild(label);


	return true;
}

void Block::MoveDownAndCleanUp()
{
	Size winsize = Director::getInstance()->getWinSize();
	_lineIndex--; //ÐÐÊý
	MoveTo *mt = MoveTo::create(0.01, Vec2(getPositionX(), getPositionY() - winsize.height / 4));
	this->runAction(mt);
	if (_lineIndex < 0) {
		array->removeObject(this);
		removeFromParentAndCleanup(true);
	}
}

Block::Block()
{
}


Block::~Block()
{
}

__Array * Block::getBlockArray()
{
	return array;
}

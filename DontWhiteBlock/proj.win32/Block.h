#ifndef _Block_H_
#endif	_Block_H_
#include<cocos2d.h>
USING_NS_CC;
class Block : public Sprite
{
public:
	static Block* Create(Size size,Color3B color,__String  str,float str_strSize,Color3B strColor);
	bool init(Size size, Color3B color, __String  str, float str_strSize, Color3B strColor);
	void MoveDownAndCleanUp();
	Block();
	~Block();
	static __Array *array;
	static __Array* getBlockArray();

	CC_SYNTHESIZE(int, _lineIndex, LineIndex);


};


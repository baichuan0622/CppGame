#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
private:
	cocos2d::Size winsize;
	bool showEnd;
	long starttimer;
	bool isRunning;
	LabelTTF * ttf;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();  
    CREATE_FUNC(HelloWorld);

	void StartGame();
	void AddStartLineGame();
	void addNormalLineBlock(int Linedex);
	void MoveDown();
	void addEndLine();
	void StartTimer();
	void StopTimer();
	void update(float);

	virtual bool onTouchBegan(Touch *touch, Event *unused_event) override;
	CC_SYNTHESIZE(int, _LineCount, LineCount);
	
};

#endif // __HELLOWORLD_SCENE_H__

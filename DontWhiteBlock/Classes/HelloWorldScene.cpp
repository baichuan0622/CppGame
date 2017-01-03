#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "proj.win32/Block.h"


USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	winsize = Director::getInstance()->getWinSize();
	showEnd = false;
	starttimer = 0;
	isRunning = false;	
	ttf = LabelTTF::create("0.0000000", "Courier", 40);
	ttf->setZOrder(100);
	//ttf->setAnchorPoint(Vec2(0,0));
	ttf->setPosition(Vec2(winsize.width / 2, winsize.height-20));
	ttf->setColor(Color3B::BLUE);
	addChild(ttf);
	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	StartGame();
	setLineCount(0);
    return true;
}




void HelloWorld::StartGame()
{
	AddStartLineGame();
	addNormalLineBlock(1);
	addNormalLineBlock(2);
	addNormalLineBlock(3);
}

void HelloWorld::AddStartLineGame()
{
	
	Size startBlockSize = Size(winsize.width, winsize.height / 4);
	Block* b = Block::Create(startBlockSize,Color3B(0,205,0),"Start Game",30,Color3B(255,255,255));
	b->setLineIndex(0);
	b->setPosition(Vec2(0, 0));
	_LineCount++;
	addChild(b);
		
}

void HelloWorld::addNormalLineBlock(int Linedex)
{
	Size normalBlockSize = Size(winsize.width / 4, winsize.height / 4);
	int idex = rand() % 4; //只随机一次
	for (int i = 0; i < 4; i++)
	{
		Block* b = Block::Create(normalBlockSize,i==idex? Color3B::BLACK:Color3B::WHITE,"",30,Color3B(0,0,0));
		b->setLineIndex(Linedex);
		b->setPosition(i*winsize.width / 4, Linedex*winsize.height / 4);
		addChild(b); 
	}
	_LineCount++;
}

void HelloWorld::addEndLine()
{
	Block* b = Block::Create(winsize,Color3B::GREEN,"Game Over",30,Color3B::BLACK);
	b->setAnchorPoint(Vec2(0, 0));
	b->setPosition(Vec2(0, winsize.height/4*3));
	addChild(b);
	b->setLineIndex(4);//?
	_LineCount++;//?

}

void HelloWorld::StartTimer()
{
	if (!isRunning)
	{
		scheduleUpdate();
		starttimer = clock();
		isRunning = false;
	}

	
}

void HelloWorld::StopTimer()
{
	if (isRunning)
	{
		unscheduleUpdate();
	}
}

void HelloWorld::update(float)
{
	long long offset = clock() - starttimer;
	__String *str = __String::createWithFormat("%g", (double)offset/100000);
	ttf->setString(str->getCString());

}

void HelloWorld::MoveDown()
{
	if (getLineCount()<20)
	{

		addNormalLineBlock(4);
			
	}
	else if (!showEnd)
	{
		addEndLine();
		showEnd = true;
	}		

	Ref* pref;
	CCARRAY_FOREACH_REVERSE(Block::getBlockArray(), pref) {
		Block* bl = (Block*)pref;
		bl->MoveDownAndCleanUp();
	}
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
	Ref* obj;	
	CCARRAY_FOREACH_REVERSE(Block::getBlockArray(), obj) {
		Block* b = (Block*)obj;
		if (b->boundingBox().containsPoint(touch->getLocation())&&b->getLineIndex()==1)
		{
			if (b->getColor() == Color3B::BLACK)
			{
				StartTimer();
				this->MoveDown();
			}
			else if (b->getColor() == Color3B::WHITE)
			{

			}
			else if (b->getColor()==Color3B::GREEN)
			{
				StartTimer();
				MoveDown();
			}

			break;
		}
		
	
	}
	return true;
}


#ifndef __FSM_SCENE_H__
#define __FSM_SCENE_H__

#include "cocos2d.h"
#include "AINodeManager.h"
#include "ORCA/RVOSimulator.h"
#include "ORCA/Vector2.h"
USING_NS_CC;
using namespace std;
using namespace RVO;
class AIScene : public Scene
{
public:
	static Scene* createScene();

    virtual bool init();

    virtual bool onTouchBegan(Touch* touch, Event* unused_event);

    // implement the "static create()" method manually
    CREATE_FUNC(AIScene);

    void update(float dt);

    void createFSMNode();

    RVOSimulator* getRVOSim() { return m_sim; }

protected:
    EventListenerTouchOneByOne* _touchListener;
    Vec2 _touchBeganPosition;
    DrawNode* _mapDrawNode;

    AINodeManager* _aiNodeManager;

    vector<AINode*> _aiNodes;

    RVO::RVOSimulator* m_sim;

    int _aiNodeIdx = 0;
};

#endif
#ifndef __FSM_SCENE_H__
#define __FSM_SCENE_H__

#include "cocos2d.h"
#include "AINodeManager.h"
#include "ORCA/RVOSimulator.h"
#include "ORCA/Vector2.h"
#include "AILogNode.h"
#include "GOAPTest/GOAPTestNode.h"
USING_NS_CC;
using namespace std;
using namespace RVO;

class AIScene : public Scene
{
public:
	static Scene* createScene();

    virtual ~AIScene();
    virtual bool init();

    virtual bool onTouchBegan(Touch* touch, Event* unused_event);

    // implement the "static create()" method manually
    CREATE_FUNC(AIScene);

    void update(float dt);

    void createFSMNode();
    void createHFSMNode();
    void createBTTreeNode();
    void createAILogNode();
    void createGOAPTestNode();
    void createHTNNode();
    void createGOAPNode();

    RVOSimulator* getRVOSim() { return m_sim; }

protected:
    EventListenerTouchOneByOne* _touchListener;
    Vec2 _touchBeganPosition;
    DrawNode* _mapDrawNode;

    AINodeManager* _aiNodeManager;

    unordered_map<int, AIAttackNode*> _aiNodes;
    AILogNode* _aiLogNode;
    GOAPTestNode* _goapTestNode;

    RVO::RVOSimulator* m_sim;

    int _aiNodeIdx = 0;
};

#endif
#include "AIScene.h"

Scene* AIScene::createScene()
{
    return AIScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in AIScene.cpp\n");
}

// on "init" you need to initialize your instance
bool AIScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto layer = LayerColor::create(Color4B(255, 255, 255, 255));
    layer:setContentSize(visibleSize);
    this->addChild(layer);

    _mapDrawNode = DrawNode::create();
    this->addChild(_mapDrawNode);

    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->setSwallowTouches(true);
    _touchListener->onTouchBegan = CC_CALLBACK_2(AIScene::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, layer);

    this->scheduleUpdate();

    m_sim = new RVO::RVOSimulator();
    m_sim->setAgentDefaults(50.0f, 2, 1.0f, 5.0f, 10.0f, 1);

    /*vector<Vector2> vert1;
    vert1.push_back(RVO::Vector2(10.0f, 10.0f));
    vert1.push_back(RVO::Vector2(10.0f, 630.0f));
    vert1.push_back(RVO::Vector2(-100.0f, 630.0f));
    vert1.push_back(RVO::Vector2(-100.0f, 10.0f));
    m_sim->addObstacle(vert1);
    vector<Vector2> vert2;
    vert2.push_back(RVO::Vector2(10.0f, 630.0f));
    vert2.push_back(RVO::Vector2(1390.0f, 630.0f));
    vert2.push_back(RVO::Vector2(1390.0f, 830.0f));
    vert2.push_back(RVO::Vector2(10.0f, 830.0f));
    m_sim->addObstacle(vert2);
    vector<Vector2> vert3;
    vert3.push_back(RVO::Vector2(1390.0f, 630.0f));
    vert3.push_back(RVO::Vector2(1390.0f, 10.0f));
    vert3.push_back(RVO::Vector2(1490.0f, 10.0f));
    vert3.push_back(RVO::Vector2(1490.0f, 630.0f));
    m_sim->addObstacle(vert3);
    vector<Vector2> vert4;
    vert4.push_back(RVO::Vector2(1390.0f, 10.0f));
    vert4.push_back(RVO::Vector2(10.0f, 10.0f));
    vert4.push_back(RVO::Vector2(10.0f, -100.0f));
    vert4.push_back(RVO::Vector2(1390.0f, -100.0f));
    m_sim->addObstacle(vert4);*/

    vector<RVO::Vector2> vertices;
    vertices.push_back(RVO::Vector2(650.0f, 200.0f));
    vertices.push_back(RVO::Vector2(750.0f, 200.0f));
    vertices.push_back(RVO::Vector2(750.0f, 400.0f));
    vertices.push_back(RVO::Vector2(650.0f, 400.0f));
    m_sim->addObstacle(vertices);
    auto obstacle = DrawNode::create();
    this->addChild(obstacle);
    for (int i = 0; i < vertices.size(); i++) {
        if (i == vertices.size() - 1) {
            obstacle->drawLine(Vec2(vertices[i].x(), vertices[i].y()), Vec2(vertices[0].x(), vertices[0].y()), Color4F(0, 0, 0, 1));
        }
        else {
            obstacle->drawLine(Vec2(vertices[i].x(), vertices[i].y()), Vec2(vertices[i + 1].x(), vertices[i + 1].y()), Color4F(0, 0, 0, 1));
        }
    }
    /*for (int i = 0; i < vert1.size(); i++) {
        if (i == vert1.size() - 1) {
            obstacle->drawLine(Vec2(vert1[i].x(), vert1[i].y()), Vec2(vert1[0].x(), vert1[0].y()), Color4F(0, 0, 0, 1));
        }
        else {
            obstacle->drawLine(Vec2(vert1[i].x(), vert1[i].y()), Vec2(vert1[i + 1].x(), vert1[i + 1].y()), Color4F(0, 0, 0, 1));
        }
    }
    for (int i = 0; i < vert2.size(); i++) {
        if (i == vert2.size() - 1) {
            obstacle->drawLine(Vec2(vert2[i].x(), vert2[i].y()), Vec2(vert2[0].x(), vert2[0].y()), Color4F(0, 0, 0, 1));
        }
        else {
            obstacle->drawLine(Vec2(vert2[i].x(), vert2[i].y()), Vec2(vert2[i + 1].x(), vert2[i + 1].y()), Color4F(0, 0, 0, 1));
        }
    }
    for (int i = 0; i < vert3.size(); i++) {
        if (i == vert3.size() - 1) {
            obstacle->drawLine(Vec2(vert3[i].x(), vert3[i].y()), Vec2(vert3[0].x(), vert3[0].y()), Color4F(0, 0, 0, 1));
        }
        else {
            obstacle->drawLine(Vec2(vert3[i].x(), vert3[i].y()), Vec2(vert3[i + 1].x(), vert3[i + 1].y()), Color4F(0, 0, 0, 1));
        }
    }
    for (int i = 0; i < vert4.size(); i++) {
        if (i == vert4.size() - 1) {
            obstacle->drawLine(Vec2(vert4[i].x(), vert4[i].y()), Vec2(vert4[0].x(), vert4[0].y()), Color4F(0, 0, 0, 1));
        }
        else {
            obstacle->drawLine(Vec2(vert4[i].x(), vert4[i].y()), Vec2(vert4[i + 1].x(), vert4[i + 1].y()), Color4F(0, 0, 0, 1));
        }
    }*/

    m_sim->processObstacles(); 

    return true;
}

bool AIScene::onTouchBegan(Touch* touch, Event* event)
{
    _touchBeganPosition = touch->getLocation();
    createFSMNode();

    auto node = FSMNode::create();
    auto body = DrawNode::create();
    node->_renderNode->addChild(body, -1);
    body->drawDot(Vec2(0, 0), node->getRidius(), Color4F(0, 1, 0, 0.5));
    node->setPosition(_touchBeganPosition+Vec2(300,100));
    node->setId(_aiNodeIdx);
    this->addChild(node);
    _aiNodes.push_back(node);

    int idx = m_sim->addAgent(Vector2(_touchBeganPosition.x+300, _touchBeganPosition.y+100));
    m_sim->setAgentType(idx, 1);
    m_sim->setAgentAINode(idx, node);

    _aiNodeIdx++;

    return true;
}

void AIScene::update(float dt) {
    m_sim->setTimeStep(dt);
    for (auto aiNode: _aiNodes) {
        int idx = aiNode->getId();
        Vec2 velocity = aiNode->getVelocity();
        m_sim->setAgentMaxSpeed(idx, 1/dt);
        m_sim->setAgentPrefVelocity(idx, Vector2(velocity.x * 1 / dt, velocity.y * 1 / dt));
    }

    m_sim->doStep();

    for (auto aiNode : _aiNodes) {
        int idx = aiNode->getId();
        Vector2 velocity = m_sim->getAgentVelocity(idx);
        Vector2 v = m_sim->getAgentPosition(idx);
        aiNode->updatePos(Vec2(velocity.x() * dt, velocity.y() * dt));
        aiNode->setPosition(Vec2(v.x(), v.y()));

        int enemyIdx = m_sim->getNearestEnemy(idx, aiNode->getPursuitRidius());
        if (enemyIdx >= 0) {
            aiNode->setNearestEnemy(_aiNodes[enemyIdx]);
        }
        else {
            aiNode->setNearestEnemy(nullptr);
        }
    }
}

void AIScene::createFSMNode() {
    auto node = _aiNodeManager->getFSMNode();
    node->setPosition(_touchBeganPosition);
    node->setId(_aiNodeIdx);
    this->addChild(node);
    _aiNodes.push_back(node);

    int idx = m_sim->addAgent(Vector2(_touchBeganPosition.x, _touchBeganPosition.y));
    m_sim->setAgentAINode(idx, node);
    m_sim->setAgentType(idx, int(AINodeType::FSMNode));

    _aiNodeIdx++;
}
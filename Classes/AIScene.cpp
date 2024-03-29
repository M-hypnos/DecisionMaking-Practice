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

AIScene::~AIScene() {
    delete m_sim;
    m_sim = nullptr;
    delete _aiNodeManager;
    _aiNodeManager = nullptr;
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
    this->addChild(layer, -1);

    _mapDrawNode = DrawNode::create();
    this->addChild(_mapDrawNode);

    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->setSwallowTouches(true);
    _touchListener->onTouchBegan = CC_CALLBACK_2(AIScene::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, layer);

    this->scheduleUpdate();

    _aiNodeManager = new AINodeManager();
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
    createAILogNode();
    createGOAPTestNode();

    return true;
}

bool AIScene::onTouchBegan(Touch* touch, Event* event)
{
    _touchBeganPosition = touch->getLocation();
    createFSMNode();
    createFSMNode();
    createHFSMNode();
    createHFSMNode();
    createHFSMNode();
    createBTTreeNode();
    createBTTreeNode();
    createHTNNode();
    createHTNNode();
    createGOAPNode();
    createGOAPNode();

    //_goapTestNode->createGoap();
    //_aiLogNode->startTree();

    /*auto node = GOAPNode::create();
    auto body = DrawNode::create();
    node->_renderNode->addChild(body, -1);
    body->drawDot(Vec2(0, 0), node->getRidius(), Color4F(1, 0, 1, 0.5));
    float x = RandomHelper::random_real<float>(1200, 1400);
    float y = RandomHelper::random_real<float>(400, 600);
    Vec2 v(x, y);
    node->setPosition(v);
    node->setId(_aiNodeIdx);
    this->addChild(node);
    int idx = m_sim->addAgent(Vector2(v.x, v.y));
    m_sim->setAgentAINode(idx, node);
    m_sim->setAgentType(idx, 0);
    _aiNodes.emplace(_aiNodeIdx++, node);*/

    return true;
}

void AIScene::update(float dt) {
    m_sim->setTimeStep(dt);
    auto iter = _aiNodes.begin();
    while (iter != _aiNodes.end()) {
        int idx = (*iter).second->getId();
        if ((*iter).second->getDeadTime() > 4) {
            m_sim->removeAgent(idx);
            (*iter).second->removeFromParent();
            iter = _aiNodes.erase(iter++);
        }
        else {
            Vec2 velocity = (*iter).second->getVelocity();
            m_sim->setAgentMaxSpeed(idx, 1 / dt);
            m_sim->setAgentPrefVelocity(idx, Vector2(velocity.x * 1 / dt, velocity.y * 1 / dt));
            iter++;
        }
    }
    
    /*for (auto aiNode: _aiNodes) {
        int idx = aiNode->getId();
        Vec2 velocity = aiNode->getVelocity();
        m_sim->setAgentMaxSpeed(idx, 1/dt);
        m_sim->setAgentPrefVelocity(idx, Vector2(velocity.x * 1 / dt, velocity.y * 1 / dt));
    }*/

    m_sim->doStep();

    for (auto iter : _aiNodes) {
        int idx = iter.second->getId();
        Vector2 velocity = m_sim->getAgentVelocity(idx);
        Vector2 v = m_sim->getAgentPosition(idx);
        iter.second->updatePos(Vec2(velocity.x() * dt, velocity.y() * dt));
        iter.second->setPosition(Vec2(v.x(), v.y()));

        int enemyIdx = m_sim->getNearestEnemy(idx, iter.second->getPursuitRidius());
        if (enemyIdx >= 0) {
            iter.second->setNearestEnemy(_aiNodes[enemyIdx]);
        }
        else {
            iter.second->setNearestEnemy(nullptr);
        }
    }
}

void AIScene::createFSMNode() {
    float x = RandomHelper::random_real<float>(300, 400);
    float y = RandomHelper::random_real<float>(0, 100);
    Vec2 v(x, y);

    auto node = _aiNodeManager->getFSMNode();
    node->setPosition(v);
    node->setId(_aiNodeIdx);
    this->addChild(node);

    int idx = m_sim->addAgent(Vector2(v.x, v.y));
    m_sim->setAgentAINode(idx, node);
    m_sim->setAgentType(idx, int(AINodeType::FSMNode));

    _aiNodes.emplace(_aiNodeIdx++, node);
}

void AIScene::createHFSMNode() {
    float x = RandomHelper::random_real<float>(600, 700);
    float y = RandomHelper::random_real<float>(540, 640);
    Vec2 v(x, y);
    auto node = _aiNodeManager->getHFSMNode();
    node->setPosition(v);
    node->setId(_aiNodeIdx);
    this->addChild(node);

    int idx = m_sim->addAgent(Vector2(v.x, v.y));
    m_sim->setAgentAINode(idx, node);
    m_sim->setAgentType(idx, int(AINodeType::HFSMNode));

    _aiNodes.emplace(_aiNodeIdx++, node);
}

void AIScene::createBTTreeNode() {
    float x = RandomHelper::random_real<float>(1000, 1100);
    float y = RandomHelper::random_real<float>(0, 100);
    Vec2 v(x, y);
    auto node = _aiNodeManager->getBTTreeNode();
    node->setPosition(v);
    node->setId(_aiNodeIdx);
    this->addChild(node);

    int idx = m_sim->addAgent(Vector2(v.x, v.y));
    m_sim->setAgentAINode(idx, node);
    m_sim->setAgentType(idx, int(AINodeType::BTTreeNode));

    _aiNodes.emplace(_aiNodeIdx++, node);
}

void AIScene::createAILogNode() {
    _aiLogNode = AILogNode::create();
    this->addChild(_aiLogNode);
    _aiLogNode->setPosition(Vec2(700, 320));
}

void AIScene::createGOAPTestNode() {
    _goapTestNode = GOAPTestNode::create();
    this->addChild(_goapTestNode);
    _aiLogNode->setPosition(Vec2(700, 320));
}

void AIScene::createHTNNode() {
    float x = RandomHelper::random_real<float>(0, 100);
    float y = RandomHelper::random_real<float>(440, 540);
    Vec2 v(x, y);
    auto node = _aiNodeManager->getHTNNode();
    node->setPosition(v);
    node->setId(_aiNodeIdx);
    this->addChild(node);

    int idx = m_sim->addAgent(Vector2(v.x, v.y));
    m_sim->setAgentAINode(idx, node);
    m_sim->setAgentType(idx, int(AINodeType::HTNNode));

    _aiNodes.emplace(_aiNodeIdx++, node);
}

void AIScene::createGOAPNode() {
    float x = RandomHelper::random_real<float>(1300, 1400);
    float y = RandomHelper::random_real<float>(440, 540);
    Vec2 v(x, y);
    auto node = _aiNodeManager->getGOAPNode();
    node->setPosition(v);
    node->setId(_aiNodeIdx);
    this->addChild(node);

    int idx = m_sim->addAgent(Vector2(v.x, v.y));
    m_sim->setAgentAINode(idx, node);
    m_sim->setAgentType(idx, int(AINodeType::GOAPNode));

    _aiNodes.emplace(_aiNodeIdx++, node);
}
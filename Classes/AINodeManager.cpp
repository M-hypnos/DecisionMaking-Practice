#include "AINodeManager.h"

AINode* AINodeManager::getFSMNode(){
	auto node = FSMNode::create();
    auto body = DrawNode::create();
    node->_renderNode->addChild(body, -1);
    /*float r = RandomHelper::random_real<float>(0, 1);
    float g = RandomHelper::random_real<float>(0, 1);
    float b = RandomHelper::random_real<float>(0, 1);
    body->drawDot(Vec2(0, 0), node->getRidius(), Color4F(r, g, b, 0.5));*/
    body->drawDot(Vec2(0, 0), node->getRidius(), Color4F(1, 0, 0, 0.5));
	return node;
}

AINode* AINodeManager::getHFSMNode(){
	auto node = HFSMNode::create();
    auto body = DrawNode::create();
    node->_renderNode->addChild(body, -1);
    /*float r = RandomHelper::random_real<float>(0, 1);
    float g = RandomHelper::random_real<float>(0, 1);
    float b = RandomHelper::random_real<float>(0, 1);
    body->drawDot(Vec2(0, 0), node->getRidius(), Color4F(r, g, b, 0.5));*/
    body->drawDot(Vec2(0, 0), node->getRidius(), Color4F(0, 1, 0, 0.5));
	return node;
}
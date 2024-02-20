#include "BTTreeNode.h"

BTTreeNode* BTTreeNode::create() {
    BTTreeNode* btTreeNode = new(nothrow) BTTreeNode();
    if (btTreeNode && btTreeNode->init()) {
        btTreeNode->autorelease();
        return btTreeNode;
    }
    CC_SAFE_DELETE(btTreeNode);
    return nullptr;
}

BTTreeNode::~BTTreeNode() {
    delete _btTree;
    _btTree = nullptr;
}

bool BTTreeNode::init()
{
    AIAttackNode::init();
    _btTree = new BTTreeExample(nullptr);
    _btTree->setTree();
    _btTree->start();

    return true;
}

void BTTreeNode::update(float dt) {
    AIAttackNode::update(dt);
    _btTree->onUpdate(dt, this);
}
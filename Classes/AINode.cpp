#include "AINode.h"

AINode* AINode::create() {
    AINode* aiNode = new(nothrow) AINode();
    if (aiNode && aiNode->init()) {
        aiNode->autorelease();
        return aiNode;
    }
    CC_SAFE_DELETE(aiNode);
    return nullptr;
}

bool AINode::init()
{
    return true;
}

bool AINode::isStopORCA() {
    return true;
}
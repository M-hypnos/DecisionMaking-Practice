#include "BTConditionNode.h"

BTConditionNode::BTConditionNode( function<bool(AINode*, float dt)> conditionFunc)
: _conditionFunc(conditionFunc)
{
};

BTConditionNode::~BTConditionNode(){

}

BTResult BTConditionNode::onUpdateAction(float dt, AINode* aiNode) {
	return _conditionFunc(aiNode, dt) ? BTResult::SUCCESS : BTResult::FAIL;
}
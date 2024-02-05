#include "BTNode.h"

BTNode::BTNode()
: _parentNode(nullptr)
, _precondition(nullptr)
, _isRunning(false)
{
};

BTNode::~BTNode(){
	clear();
}

void BTNode::clear() {
	if (_precondition != nullptr) {
		delete _precondition;
		_precondition = nullptr;
	}
}

bool BTNode::evaluate(AINode* aiNode) {
	if (_precondition == nullptr) {
		return true;
	}
	return _precondition->doEvaluate(aiNode);
}

void BTNode::onEnter(AINode* aiNode) {
	CCASSERT(!_isRunning, "running node cannot enter");
	if (_isRunning) {
		return;
	}
	_isRunning = true;
	onEnterAction(aiNode);
}

BTResult BTNode::onUpdate(float dt, AINode* aiNode) {
	if (!_isRunning) {
		onEnter(aiNode);
	}
	auto result = onUpdateAction(dt, aiNode);
	if (result != BTResult::RUNNING) {
		onExit(aiNode, result);
	}
	return result;
}

void BTNode::onExit(AINode* aiNode, BTResult result) {
	if (!_isRunning) {
		return;
	}
	_isRunning = false;
	onExitAction(aiNode, result);
}

void BTNode::onInterrupt(AINode* aiNode) {
	onExit(aiNode, BTResult::INTERRUPT);
}
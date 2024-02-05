#include "BTSequenceNode.h"

BTSequenceNode::BTSequenceNode()
: _executeIdx(-1)
{
};

BTSequenceNode::~BTSequenceNode(){

}

void BTSequenceNode::onEnterAction(AINode* aiNode) {

}

BTResult BTSequenceNode::onUpdateAction(float dt, AINode* aiNode) {
	if (_childNodes.empty()) {
		return BTResult::SUCCESS;
	}

	auto result = BTResult::SUCCESS;
	if (_executeIdx >= 0) {
		if (_childNodes[_executeIdx]->evaluate(aiNode)) {
			result = _childNodes[_executeIdx]->onUpdate(dt, aiNode);
			if (result != BTResult::SUCCESS) {
				return result;
			}
		}
		else {
			_childNodes[_executeIdx]->onInterrupt(aiNode);
			return BTResult::FAIL;
		}
	}

	for (int i = _executeIdx + 1; i < _childNodes.size(); i++) {
		if (_childNodes[i]->evaluate(aiNode)) {
			_executeIdx = i;
			_childNodes[_executeIdx]->onEnter(aiNode);
			result = _childNodes[_executeIdx]->onUpdate(dt, aiNode);
			if (result != BTResult::SUCCESS) {
				return result;
			}
		}
		else {
			return BTResult::FAIL;
		}
	}
	return result;
}

void BTSequenceNode::onExitAction(AINode* aiNode, BTResult result) {
	_executeIdx = -1;
}

void BTSequenceNode::onInterrupt(AINode* aiNode) {
	if (_executeIdx >= 0) {
		_childNodes[_executeIdx]->onInterrupt(aiNode);
	}
	onExit(aiNode, BTResult::INTERRUPT);
}
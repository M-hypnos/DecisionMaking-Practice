#include "BTSelectNode.h"

BTSelectNode::BTSelectNode()
: _executeIdx(-1)
{
};

BTSelectNode::~BTSelectNode(){

}

void BTSelectNode::onEnterAction(AINode* aiNode) {
	
}

BTResult BTSelectNode::onUpdateAction(float dt, AINode* aiNode) {
	if (_childNodes.empty()) {
		return BTResult::SUCCESS;
	}

	auto result = BTResult::FAIL;
	if (_executeIdx >= 0) {
		if (_childNodes[_executeIdx]->evaluate(aiNode)) {
			result = _childNodes[_executeIdx]->onUpdate(dt, aiNode);
			if (result != BTResult::FAIL) {
				return result;
			}
		}
		else {
			_childNodes[_executeIdx]->onInterrupt(aiNode);
		}
	}

	for (int i = 0; i < _childNodes.size(); i++) {
		if (i != _executeIdx && _childNodes[i]->evaluate(aiNode)) {
			_executeIdx = i;
			_childNodes[_executeIdx]->onEnter(aiNode);
			result = _childNodes[_executeIdx]->onUpdate(dt, aiNode);
			if (result != BTResult::FAIL) {
				return result;
			}
		}
	}

	return result;
}

void BTSelectNode::onExitAction(AINode* aiNode, BTResult result) {
	_executeIdx = -1;
}

void BTSelectNode::onInterrupt(AINode* aiNode) {
	if (_executeIdx >= 0) {
		_childNodes[_executeIdx]->onInterrupt(aiNode);
	}
	onExit(aiNode, BTResult::INTERRUPT);
}
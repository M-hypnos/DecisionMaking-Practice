#include "BTPrioritySelectNode.h"

BTPrioritySelectNode::BTPrioritySelectNode()
: _executeIdx(-1)
{
};

BTPrioritySelectNode::~BTPrioritySelectNode(){

}

void BTPrioritySelectNode::onEnterAction(AINode* aiNode) {
	
}

BTResult BTPrioritySelectNode::onUpdateAction(float dt, AINode* aiNode) {
	if (_childNodes.empty()) {
		return BTResult::SUCCESS;
	}

	auto result = BTResult::FAIL;

	for (int i = 0; i < _childNodes.size(); i++) {
		if (i == _executeIdx) {
			if (_childNodes[i]->evaluate(aiNode)) {
				result = _childNodes[_executeIdx]->onUpdate(dt, aiNode);
				if (result != BTResult::FAIL) {
					return result;
				}
			}
			else {
				_childNodes[_executeIdx]->onInterrupt(aiNode);
			}
		}
		else {
			if (_childNodes[i]->evaluate(aiNode)) {
				_childNodes[i]->onEnter(aiNode);
				result = _childNodes[i]->onUpdate(dt, aiNode);
				if (result != BTResult::FAIL) {
					if (i < _executeIdx) {
						_childNodes[_executeIdx]->onInterrupt(aiNode);
					}
					_executeIdx = i;
					return result;
				}
			}
		}
	}

	return result;
}

void BTPrioritySelectNode::onExitAction(AINode* aiNode, BTResult result) {
	_executeIdx = -1;
}

void BTPrioritySelectNode::onInterrupt(AINode* aiNode) {
	if (_executeIdx >= 0) {
		_childNodes[_executeIdx]->onInterrupt(aiNode);
	}
	onExit(aiNode, BTResult::INTERRUPT);
}
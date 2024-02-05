#include "BTParallelNode.h"

BTParallelNode::BTParallelNode(int successTarNum)
: _successTarNum(successTarNum)
, _successCurNum(0)
, _failCurNum(0)
{
};

BTParallelNode::~BTParallelNode(){
	
}

void BTParallelNode::clear() {
	for (auto node : _childNodes) {
		delete node;
	}
	_childNodes.clear();
	_waitNodes.clear();
}

void BTParallelNode::onEnterAction(AINode* aiNode) {

}

BTResult BTParallelNode::onUpdateAction(float dt, AINode* aiNode) {
	if (_childNodes.empty()) {
		return BTResult::SUCCESS;
	}
	vector<BTNode*> waitNode;
	int failNum = _childNodes.size() - _successTarNum;

	if (_waitNodes.empty()) {
		for (auto node : _childNodes) {
			if (node->evaluate(aiNode)) {
				node->onEnter(aiNode);
				switch (node->onUpdate(dt, aiNode))
				{
				case BTResult::SUCCESS: 
					_successCurNum++;
					if (_successCurNum >= _successTarNum) {
						for (auto node : waitNode) {
							node->onInterrupt(aiNode);
						}
						return BTResult::SUCCESS;
					}
					break;
				case BTResult::FAIL:
					_failCurNum++;
					if (_failCurNum > failNum) {
						for (auto node : waitNode) {
							node->onInterrupt(aiNode);
						}
						return BTResult::FAIL;
					}
					break;
				case BTResult::RUNNING:
					waitNode.push_back(node);
					break;
				}
			}
			else {
				_failCurNum++;
				if (_failCurNum > failNum) {
					for (auto node : waitNode) {
						node->onInterrupt(aiNode);
					}
					return BTResult::FAIL;
				}
			}
		}
	}
	else {
		for (auto node : _waitNodes) {
			if (node->evaluate(aiNode)) {
				switch (node->onUpdate(dt, aiNode))
				{
				case BTResult::SUCCESS:
					_successCurNum++;
					if (_successCurNum >= _successTarNum) {
						for (auto node : waitNode) {
							node->onInterrupt(aiNode);
						}
						return BTResult::SUCCESS;
					}
					break;
				case BTResult::FAIL:
					_failCurNum++;
					if (_failCurNum > failNum) {
						for (auto node : waitNode) {
							node->onInterrupt(aiNode);
						}
						return BTResult::FAIL;
					}
					break;
				case BTResult::RUNNING:
					waitNode.push_back(node);
					break;
				}
			}
			else {
				node->onInterrupt(aiNode);
				_failCurNum++;
				if (_failCurNum > failNum) {
					for (auto node : waitNode) {
						node->onInterrupt(aiNode);
					}
					return BTResult::FAIL;
				}
			}
		}
	}

	_waitNodes.assign(waitNode.begin(), waitNode.end());
	if (_waitNodes.empty()) {
		auto result = _successCurNum >= _successTarNum ? BTResult::SUCCESS : BTResult::FAIL;
		return result;
	}
	else {
		return BTResult::RUNNING;
	}
}

void BTParallelNode::onExitAction(AINode* aiNode, BTResult result) {
	_waitNodes.clear();
	_successCurNum = 0;
	_failCurNum = 0;
}

void BTParallelNode::onInterrupt(AINode* aiNode) {
	if (!_waitNodes.empty()) {
		for (auto node : _waitNodes) {
			node->onInterrupt(aiNode);
		}
	}
	onExit(aiNode, BTResult::INTERRUPT);
}
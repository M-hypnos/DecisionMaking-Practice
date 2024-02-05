#include "BTTree.h"

BTTree::BTTree(BTNode* root)
: _isActived(false)
, _onlyOnce(false)
, _root(root)
{
};

BTTree::~BTTree(){
	if (_root != nullptr) {
		delete _root;
	}
}

void BTTree::start(bool onlyOnce) {
	if (_isActived) return;
	_isActived = true;
	_onlyOnce = onlyOnce;
}

void BTTree::onUpdate(float dt, AINode* aiNode) {
	if (!_isActived) return;
	if (_root == nullptr) return;
	if (!_root->evaluate(aiNode)) { 
		_root->onInterrupt(aiNode);
		if (_onlyOnce) {
			_isActived = false;
			CCLOG("BTTree::onUpdate interrupt£¡");
		}
		return; 
	}
	if (_root->isRunning()) {
		auto result = _root->onUpdate(dt, aiNode);
		if (_onlyOnce && result != BTResult::RUNNING) {
			_isActived = false;
			if (result == BTResult::SUCCESS) {
				CCLOG("BTTree:onUpdate success£¡");
			}
			else {
				CCLOG("BTTree:onUpdate fail£¡");
			}
		}
	}
	else {
		_root->onEnter(aiNode);
	}
}
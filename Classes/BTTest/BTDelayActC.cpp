#include "BTDelayActC.h"

void BTDelayActC::onEnterAction(AINode* aiNode) {
	CCLOG("BTDelayActC::onEnterAction  ");
	static_cast<AILogNode*>(aiNode)->setString1("BTDelayActC::onEnterAction  ");
}

void BTDelayActC::onExitAction(AINode* aiNode, BTResult result) {
	static_cast<AILogNode*>(aiNode)->interruptAct();
	if (result == BTResult::SUCCESS) {
		CCLOG("BTDelayActC::onExitAction SUCCESS ");
		static_cast<AILogNode*>(aiNode)->setString2("BTDelayActC::onExitAction SUCCESS ");
	}
	else if (result == BTResult::FAIL) {
		CCLOG("BTDelayActC::onExitAction FAIL ");
		static_cast<AILogNode*>(aiNode)->setString2("BTDelayActC::onExitAction FAIL ");
	}
	else {
		CCLOG("BTDelayActC::onExitAction INTERRUPT ");
		static_cast<AILogNode*>(aiNode)->setString2("BTDelayActC::onExitAction INTERRUPT ");
	}
}

BTResult BTDelayActC::onUpdateAction(float dt, AINode* aiNode) {
	CCLOG("BTDelayActC::onUpdateAction  ");
	return static_cast<AILogNode*>(aiNode)->doDelayAction(dt, "BTDelayActC::onUpdateAction ");
}
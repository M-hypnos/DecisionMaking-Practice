#include "BTDelayActA.h"

void BTDelayActA::onEnterAction(AINode* aiNode) {
	CCLOG("BTDelayActA::onEnterAction  ");
	static_cast<AILogNode*>(aiNode)->setString1("BTDelayActA::onEnterAction  ");
}

void BTDelayActA::onExitAction(AINode* aiNode, BTResult result) {
	static_cast<AILogNode*>(aiNode)->interruptAct();
	if (result == BTResult::SUCCESS) {
		CCLOG("BTDelayActA::onExitAction SUCCESS ");
		static_cast<AILogNode*>(aiNode)->setString2("BTDelayActA::onExitAction SUCCESS ");
	}
	else if (result == BTResult::FAIL) {
		CCLOG("BTDelayActA::onExitAction FAIL ");
		static_cast<AILogNode*>(aiNode)->setString2("BTDelayActA::onExitAction FAIL ");
	}
	else {
		CCLOG("BTDelayActA::onExitAction INTERRUPT ");
		static_cast<AILogNode*>(aiNode)->setString2("BTDelayActA::onExitAction INTERRUPT ");
	}
}

BTResult BTDelayActA::onUpdateAction(float dt, AINode* aiNode) {
	CCLOG("BTDelayActA::onUpdateAction  ");
	return static_cast<AILogNode*>(aiNode)->doDelayAction(dt, "BTDelayActA::onUpdateAction ");
}
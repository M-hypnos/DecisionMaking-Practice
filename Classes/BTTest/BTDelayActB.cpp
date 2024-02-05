#include "BTDelayActB.h"

void BTDelayActB::onEnterAction(AINode* aiNode) {
	CCLOG("BTDelayActB::onEnterAction  ");
	static_cast<AILogNode*>(aiNode)->setString1("BTDelayActB::onEnterAction  ");
}

void BTDelayActB::onExitAction(AINode* aiNode, BTResult result) {
	static_cast<AILogNode*>(aiNode)->interruptAct();
	if (result == BTResult::SUCCESS) {
		CCLOG("BTDelayActB::onExitAction SUCCESS ");
		static_cast<AILogNode*>(aiNode)->setString2("BTDelayActB::onExitAction SUCCESS ");
	}
	else if (result == BTResult::FAIL) {
		CCLOG("BTDelayActB::onExitAction FAIL ");
		static_cast<AILogNode*>(aiNode)->setString2("BTDelayActB::onExitAction FAIL ");
	}
	else {
		CCLOG("BTDelayActB::onExitAction INTERRUPT ");
		static_cast<AILogNode*>(aiNode)->setString2("BTDelayActB::onExitAction INTERRUPT ");
	}
}

BTResult BTDelayActB::onUpdateAction(float dt, AINode* aiNode) {
	CCLOG("BTDelayActB::onUpdateAction  ");
	return static_cast<AILogNode*>(aiNode)->doDelayAction(dt, "BTDelayActB::onUpdateAction ");
}
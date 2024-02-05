#include "BTImmediateActB.h"

void BTImmediateActB::onEnterAction(AINode* aiNode) {
	CCLOG("BTImmediateActB::onEnterAction  ");
	times++;
	static_cast<AILogNode*>(aiNode)->setString1("BTImmediateActB::onEnterAction  ");
}

void BTImmediateActB::onExitAction(AINode* aiNode, BTResult result) {
	times = 0;
	if (result == BTResult::SUCCESS) {
		CCLOG("BTImmediateActB::onExitAction SUCCESS ");
		static_cast<AILogNode*>(aiNode)->setString2("BTImmediateActB::onExitAction SUCCESS ");
	}
	else if (result == BTResult::FAIL) {
		CCLOG("BTImmediateActB::onExitAction FAIL ");
		static_cast<AILogNode*>(aiNode)->setString2("BTImmediateActB::onExitAction FAIL ");
	}
	else {
		CCLOG("BTImmediateActB::onExitAction INTERRUPT ");
		static_cast<AILogNode*>(aiNode)->setString2("BTImmediateActB::onExitAction INTERRUPT ");
	}
}

BTResult BTImmediateActB::onUpdateAction(float dt, AINode* aiNode) {
	CCLOG("BTImmediateActB::onUpdateAction  ");
	return static_cast<AILogNode*>(aiNode)->doImmediatelyAction("BTImmediateActB::onUpdateAction "+to_string(times));
}
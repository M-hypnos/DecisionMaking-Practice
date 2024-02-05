#include "BTImmediateActA.h"

void BTImmediateActA::onEnterAction(AINode* aiNode) {
	CCLOG("BTImmediateActA::onEnterAction  ");
	times++;
	static_cast<AILogNode*>(aiNode)->setString1("BTImmediateActA::onEnterAction  ");
}

void BTImmediateActA::onExitAction(AINode* aiNode, BTResult result) {
	times = 0;
	if (result == BTResult::SUCCESS) {
		CCLOG("BTImmediateActA::onExitAction SUCCESS ");
		static_cast<AILogNode*>(aiNode)->setString2("BTImmediateActA::onExitAction SUCCESS ");
	}
	else if (result == BTResult::FAIL) {
		CCLOG("BTImmediateActA::onExitAction FAIL ");
		static_cast<AILogNode*>(aiNode)->setString2("BTImmediateActA::onExitAction FAIL ");
	}
	else {
		CCLOG("BTImmediateActA::onExitAction INTERRUPT ");
		static_cast<AILogNode*>(aiNode)->setString2("BTImmediateActA::onExitAction INTERRUPT ");
	}
}

BTResult BTImmediateActA::onUpdateAction(float dt, AINode* aiNode) {
	CCLOG("BTImmediateActA::onUpdateAction  ");
	return static_cast<AILogNode*>(aiNode)->doImmediatelyAction("BTImmediateActA::onUpdateAction "+to_string(times));
}
#include "BTImmediateActC.h"

void BTImmediateActC::onEnterAction(AINode* aiNode) {
	CCLOG("BTImmediateActC::onEnterAction  ");
	times++;
	static_cast<AILogNode*>(aiNode)->setString1("BTImmediateActC::onEnterAction  ");
}

void BTImmediateActC::onExitAction(AINode* aiNode, BTResult result) {
	times = 0;
	if (result == BTResult::SUCCESS) {
		CCLOG("BTImmediateActC::onExitAction SUCCESS ");
		static_cast<AILogNode*>(aiNode)->setString2("BTImmediateActC::onExitAction SUCCESS ");
	}
	else if (result == BTResult::FAIL) {
		CCLOG("BTImmediateActC::onExitAction FAIL ");
		static_cast<AILogNode*>(aiNode)->setString2("BTImmediateActC::onExitAction FAIL ");
	}
	else {
		CCLOG("BTImmediateActC::onExitAction INTERRUPT ");
		static_cast<AILogNode*>(aiNode)->setString2("BTImmediateActC::onExitAction INTERRUPT ");
	}
}

BTResult BTImmediateActC::onUpdateAction(float dt, AINode* aiNode) {
	CCLOG("BTImmediateActC::onUpdateAction  ");
	return static_cast<AILogNode*>(aiNode)->doImmediatelyAction("BTImmediateActC::onUpdateAction "+to_string(times));
}
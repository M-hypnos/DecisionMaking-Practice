#include "BTTestTree.h"

BTTestTree::BTTestTree(BTNode* root)
: BTTree(root)
{
};

BTTestTree::~BTTestTree(){

}

void BTTestTree::setTree() {
	/*auto act1 = new BTImmediateActA();
	auto delayNode1 = new BTCooldownNode(act1,1);
	auto act2 = new BTImmediateActB();
	auto delayNode2 = new BTCooldownNode(act2,3);
	auto act3 = new BTImmediateActC();
	auto delayNode3 = new BTCooldownNode(act3,5);*/

	/*auto seqAct = new BTSequenceNode();
	seqAct->addChild(delayNode1);
	seqAct->addChild(delayNode2);
	seqAct->addChild(delayNode3);
	_root = seqAct;*/

	/*auto selAct = new BTSelectNode();
	selAct->addChild(delayNode1);
	selAct->addChild(delayNode2);
	selAct->addChild(delayNode3);
	_root = selAct;*/

	/*auto act1 = new BTDelayActA();
	auto repeatAct1 = new BTRepeatNode(act1,2);
	auto act2 = new BTDelayActB();
	auto repeatAct2 = new BTRepeatNode(act2,2);
	auto act3 = new BTDelayActC();
	auto repeatAct3 = new BTRepeatNode(act3,2);

	auto seqAct = new BTSequenceNode();
	seqAct->addChild(repeatAct1);
	seqAct->addChild(repeatAct2);
	seqAct->addChild(repeatAct3);
	_root = seqAct;*/
	auto act1 = new BTDelayActA();
	auto cdAct = new BTCooldownNode(act1,5);
	auto act2 = new BTDelayActB();
	auto repeatAct = new BTRepeatNode(act2, 5);
	auto sel = new BTPrioritySelectNode();
	//auto sel = new BTSelectNode();
	sel->addChild(cdAct);
	sel->addChild(repeatAct);
	_root = sel;
	/*auto act1 = new BTDelayActA();
	auto repeatAct = new BTRepeatNode(act1, 2);
	auto timeLimitAct = new BTTimeLimitNode(repeatAct, 5.0);
	auto cdAct = new BTCooldownNode(timeLimitAct, 2);
	auto act2 = new BTDelayActB();
	auto sel = new BTPrioritySelectNode();
	sel->addChild(cdAct);
	sel->addChild(act2);
	_root = sel;*/
	/*auto act1 = new BTDelayActA();
	auto act2 = new BTDelayActB();
	auto act3 = new BTDelayActC();
	auto pal = new BTParallelNode(2);
	pal->addChild(act1);
	pal->addChild(act2);
	pal->addChild(act3);
	_root = pal;*/
}
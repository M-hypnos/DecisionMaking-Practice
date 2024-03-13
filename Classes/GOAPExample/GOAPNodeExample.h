#ifndef _GOAP_NODE_EXAMPLE_H__
#define _GOAP_NODE_EXAMPLE_H__
#include "AIAttackNode.h"
#include "GOAP/GOAPAction.h"
#include "GOAP/GOAPSensors.h"
#include "GOAPNode.h"
using namespace std;

class GOAPNode;

namespace GOAPNodeExampleSpace {
	class AttackNode :public GOAPAction {
	public:
		AttackNode() = delete;
		AttackNode(GOAPNode* aiNode);
		~AttackNode();
	private:
		virtual void onEnterAction() override;
		virtual GOAPResult onUpdateAction(float dt) override;
		virtual void onExitAction(GOAPResult result) override;
		GOAPNode* _aiNode;
	};

	class DeadNode :public GOAPAction {
	public:
		DeadNode() = delete;
		DeadNode(GOAPNode* aiNode);
		~DeadNode();
	private:
		virtual void onEnterAction() override;
		virtual GOAPResult onUpdateAction(float dt) override;
		virtual void onExitAction(GOAPResult result) override;
		GOAPNode* _aiNode;
	};

	class WanderNode :public GOAPAction {
	public:
		WanderNode() = delete;
		WanderNode(GOAPNode* aiNode);
		~WanderNode();
	private:
		virtual void onEnterAction() override;
		virtual GOAPResult onUpdateAction(float dt) override;
		virtual void onExitAction(GOAPResult result) override;
		GOAPNode* _aiNode;
	};

	class PursuitNode :public GOAPAction {
	public:
		PursuitNode() = delete;
		PursuitNode(GOAPNode* aiNode);
		~PursuitNode();
	private:
		virtual void onEnterAction() override;
		virtual GOAPResult onUpdateAction(float dt) override;
		virtual void onExitAction(GOAPResult result) override;
		GOAPNode* _aiNode;
	};

	class EvadingNode :public GOAPAction {
	public:
		EvadingNode() = delete;
		EvadingNode(GOAPNode* aiNode);
		~EvadingNode();
	private:
		virtual void onEnterAction() override;
		virtual GOAPResult onUpdateAction(float dt) override;
		virtual void onExitAction(GOAPResult result) override;
		GOAPNode* _aiNode;
	};

	class IdleNode :public GOAPAction {
	public:
		IdleNode() = delete;
		IdleNode(GOAPNode* aiNode);
		~IdleNode();
	private:
		virtual void onEnterAction() override;
		virtual GOAPResult onUpdateAction(float dt) override;
		virtual void onExitAction(GOAPResult result) override;
		GOAPNode* _aiNode;
	};

	class HPSensor :public GOAPISensor {
	public:
		HPSensor() = delete;
		HPSensor(GOAPNode* aiNode);
		virtual void initSensor(unique_ptr<GOAPWorldState>& worldState);
		virtual void updateSensor(unique_ptr<GOAPWorldState>& worldState);
	private:
		GOAPNode* _aiNode;
	};

	class EnemySensor :public GOAPISensor {
	public:
		EnemySensor() = delete;
		EnemySensor(GOAPNode* aiNode);
		virtual void initSensor(unique_ptr<GOAPWorldState>& worldState);
		virtual void updateSensor(unique_ptr<GOAPWorldState>& worldState);
	private:
		GOAPNode* _aiNode;
	};
}

#endif
#ifndef _HTN_NODE_EXAMPLE_H__
#define _HTN_NODE_EXAMPLE_H__
#include "AIAttackNode.h"
#include "HTN/HTNPrimitiveTask.h"
#include "HTN/HTNSensors.h"
#include "HTNNode.h"
using namespace std;

class HTNNode;

namespace HTNNodeExampleSpace {
	class AttackNode :public HTNPrimitiveTask {
	public:
		AttackNode() = delete;
		AttackNode(HTNNode* aiNode);
		~AttackNode();
		void effectWorldState(unique_ptr<HTNWorldState>& worldState) override;
	private:
		virtual void onEnterAction() override;
		virtual HTNResult onUpdateAction(float dt) override;
		virtual void onExitAction(HTNResult result) override;
		HTNNode* _aiNode;
	};

	class DeadNode :public HTNPrimitiveTask {
	public:
		DeadNode() = delete;
		DeadNode(HTNNode* aiNode);
		~DeadNode();
		void effectWorldState(unique_ptr<HTNWorldState>& worldState) override;
	private:
		virtual void onEnterAction() override;
		virtual HTNResult onUpdateAction(float dt) override;
		virtual void onExitAction(HTNResult result) override;
		HTNNode* _aiNode;
	};

	class WanderNode :public HTNPrimitiveTask {
	public:
		WanderNode() = delete;
		WanderNode(HTNNode* aiNode);
		~WanderNode();
		void effectWorldState(unique_ptr<HTNWorldState>& worldState) override;
	private:
		virtual void onEnterAction() override;
		virtual HTNResult onUpdateAction(float dt) override;
		virtual void onExitAction(HTNResult result) override;
		HTNNode* _aiNode;
	};

	class PursuitNode :public HTNPrimitiveTask {
	public:
		PursuitNode() = delete;
		PursuitNode(HTNNode* aiNode);
		~PursuitNode();
		void effectWorldState(unique_ptr<HTNWorldState>& worldState) override;
	private:
		virtual void onEnterAction() override;
		virtual HTNResult onUpdateAction(float dt) override;
		virtual void onExitAction(HTNResult result) override;
		HTNNode* _aiNode;
	};

	class EvadingNode :public HTNPrimitiveTask {
	public:
		EvadingNode() = delete;
		EvadingNode(HTNNode* aiNode);
		~EvadingNode();
		void effectWorldState(unique_ptr<HTNWorldState>& worldState) override;
	private:
		virtual void onEnterAction() override;
		virtual HTNResult onUpdateAction(float dt) override;
		virtual void onExitAction(HTNResult result) override;
		HTNNode* _aiNode;
	};

	class IdleNode :public HTNPrimitiveTask {
	public:
		IdleNode() = delete;
		IdleNode(HTNNode* aiNode);
		~IdleNode();
		void effectWorldState(unique_ptr<HTNWorldState>& worldState) override;
	private:
		virtual void onEnterAction() override;
		virtual HTNResult onUpdateAction(float dt) override;
		virtual void onExitAction(HTNResult result) override;
		HTNNode* _aiNode;
	};

	class HPSensor :public HTNISensor {
	public:
		HPSensor() = delete;
		HPSensor(HTNNode* aiNode);
		virtual void initSensor(unique_ptr<HTNWorldState>& worldState);
		virtual void updateSensor(unique_ptr<HTNWorldState>& worldState);
	private:
		HTNNode* _aiNode;
	};

	class EnemySensor :public HTNISensor {
	public:
		EnemySensor() = delete;
		EnemySensor(HTNNode* aiNode);
		virtual void initSensor(unique_ptr<HTNWorldState>& worldState);
		virtual void updateSensor(unique_ptr<HTNWorldState>& worldState);
	private:
		HTNNode* _aiNode;
	};
}

#endif
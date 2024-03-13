#ifndef _GOAP_NODE_TEST_H__
#define _GOAP_NODE_TEST_H__
#include "GOAPTestNode.h"
#include "GOAP/GOAPAction.h"
#include "GOAP/GOAPSensors.h"
#include "GOAP/GOAPIGoal.h"

using namespace std;

class GOAPTestNode;

namespace GOAPNodeTestSpace {
	class ChopTree :public GOAPAction {
	public:
		ChopTree() = delete;
		ChopTree(GOAPTestNode* aiNode);
		~ChopTree();
	private:
		virtual void onEnterAction() override;
		virtual GOAPResult onUpdateAction(float dt) override;
		virtual void onExitAction(GOAPResult result) override;
		GOAPTestNode* _aiNode;
	};

	class BuyTree :public GOAPAction {
	public:
		BuyTree() = delete;
		BuyTree(GOAPTestNode* aiNode);
		~BuyTree();
	private:
		virtual void onEnterAction() override;
		virtual GOAPResult onUpdateAction(float dt) override;
		virtual void onExitAction(GOAPResult result) override;
		GOAPTestNode* _aiNode;
	};

	class MineOre :public GOAPAction {
	public:
		MineOre() = delete;
		MineOre(GOAPTestNode* aiNode);
		~MineOre();
	private:
		virtual void onEnterAction() override;
		virtual GOAPResult onUpdateAction(float dt) override;
		virtual void onExitAction(GOAPResult result) override;
		GOAPTestNode* _aiNode;
	};

	class WorksWood :public GOAPAction {
	public:
		WorksWood() = delete;
		WorksWood(GOAPTestNode* aiNode);
		~WorksWood();
	private:
		virtual void onEnterAction() override;
		virtual GOAPResult onUpdateAction(float dt) override;
		virtual void onExitAction(GOAPResult result) override;
		GOAPTestNode* _aiNode;
	};

	class SmeltOre :public GOAPAction {
	public:
		SmeltOre() = delete;
		SmeltOre(GOAPTestNode* aiNode);
		~SmeltOre();
	private:
		virtual void onEnterAction() override;
		virtual GOAPResult onUpdateAction(float dt) override;
		virtual void onExitAction(GOAPResult result) override;
		GOAPTestNode* _aiNode;
	};

	class CreateAxe :public GOAPAction {
	public:
		CreateAxe() = delete;
		CreateAxe(GOAPTestNode* aiNode);
		~CreateAxe();
	private:
		virtual void onEnterAction() override;
		virtual GOAPResult onUpdateAction(float dt) override;
		virtual void onExitAction(GOAPResult result) override;
		GOAPTestNode* _aiNode;
	};

	class WoodSensor :public GOAPISensor {
	public:
		WoodSensor() = delete;
		WoodSensor(GOAPTestNode* aiNode);
		virtual void initSensor(unique_ptr<GOAPWorldState>& worldState);
		virtual void updateSensor(unique_ptr<GOAPWorldState>& worldState);
	private:
		GOAPTestNode* _aiNode;
	};

	class OreSensor :public GOAPISensor {
	public:
		OreSensor() = delete;
		OreSensor(GOAPTestNode* aiNode);
		virtual void initSensor(unique_ptr<GOAPWorldState>& worldState);
		virtual void updateSensor(unique_ptr<GOAPWorldState>& worldState);
	private:
		GOAPTestNode* _aiNode;
	};

	class AxeSensor :public GOAPISensor {
	public:
		AxeSensor() = delete;
		AxeSensor(GOAPTestNode* aiNode);
		virtual void initSensor(unique_ptr<GOAPWorldState>& worldState);
		virtual void updateSensor(unique_ptr<GOAPWorldState>& worldState);
	private:
		GOAPTestNode* _aiNode;
	};
}

#endif
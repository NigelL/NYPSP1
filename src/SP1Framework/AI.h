#pragma once
#include "Character.h"
#include "PathFinding.h"
#include <Windows.h>
#include <vector>



void UpdateAI();

enum AIState {
	Patrol,
	Chase,
	Attack
};


class AI : public Character {
public:
	int m_Speed;
	int AIIndex = 0;
	double updateTime;
	AIState m_curState;
	Entity* m_Target;
	void Update(double dt);
	std::vector<node> pathFound;
	AI() :Character(100,50) {
		
	}
private:
	void JustRoam();
	void MoveToTarget(double moveTime);
	void AttackPlayer(double dt);

};
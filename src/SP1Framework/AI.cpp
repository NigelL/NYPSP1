#include "AI.h"
#include "PathFinding.h"

COORD roamDir[4] = { COORD{1,0},COORD{-1,0} ,COORD{0,1},COORD{0,-1} };



extern Entity** singleplayerMap;

double Distance(COORD a,COORD b) {
	return sqrt(pow(a.X - b.X, 2) + pow(a.Y - b.Y, 2));
}

void AI::Update(double dt) {
	switch (m_curState)
	{
	case Patrol:		
		JustRoam();
		break;
	case Chase:
		MoveToTarget(dt);
		break;
	case Attack:
		AttackPlayer(dt);
		break;
	default:
		JustRoam();
		break;
	}
}

void AI::JustRoam() {
	
	COORD curDir = roamDir[rand() % 4];
	Move(curDir.X, curDir.Y, singleplayerMap);
	if (Distance(this->m_Position, m_Target->m_Position) < 10) {
		m_curState = Chase;
		pathFound = std::vector<node>();
		AIIndex = 0;
	}
}


void AI::MoveToTarget(double moveTime) {


	

	//if (updateTime < moveTime) {
		if (Distance(this->m_Position, m_Target->m_Position) > 20) {
			m_curState = Patrol;
		}		
	
		
	//	AIIndex = 0;
	//	updateTime = moveTime + 2;
	//}
	
	   if (pathFound.size() > 0) {
			Move(pathFound[AIIndex].xPos - this->m_Position.X, pathFound[AIIndex].yPos - this->m_Position.Y, singleplayerMap);
			if (Distance(COORD{ (short)pathFound[AIIndex].xPos,(short)pathFound[AIIndex].yPos }, this->m_Position) < 2) {
				m_curState = Attack;
			
			}
			if (++AIIndex >= (int)pathFound.size()) {				
				this->pathFound = pathFinder(this->m_Position, m_Target->m_Position);
				AIIndex = 0;
			}
		}
		else {
			this->pathFound = pathFinder(this->m_Position, m_Target->m_Position);
			
		}
	

}

void AI::AttackPlayer(double dt) {
	
	if (Distance(this->m_Position, m_Target->m_Position) > 1.4) {
		m_curState = Chase;
		
	}
	else  {
		if (updateTime < dt) {
			m_Target->TakeDamage(20);
			updateTime = dt + 0.25;
		}
		
	}
}
std::vector<AI> allAI;


void UpdateAI() {
	for (int i = 0; i < (int)allAI.size(); i++) {
		//allAI[i].Update();
	}

}
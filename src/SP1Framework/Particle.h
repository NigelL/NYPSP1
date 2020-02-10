#pragma once
#include <Windows.h>
#include "Entity.h"

#include <vector>

enum ParticleIdentifier {
	
	BreakWall,
	Explosion,
	Ezreal,
};

class Particle {
public:
	Entity particle;

	COORD m_Speed;
	double lifeTime;	
	ParticleIdentifier identifier;


	Particle();
	Particle(Entity _particle);
	Particle(Entity _particle, COORD _speed);

	void Update();


private:
	void Move(COORD dir);
	


};

#include "ParticleSystem.h"
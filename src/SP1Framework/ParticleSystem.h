#pragma once
#include "Particle.h"
#include <vector>



class ParticleSystem {
public:
	COORD startLocation;
	std::vector<COORD> dirParticles;
	std::vector<Particle> particlesToAnimate;
	int particleAmount;
	double timeElapsed;
	double particleSpeed;

	void StartParticles();
	void StartParticles(COORD _startLocation, double time);
	void StartParticles(COORD _startLocation, COORD _dir, double time, bool justFlip);
	void StartParticles(COORD _startLocation, double currentTimeToAdd, COORD dir, bool justFlip);



	ParticleSystem();
	ParticleSystem(COORD _startLocation, std::vector<COORD> _dirParticles, Entity _particleProperties, int _particleAmount, double _particleSpeed, double _timeElapsed, ParticleIdentifier identify);
	ParticleSystem(COORD _startLocation, Entity _particleProperties, int _particleAmount, double _particleSpeed, double _timeElapsed, ParticleIdentifier identify);
	ParticleSystem(COORD _startLocation, std::vector<Particle> _givenParticle, double _particleSpeed, double _timeElapsed, ParticleIdentifier identify);

};

void UpdateAllParticles(double currentTime);
void CheckCollisionParticles();
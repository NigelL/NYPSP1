#include "ParticleSystem.h"
#include "PresetParticles.h"
#include "Values.h"
#include "PathFinding.h"
#include "Character.h"

extern std::vector<Particle> allParticles;
extern Entity** entireMapChar;

extern Character playerOne, playerTwo;

extern double g_dElapsedTime;
extern bool renderSpotlightMap;

void ParticleSystem::StartParticles() {


	for (int i = 0; i < (int)particlesToAnimate.size(); i++) {


		allParticles.push_back(particlesToAnimate[i]);
	}


}

void ParticleSystem::StartParticles(COORD _startLocation, double currentTimeToAdd) {


	for (int i = 0; i < (int)particlesToAnimate.size(); i++) {
		particlesToAnimate[i].particle.m_Position = _startLocation;
		particlesToAnimate[i].lifeTime = currentTimeToAdd + timeElapsed;
		allParticles.push_back(particlesToAnimate[i]);
	}


}
void ParticleSystem::StartParticles(COORD _startLocation, COORD _dir, double currentTimeToAdd, bool justFlip) {

	UpdateParticleDir(_dir, dirParticles, justFlip);
	for (int i = 0; i < (int)particlesToAnimate.size(); i++) {
		particlesToAnimate[i].particle.m_Position = _startLocation;
		particlesToAnimate[i].lifeTime = currentTimeToAdd + timeElapsed;
		particlesToAnimate[i].m_Speed.X = (SHORT)(dirParticles[i].X * particleSpeed);
		particlesToAnimate[i].m_Speed.Y = (SHORT)(dirParticles[i].Y * particleSpeed);
		allParticles.push_back(particlesToAnimate[i]);
	}


}
void ParticleSystem::StartParticles(COORD _startLocation, double currentTimeToAdd, COORD dir, bool justFlip) {
	//UpdateParticleDir(dir, dirParticles,justFlip);
	if (justFlip) {
		FlipParticles(particlesToAnimate, dir);
	}
	if (dir.X != 0 || dir.Y != 0) {
		for (int i = 0; i < (int)particlesToAnimate.size(); i++) {
			short int prevX = particlesToAnimate[i].particle.m_Position.X;
			short int prevY = particlesToAnimate[i].particle.m_Position.Y;
			particlesToAnimate[i].particle.m_Position.X = _startLocation.X != -1 ? particlesToAnimate[i].particle.m_Position.X + _startLocation.X : particlesToAnimate[i].particle.m_Position.X;
			particlesToAnimate[i].particle.m_Position.Y = _startLocation.Y != -1 ? particlesToAnimate[i].particle.m_Position.Y + _startLocation.Y : particlesToAnimate[i].particle.m_Position.Y;
			dirParticles[i].X = dir.X;
			dirParticles[i].Y = dir.Y;
			particlesToAnimate[i].lifeTime = currentTimeToAdd + timeElapsed;
			particlesToAnimate[i].m_Speed.X = (SHORT)(dirParticles[i].X * particleSpeed);
			particlesToAnimate[i].m_Speed.Y = (SHORT)(dirParticles[i].Y * particleSpeed);
			allParticles.push_back(particlesToAnimate[i]);
			particlesToAnimate[i].particle.m_Position.X = prevX;
			particlesToAnimate[i].particle.m_Position.Y = prevY;
		}
	}

}


ParticleSystem::ParticleSystem() {

}

ParticleSystem::ParticleSystem(COORD _startLocation, std::vector<COORD> _dirParticles, Entity _particlesProperties, int _particleAmount, double _particleSpeed, double _timeElapsed, ParticleIdentifier identify) {
	dirParticles = _dirParticles;
	timeElapsed = _timeElapsed;
	particleSpeed = _particleSpeed;
	for (int i = 0; i < _particleAmount; i++) {

		Particle currentParticle = Particle(_particlesProperties);
		currentParticle.particle.m_Position = _startLocation;
		currentParticle.m_Speed = _dirParticles[i];
		currentParticle.lifeTime = timeElapsed;
		currentParticle.identifier = identify;
		particlesToAnimate.push_back(currentParticle);
	}
}


ParticleSystem::ParticleSystem(COORD _startLocation, Entity _particlesProperties, int _particleAmount, double _particleSpeed, double _timeElapsed, ParticleIdentifier identify) {
	particleSpeed = _particleSpeed;
	timeElapsed = _timeElapsed;
	for (int i = 0; i < _particleAmount; i++) {

		Particle currentParticle = Particle(_particlesProperties);
		currentParticle.particle.m_Position = _startLocation;
		currentParticle.lifeTime = timeElapsed;
		COORD randDir;
		randDir.X = (rand() % ((_particleAmount - i))) - ((_particleAmount - i));
		randDir.Y = (rand() % ((_particleAmount - i))) + ((_particleAmount - i));
		currentParticle.m_Speed = randDir;
		currentParticle.identifier = identify;
		particlesToAnimate.push_back(currentParticle);

	}
}
ParticleSystem::ParticleSystem(COORD _startLocation, std::vector<Particle> _givenParticle, double _particleSpeed, double _timeElapsed, ParticleIdentifier identify) {

	timeElapsed = _timeElapsed;
	particleSpeed = _particleSpeed;
	particlesToAnimate = _givenParticle;
	dirParticles = std::vector<COORD>(_givenParticle.size());
	for (int i = 0; i < (int)particlesToAnimate.size(); i++) {
		particlesToAnimate[i].lifeTime = timeElapsed;
		particlesToAnimate[i].identifier = identify;
		dirParticles[i] = COORD{ 1, 0 };
		//particlesToAnimate[i].m_Speed = 
	}
}

void UpdateAllParticles(double currentTime) {

	for (int i = 0; i < (int)allParticles.size(); i++) {
		if (currentTime > allParticles[i].lifeTime) {
			switch (allParticles[i].identifier) {
			case Explosion:
				if (allParticles[i].particle.m_Position.Y < 41 && allParticles[i].particle.m_Position.Y > 0 && allParticles[i].particle.m_Position.X > 0 && allParticles[i].particle.m_Position.X < 179) {
					entireMapChar[allParticles[i].particle.m_Position.Y][allParticles[i].particle.m_Position.X] = E_WALL;
				//	grid[allParticles[i].particle.m_Position.Y][allParticles[i].particle.m_Position.X].obstacle = true;
				}
				break;
			}

			allParticles[i].particle.m_Position.X = 180;
			allParticles[i].particle.m_Position.Y = 52;
			continue;
		}
		allParticles[i].Update();
	}

	if (allParticles.size() > 0) {
		renderSpotlightMap = false;
	}
	else {
		renderSpotlightMap = true;
	}
}


void CheckCollisionParticles() {

	for (int i = 0; i < (int)allParticles.size(); i++) {
		if (allParticles[i].particle.m_Position.X < 1 || allParticles[i].particle.m_Position.X > 178 ||
			allParticles[i].particle.m_Position.Y < 1 || allParticles[i].particle.m_Position.Y > 41) {
			allParticles.erase(allParticles.begin() + i);
			continue;
		}

		switch (allParticles[i].identifier) {
		case Ezreal:
			if (entireMapChar[allParticles[i].particle.m_Position.Y][allParticles[i].particle.m_Position.X] == E_WALL)
			{
				entireMapChar[allParticles[i].particle.m_Position.Y][allParticles[i].particle.m_Position.X] = E_BLANK;
			//	grid[allParticles[i].particle.m_Position.Y][allParticles[i].particle.m_Position.X].obstacle = false;
				COORD currPart = { allParticles[i].particle.m_Position.X ,allParticles[i].particle.m_Position.Y };
				Particle explosionParticle = Particle(Entity(currPart, 219, 0x04), COORD{ 1,1 });
				explosionParticle.identifier = Explosion;
				explosionParticle.lifeTime = g_dElapsedTime + 2;
				explosionParticle.m_Speed = COORD{ 1, 1 };
				explosionParticle.particle.m_Character = 219;
				allParticles.push_back(explosionParticle);
			}
			if (entireMapChar[allParticles[i].particle.m_Position.Y][allParticles[i].particle.m_Position.X].m_Character == E_PLAYERONE.m_Character)
			{
				playerOne.TakeDamage(500);
			}
			break;


		}

		//allParticles.erase(allParticles.begin() + i);


		//if (entireMapChar[allParticles[i]][])
	}
}



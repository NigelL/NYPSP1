#include "Ezreal.h"

ParticleSystem ezrealParticles;
double currTimeForEz;
COORD ezDir;

ParticleSystem EzrealInIt()
{
    COORD c = { 0,0 };
	Entity ezParticles = Entity(c, 248, 0xF);
	double partSpeed = 2;
	ezrealParticles = ParticleSystem(c,EzrealParticleSetup(25,ezParticles),2,10,Ezreal);
	return ezrealParticles;
}


void EzrealFirstAbility() {
//	ezrealParticles.StartParticles(currTimeForEz, ezDir);
}
#pragma once
#include "Entity.h"
#include "ParticleSystem.h"

class Class : public Entity {
public :
	void(*FirstAbility)(ParticleSystem&,double);
	void (*SecondAbility)();

	Class() {

	}

	Class(void(*first)(ParticleSystem&,double), void(*second)()) : Entity(){
		FirstAbility = first;
		SecondAbility = second;
	};
	

	void UseFirstAbility(ParticleSystem& system, double elapsed) const {
		FirstAbility(system,elapsed);
	}

	void UseSecondAbility() const {
		SecondAbility();
	}


};

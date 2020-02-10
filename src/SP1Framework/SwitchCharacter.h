#pragma once
#include "game.h"

enum choice
{
	NULLCHOICE,
	SWORDSMEN,
	COMMET,
	EZREAL,
	SPOOKS
};

void switchcharacter(Character* playerTwo,choice& chosenChoice);
//void SUpersinditAbility(ParticleSystem& system,double elapsed);
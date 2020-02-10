#pragma once
#include <Windows.h>
#include "Entity.h"
class Trap {
public:
	COORD dir;
	COORD pos;
	Entity* bulletForTrap;
	short int TrapDamage;

	Trap(COORD _dir, COORD _pos, Entity* _bulletForTrap, short int _TrapDamage) {
		dir = _dir;
		pos = _pos;
		bulletForTrap = _bulletForTrap;
		TrapDamage = _TrapDamage;
	}
};

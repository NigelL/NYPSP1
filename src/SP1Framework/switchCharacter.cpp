#include "SwitchCharacter.h"

void switchcharacter(Character* playerTwo, choice& switched)
{
	switch (switched)
	{
	case SWORDSMEN:
		playerTwo->m_CharHealth = 300;
		playerTwo->m_damage = 100;
		playerTwo->m_ColorInHex = 0x09;
		break;
	case EZREAL:
		playerTwo->m_CharHealth = 100;
		playerTwo->m_damage = 50;
		playerTwo->m_ColorInHex = 0x05;
		break;
	case COMMET:
		playerTwo->m_CharHealth = 100;
		playerTwo->m_damage = 50;
		playerTwo->m_ColorInHex = 0x06;
		break;
	case SPOOKS:
		playerTwo->m_CharHealth = 200;
		playerTwo->m_damage = 1;
		playerTwo->m_ColorInHex = 0x0A;
		break;

	default:
		break;
	}
}
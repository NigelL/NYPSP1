#include "Swordsmen.h"

bool swordsmen(Character* playerTwo,Character* playerOne,double* addtime2,int** entireMapChar,bool g_abKeyPressed[])
{
	bool attack = false;
	

	if (entireMapChar[playerTwo->m_dirY + playerTwo->m_Position.Y][playerTwo->m_dirX + playerTwo->m_Position.X] == 100)
	{
		if (g_abKeyPressed[K_F])
		{
			playerOne->TakeDamage(playerTwo->m_damage);
			if (playerOne->m_CharHealth <= 0)
			{
				entireMapChar[playerTwo->m_dirY + playerTwo->m_Position.Y][playerTwo->m_dirX + playerTwo->m_Position.X] = 0;
			}
			attack = true;
		}
	}

	return attack;
}
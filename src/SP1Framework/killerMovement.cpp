#include "KillerMovement.h"
bool killerMovement(Character* player, bool g_abKeyPressed[], Entity** entireMapChar)
{
	bool moved = false;

	if (g_abKeyPressed[K_UP])
	{
		player->SetDirection(0, -1);
	
		player->Move(0, -1, entireMapChar);
		
		moved = true;
		//Beep(1440, 30);
	}
	if (g_abKeyPressed[K_LEFT])
	{
		player->SetDirection(-1, 0);
	
		player->Move(-1, 0, entireMapChar);
		
		//Beep(1440, 30);
		moved = true;
	}
	if (g_abKeyPressed[K_DOWN])
	{
		player->SetDirection(0, 1);
		player->Move(0, 1, entireMapChar);
		
		//Beep(1440, 30);
		moved = true;
	}
	if (g_abKeyPressed[K_RIGHT])
	{
		player->SetDirection(1, 0);
		player->Move(1, 0, entireMapChar);
		
		moved = true;
	}
	return moved;
}
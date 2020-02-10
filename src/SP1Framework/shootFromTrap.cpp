#include "ShootFromTrap.h"
double shootdelay = 0;
extern double g_dElapsedTime;
extern std::vector <Trap> allTraps;


void ShootFromTrap(Character* curPlayer, Entity** mapdata, irrklang::ISoundEngine* engine, irrklang::ISoundSource* M_injured, irrklang::ISoundSource* S_injured, Console& g_Console) {

		// Loop through the allTraps
		for (int i = 0; i < (int)allTraps.size(); i++) {
			// Check if the bullet hits a wall, if it hits the wall, the bullet will go back to the original trap it came from.
			if (mapdata[allTraps[i].bulletForTrap->m_Position.Y][allTraps[i].bulletForTrap->m_Position.X].m_Character == curPlayer->m_Character)
			{
				// Killer Takes Damage
				curPlayer->TakeDamage(allTraps[i].TrapDamage);
				engine->play2D(S_injured);
			}

			if (shootdelay < g_dElapsedTime) {
				//Delay for shooting, Also shooting, sets the position of bullet to make it move
				allTraps[i].bulletForTrap->m_Position.X += allTraps[i].dir.X;
				allTraps[i].bulletForTrap->m_Position.Y += allTraps[i].dir.Y;				
			}
			//if not a blank space
			if (mapdata[allTraps[i].bulletForTrap->m_Position.Y][allTraps[i].bulletForTrap->m_Position.X].m_Character != 32) {
				
				if (mapdata[allTraps[i].bulletForTrap->m_Position.Y][allTraps[i].bulletForTrap->m_Position.X].m_Character == curPlayer->m_Character)
				{
					// Killer Takes Damage
					curPlayer->TakeDamage(allTraps[i].TrapDamage);
					engine->play2D(S_injured);
				}
				// Actual shooting from traps, sets the position of bullet to make it move
				allTraps[i].bulletForTrap->m_Position.X = allTraps[i].pos.X;
				allTraps[i].bulletForTrap->m_Position.Y = allTraps[i].pos.Y;
			}

		}
		// Delay for shooting
		if (shootdelay < g_dElapsedTime) {
			shootdelay = g_dElapsedTime + 0.25;
		}
	

	
	for (int i = 0; i < (int)allTraps.size(); i++) {
		g_Console.writeToBuffer(allTraps[i].bulletForTrap->m_Position, (char)248, 0xF);
	}
}

void ShootFromTrap(Character* playerOne,Character* playerTwo,Entity** mapdata,irrklang::ISoundEngine* engine, irrklang::ISoundSource* M_injured, irrklang::ISoundSource* S_injured,Console& g_Console) {

	
		// Loop through the allTraps
		for (int i = 0; i < (int)allTraps.size(); i++) {
			// Check if the bullet hits a wall, if it hits the wall, the bullet will go back to the original trap it came from.
			if (mapdata[allTraps[i].bulletForTrap->m_Position.Y][allTraps[i].bulletForTrap->m_Position.X].m_Character == E_PLAYERONE.m_Character)
			{
				// Killer Takes Damage
				playerOne->TakeDamage(allTraps[i].TrapDamage);
				engine->play2D(M_injured);
				if (playerOne->m_CharHealth <= 0) {
					//g_bQuitGame = true;
				}
			}

			if (mapdata[allTraps[i].bulletForTrap->m_Position.Y][allTraps[i].bulletForTrap->m_Position.X].m_Character == E_PLAYERTWO.m_Character)
			{
				// Survivor Takes Damage
				playerTwo->TakeDamage(allTraps[i].TrapDamage);
				engine->play2D(S_injured);
				if (playerTwo->m_CharHealth <= 0) {
					//g_bQuitGame = true;
				}

			}

			if (shootdelay < g_dElapsedTime) {
				allTraps[i].bulletForTrap->m_Position.X += allTraps[i].dir.X;
				allTraps[i].bulletForTrap->m_Position.Y += allTraps[i].dir.Y;
			}

			if (mapdata[allTraps[i].bulletForTrap->m_Position.Y][allTraps[i].bulletForTrap->m_Position.X].m_Character != 32) {
				if (mapdata[allTraps[i].bulletForTrap->m_Position.Y][allTraps[i].bulletForTrap->m_Position.X].m_Character == E_PLAYERONE.m_Character)
				{
					// Killer Takes Damage
					playerOne->TakeDamage(allTraps[i].TrapDamage);
					engine->play2D(M_injured);
					if (playerOne->m_CharHealth <= 0) {
						//g_bQuitGame = true;
					}
				}

				if (mapdata[allTraps[i].bulletForTrap->m_Position.Y][allTraps[i].bulletForTrap->m_Position.X].m_Character == E_PLAYERTWO.m_Character)
				{
					// Survivor Takes Damage
					playerTwo->TakeDamage(allTraps[i].TrapDamage);
					engine->play2D(S_injured);
					if (playerTwo->m_CharHealth <= 0) {
						//g_bQuitGame = true;
					}

				}
				// Actual shooting from traps, sets the position of bullet to make it move
				allTraps[i].bulletForTrap->m_Position.X = allTraps[i].pos.X;
				allTraps[i].bulletForTrap->m_Position.Y = allTraps[i].pos.Y;

			}
						
		}
		//Delay for shooting
		if (shootdelay < g_dElapsedTime) {
			shootdelay = g_dElapsedTime + 0.25;
		}


	//Draws the bullet
	
}
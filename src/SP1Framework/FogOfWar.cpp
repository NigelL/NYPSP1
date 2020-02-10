#include "FogOfWar.h"

double darkcooldown;
double darkcd;
bool DARK = false;
bool DARKDARK = false;

void Normal(Entity** entireMapChar,Console& g_Console,bool completed) {
	for (int i = 0; i < 42; i++) {
		for (int j = 0; j < 180; j++) {
			COORD spotlightkiller;
			spotlightkiller.Y = i;
			spotlightkiller.X = j;

			if (entireMapChar[i][j].IDENTIFIER == 1)
				entireMapChar[i][j].m_ColorInHex = 0x4;


			if (completed && entireMapChar[i][j] == E_GENERATOR)
			{
				entireMapChar[i][j] = E_BLANK;
			}

			g_Console.writeToBuffer(spotlightkiller, entireMapChar[i][j].m_Character, entireMapChar[i][j].m_ColorInHex);

		}
	}
}

void Spotlight(Character playerOne,Character playerTwo,Entity** entireMapChar,Console& g_Console,bool g_abKeyPressed[],double* g_dElapsedTime,bool completed) {

	// Making the killer's ability to remove the spotlight for the survivor

	// COOLDOWN FOR SKILL
	if (DARKDARK == false) {
		if (g_abKeyPressed[K_DARK]) {
			DARK = true;
			DARKDARK = true;
			darkcd = *g_dElapsedTime + 3;
			darkcooldown = *g_dElapsedTime + 8;
			RenderInstruction::RenderCoolDown(7, *g_dElapsedTime, "BlackOut", 20);
		}
	}

	// SKILL ACTIVATES / DEACTIVATES
	if (*g_dElapsedTime >= darkcd) {
		DARK = false;
		if (*g_dElapsedTime >= darkcooldown) {
			DARKDARK = false;
		}
	}
	// PLAYER ONE (KILLER)
	// Set the vertical section of the spotlight, The first part of the loop centers player one vertically, second part makes it longer vertically.


		for (int i = playerOne.m_Position.Y - 3; i < playerOne.m_Position.Y + 6; i++) {
			// Set the horizontal section of the spotlight, The first part of the loop increases width to the left, second part increases width to the right.
			for (int j = playerOne.m_Position.X - 7; j < playerOne.m_Position.X + 8; j++) {
				if (i < 0 || i > 41 || j < 0 || j > 179)
				{
					continue;
				}
				COORD spotlightkiller;
				spotlightkiller.Y = i;
				spotlightkiller.X = j;
				if (entireMapChar[i][j].IDENTIFIER == 1)
					entireMapChar[i][j].m_ColorInHex = 0x4;
				if (completed && entireMapChar[i][j] == E_GENERATOR)
				{
					entireMapChar[i][j] = E_BLANK;
				}

				g_Console.writeToBuffer(spotlightkiller, entireMapChar[i][j].m_Character, entireMapChar[i][j].m_ColorInHex);
				
				
			}
		}
	


	// PLAYER TWO (SURVIVOR)
	// Set the vertical section of the spotlight, The first part of the loop centers player one vertically, second part makes it longer vertically.
		if (DARK == false)
		{
			for (int i = playerTwo.m_Position.Y - 3; i < playerTwo.m_Position.Y + 6; i++) {
				// Set the horizontal section of the spotlight, The first part of the loop increases width to the left, second part increases width to the right.
				for (int j = playerTwo.m_Position.X - 7; j < playerTwo.m_Position.X + 8; j++) {
					if (i < 0 || i > 41 || j < 0 || j > 179)
					{
						continue;
					}
					COORD spotlightsurvivor;
					spotlightsurvivor.Y = i;
					spotlightsurvivor.X = j;
					if (entireMapChar[i][j].IDENTIFIER == 1)
						entireMapChar[i][j].m_ColorInHex = 0x4;

					if (completed && entireMapChar[i][j] == E_GENERATOR)
					{
						entireMapChar[i][j] = E_BLANK;
					}
					g_Console.writeToBuffer(spotlightsurvivor, entireMapChar[i][j].m_Character, entireMapChar[i][j].m_ColorInHex);
					
					

				
				}
			}
		}
}
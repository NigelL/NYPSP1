#include "SurvivorAbility.h"
#include "PathFinding.h"

void renderRotation(COORD coord, COORD startCOORD, COORD dirCOORD, COORD prevDirCOORD);
int pressCount = 0;
bool metgenerator = false;
double timeToMeet = 0;
extern EGAMESTATES g_eGameState;

bool generatorCheck(Character* playerTwo, bool g_abKeyPressed[], Entity** entireMapChar)
{
	bool check = false;

	if (entireMapChar[playerTwo->m_dirY + playerTwo->m_Position.Y][playerTwo->m_dirX + playerTwo->m_Position.X].m_Character == 234)
	{
		if (g_abKeyPressed[K_W])
		{
			metgenerator = true;
			check = true;
		}
	}
	return check;
}
bool generatorGame(Character* playerTwo, bool g_abKeyPressed[], Entity** entireMapChar,double g_dElapsedTime,bool* suspended,int* numOfGenerator)
{
	bool complete = false;

	if (entireMapChar[playerTwo->m_dirY + playerTwo->m_Position.Y][playerTwo->m_dirX + playerTwo->m_Position.X].m_Character == 234)
	{
		if (g_abKeyPressed[K_W])
		{
			pressCount++;
			metgenerator = true;
			if (timeToMeet == 0)
				timeToMeet = g_dElapsedTime + 6;
		}
	}
	if (metgenerator) {
		if (*numOfGenerator == 0 && pressCount >= 5 && g_dElapsedTime < timeToMeet) {
			entireMapChar[playerTwo->m_dirY + playerTwo->m_Position.Y][playerTwo->m_dirX + playerTwo->m_Position.X] = E_BLANK;
			pressCount = 0;
			timeToMeet = 0;
			*(numOfGenerator) += 1;
			metgenerator = false;
			complete = true;
		}
		else if (*numOfGenerator >= 1 && pressCount >= 10 && g_dElapsedTime < timeToMeet) {
			entireMapChar[playerTwo->m_dirY + playerTwo->m_Position.Y][playerTwo->m_dirX + playerTwo->m_Position.X] = E_BLANK;
			pressCount = 0;
			timeToMeet = 0;
			*(numOfGenerator) += 1;
			metgenerator = false;
			complete = true;
		}
		else if (*numOfGenerator >= 2 && pressCount >= 15 && g_dElapsedTime < timeToMeet) {
			entireMapChar[playerTwo->m_dirY + playerTwo->m_Position.Y][playerTwo->m_dirX + playerTwo->m_Position.X] = E_BLANK;
			pressCount = 0;
			timeToMeet = 0;
			metgenerator = false;
			*(numOfGenerator) += 1;
			complete = true;
		}
		else if (g_dElapsedTime > timeToMeet) {
			pressCount = 0;
			timeToMeet = 0;
			metgenerator = false;
			*suspended = false;
			return false;
		}
		if (g_abKeyPressed[K_F])
		{
			pressCount = 0;
			timeToMeet = 0;
			metgenerator = false;
			*suspended = false;
			return false;
		}
	}
	return complete;
}

double placeCooldown;
bool Place = false;

bool place(Character* playerTwo,bool g_abKeyPressed[], Entity** entireMapChar, double g_dElapsedTime, irrklang::ISoundEngine* engine, irrklang::ISoundSource* Rotating)
{
	bool placed = false;

	if (g_dElapsedTime >= placeCooldown)
		Place = false;

	if (g_abKeyPressed[K_R])
	{
		if (entireMapChar[playerTwo->m_dirY + playerTwo->m_Position.Y][playerTwo->m_dirX + playerTwo->m_Position.X].m_Character == ' ')
		{
			if (Place == false)
			{
				entireMapChar[playerTwo->m_dirY + playerTwo->m_Position.Y][playerTwo->m_dirX + playerTwo->m_Position.X] = E_WALL;
				//grid[playerTwo->m_dirY + playerTwo->m_Position.Y][playerTwo->m_dirX + playerTwo->m_Position.X].obstacle = true;
				Place = true;
				placeCooldown = g_dElapsedTime + 5;
				placed = true;
			}
		}
	}
	return placed;
}

bool rotate(Character* playerTwo,bool g_abKeyPressed[],Entity** entireMapChar,double g_dElapsedTime, irrklang::ISoundEngine* engine, irrklang::ISoundSource* Rotating)
{
	bool rotated = false;

	if (g_abKeyPressed[K_R])
	{
		if (!Place) {
			Rotating->setDefaultVolume(0.2f);

			engine->play2D(Rotating);
			COORD c, dirC, prevDirC;

			dirC.X = playerTwo->m_dirX;
			dirC.Y = playerTwo->m_dirY;
			prevDirC.X = playerTwo->m_prevDirX;
			prevDirC.Y = playerTwo->m_prevDirY;

			c.X = playerTwo->m_Position.X + dirC.X;
			c.Y = playerTwo->m_Position.Y + dirC.Y;
			if (entireMapChar[c.Y][c.X].m_Character == 219) {
				renderRotation(c, c, dirC, prevDirC);
				placeCooldown = g_dElapsedTime + 5;
			}
			Place = true;
		
			rotated = true;
		}
	}
	return rotated;
}
bool sAttack(Character* playerTwo, Character* playerOne, bool g_abKeyPressed[], Entity** entireMapChar, irrklang::ISoundEngine* engine, irrklang::ISoundSource* Melee, irrklang::ISoundSource* M_injured)
{
	bool attack = false;

	if (entireMapChar[playerTwo->m_dirY + playerTwo->m_Position.Y][playerTwo->m_dirX + playerTwo->m_Position.X].m_Character == E_PLAYERONE.m_Character)
	{
		if (g_abKeyPressed[K_F])
		{
			Melee->setDefaultVolume(0.2f);
			engine->play2D(Melee);
			M_injured->setDefaultVolume(0.2f);
			engine->play2D(M_injured);

			playerOne->TakeDamage(playerTwo->m_damage);
			if (playerOne->m_CharHealth <= 0)
			{
				entireMapChar[playerTwo->m_dirY + playerTwo->m_Position.Y][playerTwo->m_dirX + playerTwo->m_Position.X] = E_BLANK;
				g_eGameState = S_WINNERSCREEN;
				//g_bQuitGame = true;
			}
			attack = true;
		}
	}

	return attack;
}


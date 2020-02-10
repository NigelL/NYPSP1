#include "KillerAbility.h"

#include "Projectile.h"


extern double g_dBounceTime;
extern double g_dElapsedTime;

double breakCooldown;
PROJECTILE bullet;
bool Break = false;
double bulletdelay = 0;


extern EGAMESTATES g_eGameState;

bool breakWall(Character* playerOne,bool g_abKeyPressed[],double g_dElapsedTime,Entity** entireMapChar, irrklang::ISoundEngine* engine, irrklang::ISoundSource* Dig, ParticleSystem& particleSystem )
{
	bool BREAK = false;

	if (g_dElapsedTime >= breakCooldown)
		Break = false;
	if (entireMapChar[playerOne->m_dirY + playerOne->m_Position.Y][playerOne->m_dirX + playerOne->m_Position.X] == E_WALL )
	{

		if (g_abKeyPressed[K_BREAK])
		{
			if (Break == false)
			{
				Dig->setDefaultVolume(0.2f);

				engine->play2D(Dig);
				entireMapChar[playerOne->m_dirY + playerOne->m_Position.Y][playerOne->m_dirX + playerOne->m_Position.X] = E_BLANK;
				//grid[playerOne->m_dirY + playerOne->m_Position.Y][playerOne->m_dirX + playerOne->m_Position.X].obstacle = false;
				COORD playerC = { playerOne->m_dirX,playerOne->m_dirY };
				COORD startParticle = { playerOne->m_dirX + playerOne->m_Position.X,playerOne->m_dirY + playerOne->m_Position.Y };
				particleSystem.StartParticles(startParticle, playerC, g_dElapsedTime,false);
				BREAK = true;
				Break = true;
				breakCooldown = g_dElapsedTime + 7;
			}
		}
	}

	return BREAK;
}

bool kAttack(Character* playerOne, Character* playerTwo, bool g_abKeyPressed[], Entity** entireMapChar, irrklang::ISoundEngine* engine, irrklang::ISoundSource* S_injured)
{
	bool attack = false;

	if (entireMapChar[playerOne->m_dirY + playerOne->m_Position.Y][playerOne->m_dirX + playerOne->m_Position.X].m_Character == E_PLAYERTWO.m_Character)
	{

		if (g_abKeyPressed[K_KATTACK])
		{
			S_injured->setDefaultVolume(0.8f);
			playerTwo->TakeDamage(playerOne->m_damage);
			engine->play2D(S_injured);
			if (playerTwo->m_CharHealth <= 0)
			{
				entireMapChar[playerOne->m_dirY + playerOne->m_Position.Y][playerOne->m_dirX + playerOne->m_Position.X] = E_BLANK;
				g_eGameState = S_WINNERSCREEN;
				attack = true;
				//g_bQuitGame = true;
			}
			attack = true;
		}
	}

	return attack;
}
void kShoot(Character playerOne, bool g_abKeyPressed[])
{

	if (g_dElapsedTime > g_dBounceTime)
	{
		if (g_abKeyPressed[K_SHOOT])
		{
			bullet.SetPosition(playerOne.m_Position.X + playerOne.m_dirX, playerOne.m_Position.Y + playerOne.m_dirY);
		}
		
	}


}
void renderBullet(Character playerOne, Character* playerTwo, Console& g_Console, Entity** entireMapChar)
{
	if (bullet.projectileCoord.X != 185 && entireMapChar[bullet.projectileCoord.Y][bullet.projectileCoord.X] == E_BLANK)
	{
		g_Console.writeToBuffer(bullet.projectileCoord, (char)248, 0x09);
		if (g_dElapsedTime > bulletdelay)
		{
			bullet.move(playerOne.m_dirX, playerOne.m_dirY);
			bulletdelay = g_dElapsedTime + 0.1;
		}
	}
	else
	{
		if (bullet.projectileCoord.X != 185 && entireMapChar[bullet.projectileCoord.Y][bullet.projectileCoord.X].m_Character == E_PLAYERTWO.m_Character)
		{
			playerTwo->TakeDamage(50);
			if (playerTwo->m_CharHealth <= 0)
			{
				entireMapChar[bullet.projectileCoord.Y][bullet.projectileCoord.X] = E_BLANK;
				g_eGameState = S_WINNERSCREEN;
				//g_bQuitGame = true;
			}

		}
		bullet.projectileCoord.X = 185;
		bullet.projectileCoord.Y = 56;

	}
}
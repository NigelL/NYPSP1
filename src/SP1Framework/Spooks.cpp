#include "game.h"
#include "Spooks.h"
#include "Values.h"

extern std::vector<Particle> allParticles;
extern EGAMESTATES g_eGameState;
bool charge = false;
COORD c, dirC, prevDirC;
bool Charge(Character* playerTwo, Character* playerOne, bool g_abKeyPressed[], Entity** entireMapChar, irrklang::ISoundEngine* engine, irrklang::ISoundSource* M_injured, irrklang::ISoundSource* rotating, double& dt) {



	
	if (g_abKeyPressed[K_Q] || dirC.X == 0) {
		dirC.X = playerTwo->m_dirX;
		dirC.Y = playerTwo->m_dirY;
		prevDirC.X = playerTwo->m_prevDirX;
		prevDirC.Y = playerTwo->m_prevDirY;
		
	}

		/*if (entireMapChar[playerTwo->m_Position.Y + dirC.Y][playerTwo->m_Position.X + dirC.X] == 7)
		{
		playerTwo->Move(0, 0);
		}*/

		if (entireMapChar[playerTwo->m_Position.Y + dirC.Y][playerTwo->m_Position.X + dirC.X].IDENTIFIER != 1) {

			if (entireMapChar[playerTwo->m_Position.Y + dirC.Y][playerTwo->m_Position.X + dirC.X].m_Character  == E_PLAYERONE.m_Character ) {
				playerOne->TakeDamage(playerOne->m_CharHealth);
				if (playerOne->m_CharHealth <= 0)
				{
					M_injured->setDefaultVolume(0.28f);
					engine->play2D(M_injured);
					entireMapChar[playerTwo->m_dirY + playerTwo->m_Position.Y][playerTwo->m_dirX + playerTwo->m_Position.X] = E_BLANK;
					g_eGameState = S_WINNERSCREEN;
					//g_bQuitGame = true;
				}
				charge = true;
			}
			else {
				
				for (int i = -5; i < 5; i++) {
					for (int j = -5; j < 5; j++) {
						if (playerTwo->m_Position.Y + i < 2 || playerTwo->m_Position.X+ j < 2 || playerTwo->m_Position.Y + i > 41 || playerTwo->m_Position.X + j > 178) {
							continue;
						}
						if (entireMapChar[playerTwo->m_Position.Y + i][playerTwo->m_Position.X + j] == E_WALL) {
							entireMapChar[playerTwo->m_Position.Y + i][playerTwo->m_Position.X + j] = E_BLANK ;
							COORD currPart = { (SHORT)playerTwo->m_Position.X + (SHORT)j ,(SHORT)playerTwo->m_Position.Y + (SHORT)i };
							Particle explosionParticle = Particle(Entity(currPart, 219, 0x04), COORD{ 2 - ((rand() % 3) + 1) ,2 - ((rand() % 3) + 1) });
							explosionParticle.m_Speed.X *= 2;
							explosionParticle.m_Speed.Y *= 2;
							explosionParticle.identifier = Explosion;
							explosionParticle.particle.m_Character = 219;
							explosionParticle.lifeTime = dt + 2;
							allParticles.push_back(explosionParticle);
							engine->play2D(rotating);
						}
					}

				}
				
			}
			

			playerTwo->Move(dirC.X, dirC.Y, entireMapChar);
		}
		

		return true;
}
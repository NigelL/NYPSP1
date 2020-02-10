//player position , time , map data
#include "commet.h"
#include "Values.h"
#include "game.h"


extern std::vector<Particle> allParticles;
extern Character playerOne;
ParticleSystem commetSystem;
bool commetAlready;
double timeRunning = -1;

std::vector<COORD> allExplosionCOORD;

void Commet(Entity** mapData, Character& commet,bool keyPressed[], double elapsedTime) {
	//from character position we expand check if it exceeds the boundary
	//we find the data to explode   1
	//then we can make them fly once the timer is up 
	// if survivor or killer is there then - 3 hearts 99 100 
	
		for (int i = -5; i < 5; i++)
		{
			for (int j = -10; j < 10; j++)
			{
				if (commet.m_Position.Y + i < 2 || commet.m_Position.X + j < 2 || commet.m_Position.Y + i > 41 || commet.m_Position.X + j > 178) {
					continue;
				}
				COORD currPart = { (SHORT)commet.m_Position.X + (SHORT)j ,(SHORT)commet.m_Position.Y + (SHORT)i };
				if (!commetAlready) {
					if (mapData[commet.m_Position.Y + i][commet.m_Position.X + j] == E_WALL)
					{						
						Particle explosionParticle = Particle(Entity(currPart, 219, 0x04), COORD{ 2 - ((rand() % 3) + 1) ,2 - ((rand() % 3) + 1) });
						explosionParticle.identifier = Explosion;

						explosionParticle.particle.m_Character = 219;

						commetSystem.particlesToAnimate.push_back(explosionParticle);
					

					}
					allExplosionCOORD.push_back(currPart);
				}
				
				


			}
		
	}
		if (elapsedTime > timeRunning) {
			timeRunning = elapsedTime + 5;
			RenderInstruction::RenderCoolDown(4, elapsedTime, "Commet",100);
			
			commetAlready = true;
		}
	
}

void CometUpdate(Entity** mapData , const double& dt, irrklang::ISoundEngine* engine, irrklang::ISoundSource* boom) {
	if ( dt > timeRunning && commetAlready) {
		for (int i = 0; i < (int)allExplosionCOORD.size(); i++) {
			if (mapData[allExplosionCOORD[i].Y][allExplosionCOORD[i].X].m_Character == E_PLAYERONE.m_Character) {
				playerOne.TakeDamage(100);
			}
		}

		for (int i = 0; i < (int)commetSystem.particlesToAnimate.size(); i++) {
			
			
			mapData[commetSystem.particlesToAnimate[i].particle.m_Position.Y][commetSystem.particlesToAnimate[i].particle.m_Position.X] = E_BLANK;
			
			commetSystem.particlesToAnimate[i].lifeTime = dt + 2;
		}
		engine->play2D(boom);
		commetSystem.StartParticles();
		commetSystem.particlesToAnimate.clear();
		commetAlready = false;
		
	}
}
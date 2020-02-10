#pragma once
#include "Character.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "game.h"


void Commet(Entity** mapData, Character& commet, bool keyPressed[], double elapsedTime);
void CometUpdate(Entity** mapData,const double& dt, irrklang::ISoundEngine* engine, irrklang::ISoundSource* boom);
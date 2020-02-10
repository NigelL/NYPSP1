#pragma once

#include "game.h"
#include "Trap.h"

void ShootFromTrap(Character* curPlayer, Entity** mapdata, irrklang::ISoundEngine* engine, irrklang::ISoundSource* M_injured, irrklang::ISoundSource* S_injured, Console& g_Console);
void ShootFromTrap(Character* playerOne, Character* playerTwo, Entity** mapdata, irrklang::ISoundEngine* engine, irrklang::ISoundSource* M_injured, irrklang::ISoundSource* S_injured, Console& g_Console);
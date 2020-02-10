#pragma once
#include "game.h"

bool breakWall(Character* playerOne, bool g_abKeyPressed[], double g_dElapsedTime, Entity** entireMapChar, irrklang::ISoundEngine* engine, irrklang::ISoundSource* Dig, ParticleSystem& particleSystem);
bool kAttack(Character* playerOne, Character* playerTwo, bool g_abKeyPressed[], Entity** entireMapChar, irrklang::ISoundEngine* engine, irrklang::ISoundSource* S_injured);
void kShoot(Character playerOne, bool g_abKeyPressed[]);
void renderBullet(Character playerOne, Character* playerTwo, Console& g_Console, Entity** entireMapChar);
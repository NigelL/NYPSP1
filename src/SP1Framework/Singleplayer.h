#pragma once
#include "game.h"
#include "Trap.h"
#include "AI.h"
#include "killerAbility.h"
#include "Projectile.h"

void usePots(bool g_abKeyPressed[]);
void attack(bool g_abKeyPressed[], Console& g_Console);
void renderbullets(Console& g_Console);
void collectitems(bool g_abKeyPressed[]);
void doorUnlocked(irrklang::ISoundEngine* engine, irrklang::ISoundSource* gate);
void checkPoint();
void toNextLevel();
void renderSingleplayerMap(Console& g_Console);
void initSingleplayerMap();
void renderControls(Console& g_Console, Character* player);
void renderCompleted(Console& g_Console);
void cheat(bool g_abKeyPressed[]);
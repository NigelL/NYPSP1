#pragma once
#include "Character.h"

bool Charge(Character* playerTwo, Character* playerOne, bool g_abKeyPressed[], Entity** entireMapChar, irrklang::ISoundEngine* engine, irrklang::ISoundSource* M_injured, irrklang::ISoundSource* rotating, double& dt);
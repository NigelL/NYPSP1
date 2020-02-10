#pragma once
#include "game.h"
#include "Character.h"
#include "Framework\console.h"
#include "KillerMovement.h"
#include "KillerAbility.h"
#include "SurvivorMovement.h"
#include "SurvivorAbility.h"
#include "FogOfWar.h"
#include "Rotation.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
bool swordsmen(Character* playerTwo, Character* playerOne, double* addtime2, int** entireMapChar, bool g_abKeyPressed[]);
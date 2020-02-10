#pragma once

#include <iostream>
#include "game.h"
#include "PathFinding.h"
#include <vector>

void convertToAI(Character* AIone, Character* AItwo, int** entireMapChar);
std::vector <node> runPathFinder(Character playerTwo);
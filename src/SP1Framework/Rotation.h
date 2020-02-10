#pragma once
#include <Windows.h>
#include "Entity.h"
#include <vector>
void Rotate(COORD coord, COORD startCoord, COORD dirCOORD, COORD prevDirCOORD, int index, Entity** mazeData, const int boundX, const int boundY, std::vector<COORD> coordForChange);

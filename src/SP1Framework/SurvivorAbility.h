#pragma once
#include "game.h"


bool generatorCheck(Character* playerTwo, bool g_abKeyPressed[], Entity** entireMapChar);
bool generatorGame(Character* playerTwo, bool g_abKeyPressed[], Entity** entireMapChar, double g_dElapsedTime, bool* suspended, int* numOfGenerator);
bool place(Character* playerTwo, bool g_abKeyPressed[], Entity** entireMapChar, double g_dElapsedTime, irrklang::ISoundEngine* engine, irrklang::ISoundSource* Rotating);
bool rotate(Character* playerTwo, bool g_abKeyPressed[], Entity** entireMapChar, double g_dElapsedTime, irrklang::ISoundEngine* engine, irrklang::ISoundSource* Rotate);
bool sAttack(Character* playerTwo, Character* playerOne, bool g_abKeyPressed[], Entity** entireMapChar, irrklang::ISoundEngine* engine, irrklang::ISoundSource* Melee, irrklang::ISoundSource* injured);
//bool Charge(Character* playerTwo, Character* playerOne, bool g_abKeyPressed[], int** entireMapChar);
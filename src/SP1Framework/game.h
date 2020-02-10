//#ifndef _GAME_H
//#define _GAME_H
#pragma once

enum EGAMESTATES
{
	S_SINGLEPLAYER,
	S_SPLASHSCREEN,
	S_MAINMENU,
	S_INSTRUCTIONS,
	S_OPTIONS,
	S_TUTORIAL,
	S_BUILD,
	S_NULL,
	S_GAME,
	S_WINNERSCREEN,
	S_CLASSSELECTION,
	S_COMPLETEDSCREEN,
	S_COUNT
};
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <irrKlang.h>
#include <ik_IVirtualRefCounted.h>
#include "Particle.h"
#include "Framework\timer.h"
#include "Framework\console.h"
#include "Character.h"
#include "Values.h"
#include "ParticleSystem.h"
#include "KillerMovement.h"
#include "KillerAbility.h"
#include "TrapBuilder.h"
#include "SurvivorMovement.h"
#include "SurvivorAbility.h"
#include "SwitchCharacter.h"
#include "FogOfWar.h"
#include "Rotation.h"
#include "RenderInfo.h"

#include "Ezreal.h"


extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

// Enumeration to store the control keys that your game will have
enum EKEYS
{
	//Killer
	K_UP,
	K_DOWN,
	K_LEFT,
	K_RIGHT,
	K_ESCAPE,
	K_SPACE,
	K_KATTACK,
	K_BREAK,
	K_DARK,
	K_SHOOT,

	//Survivor
	K_W,
	K_S,
	K_A,
	K_D,
	K_R,
	K_Q,
	K_E,
	K_F,
	K_TAB,
	K_M1,
	K_M2,
	K_ONE,
	K_TWO,
	K_THREE,
	K_FOUR,

	//Additional Keys for Singleplayer
	K_G,//Collect
	K_H,//Use healthpots
	K_J,//shoot
	K_K,//melee
	K_CHEAT,
	K_COUNT
};
// Enumeration for the different screen states

// struct for the game character
struct SGameChar
{
    COORD m_cLocation;
    bool  m_bActive;
};

void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory
void renderWinScreen();
void renderTutorial();
void splashScreenWait();    // waits for time to pass in splash screen
void gameplay();            // gameplay logic
void moveCharacter();       // moves the character, collision detection, physics, etc
void clearScreen();         // clears the current screen and draw from scratch 
void renderGame();          // renders the game stuff
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void LoadCharacters();
void singleplayerGameplay();
void resetMultiplayer();
void resetSingleplayer();
void resetTutorial();
void processInput();
// _GAME_H
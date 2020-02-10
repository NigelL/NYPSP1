// This is the main file for the game logic and function
#include "game.h"
#include "PathFinding.h"
#include "PresetParticles.h"
#include "BinaryHeap.h"
#include "commet.h"
#include "Spooks.h"
#include "Singleplayer.h"
#include "Trap.h"
#include "ShootFromTrap.h"
#include "RenderInstruction.h"
#include "RenderMainMenu.h"
#include "RenderClassSelection.h"
#include "RenderTitleScreen.h"
#include <cctype>
#include "AI.h"

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

std::vector<Entity*> allEntity;

//Maps
Entity** singleplayerMap;
Entity** entireMapChar; //0 - blank 1 - wall   entireMapChar[y][x] = 0;
std::string MAZE = "Mazes/maze";
std::string EXTENSION = ".txt";
int MAPNUM = rand() % 3 + 1;

//Sounds Variables
irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
irrklang::ISoundSource* Melee = engine->addSoundSourceFromFile("OST/MeleeAttack.wav");
irrklang::ISoundSource* bgm = engine->addSoundSourceFromFile("OST/gamebgm.wav");
irrklang::ISoundSource* menu = engine->addSoundSourceFromFile("OST/menu.wav");
irrklang::ISoundSource* Dig = engine->addSoundSourceFromFile("OST/WallBreak.wav");
irrklang::ISoundSource* Rotating = engine->addSoundSourceFromFile("OST/PlaceBlock.wav");
irrklang::ISoundSource* S_injured = engine->addSoundSourceFromFile("OST/DamagedSurvivor.wav");
irrklang::ISoundSource* weeb = engine->addSoundSourceFromFile("OST/weeb1.wav");
irrklang::ISoundSource* M_injured = engine->addSoundSourceFromFile("OST/DamagedMonster.wav");
irrklang::ISoundSource* gate = engine->addSoundSourceFromFile("OST/gate.wav");
irrklang::ISoundSource* boom = engine->addSoundSourceFromFile("OST/explosion.wav");
irrklang::ISoundSource* solo = engine->addSoundSourceFromFile("OST/solo.wav");

// Game specific variables here
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once
double g_dBounceTime2;
double particleBounceTime;

// Console object
Console g_Console(180, 52, "Revenge of the Shade");
choice chosenChoice;

//Characters
Character playerOne = Character(200,50);
Character playerTwo = Character(100,0);
Character player(100, 25);

//Particles
std::vector<Particle> allParticles;
ParticleSystem breakWalls;
ParticleSystem ezRealParticle;

//General Variables
bool single = false;
bool suspended = false;
bool once = false;
double addtime = 0.25;
double addtime2 = 0.25;
bool finishedRendering = false;
bool renderSpotlightMap = true;
std::vector<Heap<node>> heapTest;

//Variables for AI
std::vector<AI*> allAI;
double AIUpdate;

//Variables for Generators
bool completed = false;
int numOfCompletion = 0;

//Variables for Traps
std::vector<Trap> allTraps;


//Variables for Skill
bool usedOnce = false;

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput(void)
{
	g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);

	//Controls for playerOne (Killer)
	g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
	g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_KATTACK] = isKeyPressed(0xDE); // "quotes" Button
	g_abKeyPressed[K_BREAK] = isKeyPressed(0x4C); // "L" Button
	g_abKeyPressed[K_DARK] = isKeyPressed(0xBA); // ";" Button
	g_abKeyPressed[K_SHOOT] = isKeyPressed(0x50);
	//Controls for playerTwo (Survivor)
	g_abKeyPressed[K_W] = isKeyPressed(0x57);
	g_abKeyPressed[K_S] = isKeyPressed(0x53);
	g_abKeyPressed[K_A] = isKeyPressed(0x41);
	g_abKeyPressed[K_D] = isKeyPressed(0x44);
	g_abKeyPressed[K_R] = isKeyPressed(0x52);//Rotate/Place wall
	g_abKeyPressed[K_Q] = isKeyPressed(0x51);//Use ability One
	g_abKeyPressed[K_E] = isKeyPressed(0x45);//use ability Two
	g_abKeyPressed[K_F] = isKeyPressed(0x46);//Attack
	g_abKeyPressed[K_M1] = isKeyPressed(0x1);//mouse left click
	g_abKeyPressed[K_M2] = isKeyPressed(0x2);//mouse right click
	g_abKeyPressed[K_TAB] = isKeyPressed(0x09); // Switch wall type
	g_abKeyPressed[K_ONE] = isKeyPressed(0x31);
	g_abKeyPressed[K_TWO] = isKeyPressed(0x32);
	g_abKeyPressed[K_THREE] = isKeyPressed(0x33);
	g_abKeyPressed[K_FOUR] = isKeyPressed(0x34);

	//Additional Key needed for singleplayer
	g_abKeyPressed[K_G] = isKeyPressed(0x47); //Collect items
	g_abKeyPressed[K_H] = isKeyPressed(0x48); //use healthpots
	g_abKeyPressed[K_J] = isKeyPressed(0x4A); //Shoot
	g_abKeyPressed[K_K] = isKeyPressed(0x4B); //Melee
	g_abKeyPressed[K_CHEAT] = isKeyPressed(0xBB); //Melee
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
	// get the delta time
	g_dElapsedTime += dt;
	g_dElapsedTime += dt;
	g_dDeltaTime = dt;

	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: splashScreenWait(); // game logic for the splash screen
		break;
	case S_SINGLEPLAYER: singleplayerGameplay();
		break;
	case S_TUTORIAL: gameplay();
		break;
	case S_GAME: gameplay();//gameplay(); // gameplay logic when we are in the game
		break;
	}
}
//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
	clearScreen();// clears the current screen and draw from scratch 
	switch (g_eGameState)
	{
	case S_MAINMENU: renderMainMenu(g_Console, g_eGameState, g_abKeyPressed, engine, bgm, solo);
		break;
	case S_INSTRUCTIONS: renderInstruction(g_Console, g_eGameState, g_abKeyPressed);
		break;
	case S_SINGLEPLAYER: renderSingleplayerMap(g_Console);
		break;
	case S_COMPLETEDSCREEN: renderCompleted(g_Console);
		break;
	case S_TUTORIAL:renderTutorial();
		break;
	case S_GAME:renderGame();
		break;
	case S_SPLASHSCREEN:renderTitleScreen(g_Console);
		break;
	case S_WINNERSCREEN: renderWinScreen();
		break;
	case S_CLASSSELECTION: renderClassSelection(g_Console, g_eGameState, g_abKeyPressed);
		break;

	}
	renderFramerate();  // renders debug information, frame rate, elapsed time, etc
	renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------

void SetupTutorial() {
	allTraps.clear();
	std::string line;
	std::fstream file("MainMenu/tutorial.txt");

	int index = 0;
	if (file.is_open()) {
		while (!file.eof()) {
			std::getline(file, line);
			for (int i = 0; i < (int)line.length(); i++) {

				entireMapChar[index][i].m_Character = line[i];
				entireMapChar[index][i].m_Position = COORD{ (short)i ,(short)index };
				entireMapChar[index][i].m_ColorInHex = 0x09;
				if (std::isspace(line[i])) {
					entireMapChar[index][i] = E_BLANK;
				}
				switch (entireMapChar[index][i].m_Character) {
				case '#':
					entireMapChar[index][i] = E_WALL;
					break;
				case '0':
					entireMapChar[index][i] = E_GENERATOR;
					break;

				case '>':


					allTraps.push_back(Trap({ (short)1 , (short)0 }, entireMapChar[index][i].m_Position, new Entity(COORD{ (short)i,(short)index }, '°', 0x2), 50));
					entireMapChar[index][i] = E_RIGHTTRAP;

					break;
				case '<':

					allTraps.push_back(Trap({ (short)-1 , (short)0 }, entireMapChar[index][i].m_Position, new Entity(COORD{ (short)i,(short)index }, '°', 0x2), 50));
					entireMapChar[index][i] = E_LEFTTRAP;

					break;
				case 'D':

					allTraps.push_back(Trap({ (short)0 , (short)1 }, entireMapChar[index][i].m_Position, new Entity(COORD{ (short)i,(short)index }, '°', 0x2), 50));
					entireMapChar[index][i] = E_DOWNTRAP;
					break;
				case 'U':
					allTraps.push_back(Trap({ (short)0 , (short)-1 }, entireMapChar[index][i].m_Position, new Entity(COORD{ (short)i,(short)index }, '°', 0x2), 50));
					entireMapChar[index][i] = E_UPTRAP;
					break;
				case '8':
					entireMapChar[index][i].m_Character = (char)219;
					entireMapChar[index][i].m_ColorInHex = 0x4;
					entireMapChar[index][i].IDENTIFIER = 1;
					break;
				case 'K':
					playerOne.m_Position = COORD{ (short)i, (short)index };
					entireMapChar[index][i].m_Character = (char)4;
					entireMapChar[index][i].m_ColorInHex = 0x09;
					break;
				case 'S':

					playerTwo.m_Position = COORD{ (short)i, (short)index };
					entireMapChar[index][i].m_Character = (char)6;
					entireMapChar[index][i].m_ColorInHex = 0x0A;
					break;

				case 'A':
					AI *currAI = new AI();
					currAI->m_Position = COORD{ (short)i,(short)index };
					currAI->m_Character = 'A';
					currAI->m_ColorInHex = 0x4;
					currAI->m_curState = Patrol;
					currAI->m_Target = &playerTwo;

					allAI.push_back(currAI);
					allEntity.push_back(currAI);

					break;
				}

			}//27 X 43Y
			index++;
		}
	}
	file.close();
}


void initMap()
{
	srand((unsigned int)time(NULL));
	MAPNUM = rand() % 4 + 1;

	usedOnce = false;
	//chosenChoice = NULLCHOICE;
	playerTwo.m_damage = 0;
	std::string line;
	std::fstream file(MAZE + std::to_string(MAPNUM) + EXTENSION);
	int index = 0;
	if (file.is_open()) {
		while (!file.eof()) {
			std::getline(file, line);
			for (int i = 0; i < (int)line.length(); i++) {
				
				entireMapChar[index][i].m_Character = line[i];
				entireMapChar[index][i].m_Position = COORD{ (short)i ,(short)index };
				entireMapChar[index][i].m_ColorInHex = 0x0;
				if (std::isspace(line[i])) {					
					entireMapChar[index][i] = E_BLANK;
				}
				switch (entireMapChar[index][i].m_Character) {
				case '#':
					entireMapChar[index][i] = E_WALL;
					break;			
				case '0':
					entireMapChar[index][i] = E_GENERATOR;
					break;
		
				case '>':
					 
					
					allTraps.push_back(Trap({ (short)1 , (short)0 }, entireMapChar[index][i].m_Position, new Entity(COORD{ (short)i,(short)index }, '°', 0x2), 50));
					entireMapChar[index][i] = E_RIGHTTRAP;
					
					break;
				case '<':
					
					allTraps.push_back(Trap({ (short)-1 , (short)0 }, entireMapChar[index][i].m_Position, new Entity(COORD{ (short)i,(short)index }, '°', 0x2), 50));
					entireMapChar[index][i] = E_LEFTTRAP;
					
					break;
				case 'D':
					 
					allTraps.push_back(Trap({ (short)0 , (short)1 }, entireMapChar[index][i].m_Position, new Entity(COORD{ (short)i,(short)index }, '°', 0x2), 50));
					entireMapChar[index][i] = E_DOWNTRAP;
					break;
				case 'U':					 
					allTraps.push_back(Trap({ (short)0 , (short)-1 }, entireMapChar[index][i].m_Position, new Entity(COORD{ (short)i,(short)index }, '°', 0x2), 50));
					entireMapChar[index][i] = E_UPTRAP;
					break;
				case '8':
					entireMapChar[index][i].m_Character = (char)219;
					entireMapChar[index][i].m_ColorInHex = 0x4;
					entireMapChar[index][i].IDENTIFIER = 1;
					break;
				case 'K':
					playerOne.m_Position = COORD{ (short)i, (short)index };
					entireMapChar[index][i].m_Character = (char)4;
					entireMapChar[index][i].m_ColorInHex = 0x09;
					break;
				case 'S':
				
					playerTwo.m_Position = COORD{ (short)i, (short)index };
					entireMapChar[index][i].m_Character = (char)6;
					entireMapChar[index][i].m_ColorInHex = 0x0A;
					break;
				case 'A':
					AI *currAI = new AI();
					currAI->m_Position = COORD{ (short)i,(short)index };
					currAI->m_Character = 'A';
					currAI->m_ColorInHex= 0x4;
					currAI->m_curState = Patrol;
					currAI->m_Target = &playerTwo;

					allAI.push_back(currAI);
					allEntity.push_back(currAI);

					break;				
				}

			}
			index++;
		}
	}
	file.close();
}
void init(void)
{
	// Set precision for floating point output
	srand((unsigned int)time(NULL));
	g_dElapsedTime = 0.0;
	g_dBounceTime = 0.0;

	COORD c;
	c.X = 0;
	c.Y = 0;

	for (int i = 0; i < 10; i++) {
		Heap<node> curNode;
		curNode.current = node((rand() % 15) + 1);
		InsertHeap(heapTest,curNode);
	}

	Entity breakWallsParticle = Entity(COORD{ 0, 0 }, 219, 0xF5);

	breakWalls = ParticleSystem(c, BreakWallParticleSetup(), breakWallsParticle, P_BREAKAMOUNT, P_BREAKSPEED, P_BREAKTIME,BreakWall);
	
	ezRealParticle = EzrealInIt();

	menu->setDefaultVolume(0.5f);
	engine->play2D(menu);
	LoadCharacters();

	entireMapChar = new Entity*[52];
	for (int i = 0; i < 52; i++) {
		entireMapChar[i] = new Entity[180];
	}
	// sets the initial state for the game
	g_eGameState = S_SPLASHSCREEN;

	g_Console.setConsoleFont(0, 16, L"Consolas");
}

void LoadCharacters() {
	playerOne.m_Character = (char)4;
	playerOne.m_ColorInHex = 0x0A;
	playerOne.m_CharHealth = 200;
	allEntity.push_back(&playerOne);
	playerTwo.m_Character = (char)6;
	playerTwo.m_ColorInHex = 0x0A;
	playerTwo.m_CharHealth = 100;
	allEntity.push_back(&playerTwo);
	EzrealInIt();
}

void gameplay()            // gameplay logic
{
	RenderInstruction::UpdateCoolDown();
	moveCharacter();    // moves the character, collision detection, physics, etc
	processInput();
						// sound can be played here too.
	ShootFromTrap(&playerOne,&playerTwo,entireMapChar,engine,M_injured,S_injured,g_Console);

	/*
	if (AIUpdate < g_dElapsedTime) {
		for (int i = 0; i < (int)allAI.size(); i++) {
			allAI[i]->Update(g_dElapsedTime);
		}
		AIUpdate = g_dElapsedTime + 0.5;
	}
	*/

	if (particleBounceTime < g_dElapsedTime) {
		UpdateAllParticles(g_dElapsedTime);
		particleBounceTime = g_dElapsedTime + 0.09;
	}
	
	//Check collision for individual particles from the same particle system identify them by the particle
	CheckCollisionParticles();
}

void singleplayerGameplay()
{
	if (g_dBounceTime < g_dElapsedTime)
	{
		survivorMovement(&player, g_abKeyPressed, singleplayerMap);
		usePots(g_abKeyPressed);
		attack(g_abKeyPressed, g_Console);
		collectitems(g_abKeyPressed);
		cheat(g_abKeyPressed);
		g_dBounceTime = g_dElapsedTime + 0.15;
	}
	ShootFromTrap(&player, singleplayerMap, engine, M_injured, S_injured, g_Console);
	if (AIUpdate < g_dElapsedTime) {
		for (int i = 0; i < (int)allAI.size(); i++) {
			allAI[i]->Update(g_dElapsedTime);
		}
		AIUpdate = g_dElapsedTime + 0.125;
	}
	for (int i = 0; i < (int)allAI.size(); i++)
	{
		if (allAI[i]->m_CharHealth > 0) {
			g_Console.writeToBuffer(allAI[i]->m_Position, allAI[i]->m_Character, allAI[i]->m_ColorInHex);
		}
	}
	doorUnlocked(engine, gate);
	toNextLevel();
	checkPoint();
	processInput();
}

void moveCharacter()
{
	bool bSomethingHappened = false;
	bool bSomethingHappened2 = false;

	if (playerOne.m_CharHealth <= 0 || playerTwo.m_CharHealth <= 0)
	{
		g_eGameState = S_WINNERSCREEN;
	}
	if (g_dBounceTime <= g_dElapsedTime)
	{
		//Killer Movement (Player 1)

		if (killerMovement(&playerOne, g_abKeyPressed, entireMapChar))
			bSomethingHappened = true;

		//Killer Breaking of walls(Player 1)
		if (breakWall(&playerOne, g_abKeyPressed, g_dElapsedTime, entireMapChar, engine, Dig, breakWalls)) {
			bSomethingHappened = true;
			RenderInstruction::RenderCoolDown(6, g_dElapsedTime,"Break",20);
		}

		//Killer Attacking (Player 1)
		if (kAttack(&playerOne, &playerTwo, g_abKeyPressed, entireMapChar, engine, S_injured))
			bSomethingHappened = true;

		if(completed)
			kShoot(playerOne, g_abKeyPressed);
	}
	if (g_dBounceTime2 <= g_dElapsedTime)
	{
		//Generator
		if (completed == false)
		{
			if (generatorCheck(&playerTwo, g_abKeyPressed, entireMapChar))// Check if Met with Generator
			{
				suspended = true;
				bSomethingHappened2 = true;
			}
			if (generatorGame(&playerTwo, g_abKeyPressed, entireMapChar, g_dElapsedTime, &suspended,&numOfCompletion))//Check if Generator minigame is completed
			{
				if (numOfCompletion >= 3) //Check if 3/6 generator is completed
				{
					completed = true;
					g_eGameState = S_CLASSSELECTION;
				}
				suspended = false;
				bSomethingHappened2 = true;
			}
		}
		//Player 2 Movement (Survivior)
		if (suspended == false)
		{
			if (completed)
			{
				if (sAttack(&playerTwo, &playerOne, g_abKeyPressed, entireMapChar, engine, Melee, M_injured))
				{
					bSomethingHappened2 = true;
				}
				//Handle your own class movement here
				if (survivorMovement(&playerTwo, g_abKeyPressed, entireMapChar))
					bSomethingHappened2 = true;


				if (playerTwo.m_damage == 0) {
					if (g_abKeyPressed[K_ONE])
					{
						chosenChoice = COMMET;
						switchcharacter(&playerTwo, chosenChoice);
						addtime2 = 0.25;
						renderSpotlightMap = false;					
					}
					if (g_abKeyPressed[K_TWO]) {

						chosenChoice = SWORDSMEN;
						switchcharacter(&playerTwo, chosenChoice);
						addtime2 = 0.075;
						renderSpotlightMap = false;
					}
					if (g_abKeyPressed[K_THREE]) {
						addtime2 = 0.05;
						chosenChoice = SPOOKS;
						switchcharacter(&playerTwo, chosenChoice);
						renderSpotlightMap = false;
					}
					if (g_abKeyPressed[K_FOUR]){
						addtime2 = 0.25;
						chosenChoice = EZREAL;
						switchcharacter(&playerTwo, chosenChoice);
						renderSpotlightMap = false;
					}
				}
				
				switch (chosenChoice) {
				case EZREAL:
					if (g_abKeyPressed[K_Q] && !usedOnce) {
						COORD playerTwoDir = { playerTwo.m_dirX,0 };
						COORD playerTwoPos = { -1,playerTwo.m_Position.Y - 12 };
						ezRealParticle.StartParticles(playerTwoPos, g_dElapsedTime, playerTwoDir, true);
						engine->play2D(weeb);
						bSomethingHappened2 = true;
						usedOnce = true;
						
					}
					break;
				case COMMET:
					if (g_abKeyPressed[K_Q]) {
						Commet(entireMapChar, playerTwo, g_abKeyPressed, g_dElapsedTime);
						
					}
					CometUpdate(entireMapChar, g_dElapsedTime, engine, boom);
					break;
				case SPOOKS:
						Charge(&playerTwo, &playerOne, g_abKeyPressed, entireMapChar, engine, M_injured,Rotating, g_dElapsedTime);
					break;
				}

			}
			else {
				//movement
				if (survivorMovement(&playerTwo, g_abKeyPressed, entireMapChar))
					bSomethingHappened2 = true;
			}

			//place
			if (place(&playerTwo, g_abKeyPressed, entireMapChar, g_dElapsedTime, engine, Rotating)) {
				bSomethingHappened2 = true;
				RenderInstruction::RenderCoolDown(4, g_dElapsedTime, "Place",100);
			}
			else
			{
				//rotate
				if (rotate(&playerTwo, g_abKeyPressed, entireMapChar, g_dElapsedTime, engine, Rotating)) {
					bSomethingHappened2 = true;
					RenderInstruction::RenderCoolDown(4, g_dElapsedTime, "Rotation",100);
				}
			}

		}

	}
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + addtime; // 125ms should be enough
	}
	if (bSomethingHappened2)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime2 = g_dElapsedTime + addtime2; // 125ms should be enough
	}

}

void renderTutorial()
{
	for (int i = 0; i < 52; i++) {
		for (int j = 0; j < 180; j++) {
			COORD c = { (SHORT)j,(SHORT)i };
			g_Console.writeToBuffer(c, entireMapChar[i][j].m_Character, entireMapChar[i][j].m_ColorInHex);
		}
	}

	for (int i = 0; i < (int)allTraps.size(); i++) {
		g_Console.writeToBuffer(allTraps[i].bulletForTrap->m_Position, (char)248, 0xF);
	}
	storeinsruct(g_Console,&playerOne,&playerTwo);
}

void renderWinScreen()
{
	std::string line;
	std::fstream file("MainMenu/winnerscreen.txt");
	int index = 0;
	while (!file.eof())
	{
		for (int y = 0; y < 52; y++)
		{
			std::getline(file, line);
			for (int x = 0; x <(int)line.length(); x++)
			{
				
					g_Console.writeToBuffer(x, y, line[x], 0x09);

			}
		}
	}
	file.close();
	if (playerTwo.m_CharHealth <= 0)//killer wins
	{
		g_Console.writeToBuffer(85, 19, "Killer wins", 0x2);
	}
	else//survivor wins
	{
		g_Console.writeToBuffer(85, 19, "Survivor wins", 0x2);
	}
	if (g_abKeyPressed[K_ESCAPE])
	{
		g_eGameState = S_MAINMENU;
		engine->stopAllSounds();
		engine->play2D("OST/menu.wav", true);
	}

}

void renderRotation(COORD coord, COORD startCOORD, COORD dirCOORD, COORD prevDirCOORD) {
	int index = 0;
	std::vector<COORD> receivingCOORD;

	Rotate(coord, startCOORD, dirCOORD, prevDirCOORD, index, entireMapChar, g_Console.getConsoleSize().X, g_Console.getConsoleSize().Y, receivingCOORD);
}

void renderGame()
{
	renderMap();        // renders the map to the buffer first
	if (renderSpotlightMap) {
		Spotlight(playerOne, playerTwo, entireMapChar, g_Console, g_abKeyPressed, &g_dElapsedTime,completed);//renders the spotlight
	}
	else {
		Normal(entireMapChar, g_Console,completed);
	}
	renderCharacter();  // renders the character into the buffer
	storeinsruct(g_Console, &playerOne, &playerTwo);
	for (int i = 0; i < (int)allTraps.size(); i++) {
		g_Console.writeToBuffer(allTraps[i].bulletForTrap->m_Position, (char)248, 0xF);
	}
	for (int i = 0; i < (int)allParticles.size(); i++) {
		g_Console.writeToBuffer(allParticles[i].particle.m_Position, allParticles[i].particle.m_Character, allParticles[i].particle.m_ColorInHex);
	}
	renderBullet(playerOne, &playerTwo, g_Console, entireMapChar);
}

void renderMap()
{
	for (int i = 0; i < 52; i++) {
		for (int j = 0; j < 180; j++) {
			COORD newCOORD;
			newCOORD.Y = i;
			newCOORD.X = j;
			g_Console.writeToBuffer(newCOORD, (char)219, 0x0);
		}
	}
}

void renderCharacter()
{
	// Draw the location of the character
	int index = 0;
	do {
		if (allEntity[index]->m_CharHealth > 0)
		{
			g_Console.writeToBuffer((allEntity[index])->m_Position, (allEntity[index])->m_Character, (allEntity[index])->m_ColorInHex);
		}
	} while ((++index < (int)allEntity.size()));

}

void renderFramerate()
{
	COORD c;
	// displays the framerate
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(3);
	ss << 1.0 / g_dDeltaTime << "fps";
	c.X = g_Console.getConsoleSize().X - 9;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str());

	// displays the elapsed time
	ss.str("");
	ss << g_dElapsedTime << "secs";
	c.X = 0;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str(), 0x59);
}

void renderToScreen()
{
	// Writes the buffer to the console, hence you will see what you have written
	g_Console.flushBufferToConsole();
}



void clearScreen()
{
	// Clears the buffer with this colour attribute
	g_Console.clearBuffer(0x1F);
}

void splashScreenWait()    // waits for time to pass in splash screen
{
	if (g_dElapsedTime > 4.0) // wait for 3 seconds to switch to game mode, else do nothing
		g_eGameState = S_MAINMENU;
}
//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown(void)
{
	// Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	delete[] entireMapChar;
	delete[] singleplayerMap;
	g_Console.clearBuffer();

}
void resetMultiplayer()
{
	
	allTraps.clear();
	allParticles.clear();
	allEntity.clear();
	allAI.clear();
	g_Console.clearBuffer();
	entireMapChar = new Entity*[52];
	for (int i = 0; i < 52; i++) {
		entireMapChar[i] = new Entity[180];
	}
	LoadCharacters();
	initMap();
	completed = false;
	numOfCompletion = 0;
	renderSpotlightMap = true;
	addtime2 = 0.25;
	playerOne.m_CharHealth = 200;
	playerTwo.m_CharHealth = 100;
}
void resetSingleplayer()
{
	allTraps.clear();
	allParticles.clear();
	allEntity.clear();
	allAI.clear();
	singleplayerMap = new Entity*[52];
	for (int i = 0; i < 52; i++) {
		singleplayerMap[i] = new Entity[180];
	}	

	initSingleplayerMap();
	Initializing();
}
void resetTutorial()
{
	allTraps.clear();
	allParticles.clear();
	allEntity.clear();
	allAI.clear();
	entireMapChar = new Entity*[52];
	for (int i = 0; i < 52; i++) {
		entireMapChar[i] = new Entity[180];
	}

	SetupTutorial();
}
void processInput()
{
	if (g_abKeyPressed[K_ESCAPE])
	{
		g_eGameState = S_MAINMENU;
		engine->stopAllSounds();
		engine->play2D(menu, true);
	}
}
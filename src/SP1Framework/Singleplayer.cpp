#include "Singleplayer.h"
#include "PathFinding.h"
//Initialising Variables
COORD gateCoord;
int mapNum = 49;//Number 1 in ascii 52 is 4
std::string maze = "Mazes/singleplayermap";
std::string txt = ".txt";
std::vector <PROJECTILE*> bullets;
std::vector <int> x;
std::vector <int> y;
double bulletlag = 0;
int lastIndex;
bool doorOpened = false;

//Player Abilites Variables
bool BrokeWall = false;
int breakCooldown2 = 0;
double bounceTime = 0;

//Items Variables
int healthPots = 0;
int keyFragments = 0;
bool gun = false;

extern double g_dElapsedTime;
extern Character player;
extern Entity** singleplayerMap;
extern node** grid;
extern std::vector <Trap> allTraps;
extern std::vector <AI*> allAI;
extern EGAMESTATES g_eGameState;
//extern ParticleSystem particleSystem;

//Movement reuse survivorMovement.cpp
void cheat(bool g_abKeyPressed[])
{
	if (g_abKeyPressed[K_CHEAT])
	{
		//goes to the next map
		mapNum++;
		keyFragments = 0;
		initSingleplayerMap();
	}
}
void usePots(bool g_abKeyPressed[])
{
	//Use healthPotions
	if (player.m_CharHealth < 100)
	{
		if (healthPots > 0)
		{
			if (g_dElapsedTime > bounceTime)
			{
				if (g_abKeyPressed[K_H])
				{
					healthPots--;
					player.m_CharHealth += 20;
					bounceTime = g_dElapsedTime + 0.125;
				}
			}
		}
	}
}
void attack(bool g_abKeyPressed[], Console& g_Console)
{
	//Attacking 
	if (g_abKeyPressed[K_K])
	{
		if (singleplayerMap[player.m_dirY + player.m_Position.Y][player.m_dirX + player.m_Position.X].m_Character == E_AI.m_Character) // Check if the target an AI
		{
			if (g_dElapsedTime > bounceTime) //makes sure computer does not register more than one key press
			{
				singleplayerMap[player.m_dirY + player.m_Position.Y][player.m_dirX + player.m_Position.X].m_CharHealth -= 100; // minus the AI's HEALTH
				bounceTime = g_dElapsedTime + 0.125;
				if (singleplayerMap[player.m_dirY + player.m_Position.Y][player.m_dirX + player.m_Position.X].m_CharHealth <= 0)//if AI is dead
				{
					for (int i = 0; i < (int)allAI.size(); i++) {
						if (allAI[i]->m_Position.X == player.m_dirX + player.m_Position.X && allAI[i]->m_Position.Y == player.m_dirY + player.m_Position.Y) {
							allAI.erase(allAI.begin() + i);//removes the dead AI from the vector
							//Converts the position where the AI was to a blank to allow player to move in it
							singleplayerMap[player.m_dirY + player.m_Position.Y][player.m_dirX + player.m_Position.X] = E_BLANK;
						}
					}
				}
			}
		}
	}
	if (gun)
	{
		//makes sure computer does not register more than one key press
		if (g_dElapsedTime > bounceTime)
		{
			if (g_abKeyPressed[K_J])
			{
				//Adds a new bullets to the vector
				bullets.push_back(new PROJECTILE);
				lastIndex = bullets.size() - 1;
				//sets position of the new bullet 
				bullets[lastIndex]->SetPosition(player.m_Position.X + player.m_dirX, player.m_Position.Y + player.m_dirY);
				x.push_back(player.m_dirX);
				y.push_back(player.m_dirY);
				bounceTime = g_dElapsedTime + 0.125;
			}
		}

	}
}void renderbullets(Console& g_Console)
{
	if (bullets.size() != 0)
	{
		for (int i = 0; i < (int)bullets.size(); i++)
		{
			//Check if the place where the bullets is moving to is a not an obstacle
			if (bullets[i]->projectileCoord.X != 185 && singleplayerMap[bullets[i]->projectileCoord.Y][bullets[i]->projectileCoord.X] == E_BLANK)
			{
				g_Console.writeToBuffer(bullets[i]->projectileCoord, (char)248, 0x09);
				if (g_dElapsedTime > bulletlag)
				{
					//Moves the bullet to the next position
					bullets[i]->move(x[i], y[i]);
				}
			}
			else
			{
				//Check if the bullets hits the AI
				if (bullets[i]->projectileCoord.X != 185 && singleplayerMap[bullets[i]->projectileCoord.Y][bullets[i]->projectileCoord.X].m_Character == E_AI.m_Character)
				{
					for (int j = 0; j < (int)allAI.size(); j++) {
						//Minus the HP of the AI with the same position as what the bullet hit
						if (allAI[j]->m_Position.X == bullets[i]->projectileCoord.X && allAI[j]->m_Position.Y == bullets[i]->projectileCoord.Y) {

							allAI[j]->m_CharHealth -= 10;
						}
						//If AI dies
						if (allAI[j]->m_CharHealth <= 0)
						{
							//Removes AI
							allAI.erase(allAI.begin() + j);
							//Converts the position where the AI was to a blank to allow player to move in it
							singleplayerMap[bullets[i]->projectileCoord.Y][bullets[i]->projectileCoord.X] = E_BLANK;
						}
					}
				}
				//Renders the bullet out side the map so that it looks like the bullet hits a wall.
				bullets[i]->projectileCoord.X = 185;
				bullets[i]->projectileCoord.Y = 56;
			}
		}
		if (g_dElapsedTime > bulletlag) {
			bulletlag = g_dElapsedTime + 0.2;
		}

	}
}
void collectitems(bool g_abKeyPressed[])
{
	if (g_dElapsedTime > bounceTime)
	{
		if (g_abKeyPressed[K_G])
		{
			//Check if item collected is a Keyfragment
			if (singleplayerMap[player.m_dirY + player.m_Position.Y][player.m_dirX + player.m_Position.X].m_Character == E_KEYFRAGMENT.m_Character)
			{
				keyFragments++;
				singleplayerMap[player.m_dirY + player.m_Position.Y][player.m_dirX + player.m_Position.X] = E_BLANK;
				bounceTime = g_dElapsedTime + 0.125;
			}
			//Check if item collected is a healthPotions
			else if (singleplayerMap[player.m_dirY + player.m_Position.Y][player.m_dirX + player.m_Position.X].m_Character == E_HEALTHPOTS.m_Character)
			{
				healthPots++;
				singleplayerMap[player.m_dirY + player.m_Position.Y][player.m_dirX + player.m_Position.X] = E_BLANK;
				bounceTime = g_dElapsedTime + 0.125;
			}
			//Check if item collected is a Gun
			else if (singleplayerMap[player.m_dirY + player.m_Position.Y][player.m_dirX + player.m_Position.X].m_Character == E_GUN.m_Character)
			{
				gun = true;
				singleplayerMap[player.m_dirY + player.m_Position.Y][player.m_dirX + player.m_Position.X] = E_BLANK;
				bounceTime = g_dElapsedTime + 0.125;
			}
		}
	}
}
void checkPoint()
{
	//If player dies,make him start at the starting locaiton of the level he was in
	if (player.m_CharHealth <= 0)
	{
		initSingleplayerMap();
		keyFragments = 0;
		healthPots = 0;
		if (mapNum == 49)
		{
			gun = false;
		}
	}
}
void doorUnlocked(irrklang::ISoundEngine* engine, irrklang::ISoundSource* gate)
{
	//Open the gate for player to go through to the next level
	if (!doorOpened)
	{
		if (keyFragments >= 4)
		{
			singleplayerMap[gateCoord.Y][gateCoord.X] = E_BLANK;
			doorOpened = true;
			if (doorOpened)
				engine->play2D(gate);
		}
	}
	if (keyFragments < 4)
		doorOpened = false;
}
void toNextLevel()
{
	//Check if player is in the gates location to move on to next level
	if (player.m_Position.X == gateCoord.X && player.m_Position.Y == gateCoord.Y)
	{
		mapNum++;
		//if all 4 singleplayer map is completed 
		if (mapNum == 53)
		{
			g_eGameState = S_COMPLETEDSCREEN;

		}
		keyFragments = 0;
		initSingleplayerMap();
	}
}
void renderSingleplayerMap(Console& g_Console)
{
	for (int i = 0; i < 52; i++) {
		for (int j = 0; j < 180; j++) {
			COORD newCOORD;
			newCOORD.Y = i;
			newCOORD.X = j;

			g_Console.writeToBuffer(newCOORD, singleplayerMap[i][j].m_Character, singleplayerMap[i][j].m_ColorInHex);
		}
	}
	renderControls(g_Console, &player);
	for (int i = 0; i < (int)allTraps.size(); i++) {
		g_Console.writeToBuffer(allTraps[i].bulletForTrap->m_Position, (char)248, 0xF);
	}
	renderbullets(g_Console);
}
void initSingleplayerMap()
{
	//Clears the Vectors so that the items in the previous level will not carry over to the next level

	allTraps.clear();
	allAI.clear();
	std::string line;
	
	std::fstream file(maze + (char)mapNum + txt);
	int index = 0;
	if (file.is_open())
	{
		while (!file.eof())
		{
			std::getline(file, line);
			for (int i = 0; i < (int)line.length(); i++) {

				singleplayerMap[index][i].m_Character = line[i];
				singleplayerMap[index][i].m_Position = COORD{ (short)i ,(short)index };
				singleplayerMap[index][i].m_ColorInHex = 0x0;
				if (std::isspace(line[i])) {
					singleplayerMap[index][i] = E_BLANK;
				}

				switch (singleplayerMap[index][i].m_Character) {
				case '#':
					singleplayerMap[index][i] = E_WALL;
					break;
				case '0':
					singleplayerMap[index][i] = E_KEYFRAGMENT;
					break;

				case '>':
					allTraps.push_back(Trap({ (short)1 , (short)0 }, singleplayerMap[index][i].m_Position, new Entity(COORD{ (short)i,(short)index }, '°', 0x2), 25));
					singleplayerMap[index][i] = E_RIGHTTRAP;

					break;
				case '<':

					allTraps.push_back(Trap({ (short)-1 , (short)0 }, singleplayerMap[index][i].m_Position, new Entity(COORD{ (short)i,(short)index }, '°', 0x2), 25));
					singleplayerMap[index][i] = E_LEFTTRAP;

					break;
				case 'D':

					allTraps.push_back(Trap({ (short)0 , (short)1 }, singleplayerMap[index][i].m_Position, new Entity(COORD{ (short)i,(short)index }, '°', 0x2), 25));
					singleplayerMap[index][i] = E_DOWNTRAP;
					break;
				case 'U':

					allTraps.push_back(Trap({ (short)0 , (short)-1 }, singleplayerMap[index][i].m_Position, new Entity(COORD{ (short)i,(short)index }, '°', 0x2), 25));
					singleplayerMap[index][i] = E_UPTRAP;
					break;
				case '8':
					singleplayerMap[index][i].m_Character = (char)219;
					singleplayerMap[index][i].m_ColorInHex = 0x4;
					singleplayerMap[index][i].IDENTIFIER = 1;
					break;
				case 'S':
					player.m_Position = COORD{ (short)i, (short)index };
					player.m_Character = (char)6;
					player.m_ColorInHex = 0x0A;
					player.m_CharHealth = 100;
					singleplayerMap[index][i].m_Character = (char)6;
					singleplayerMap[index][i].m_ColorInHex = 0x0A;
					break;
				case '1':
					singleplayerMap[index][i] = E_GUN;
					break;
				case 'G':
					singleplayerMap[index][i] = E_GATE;
					gateCoord.X = i;
					gateCoord.Y = index;
					break;
				case 'H':
					singleplayerMap[index][i] = E_HEALTHPOTS;
					break;
				case 'A':
					AI *currAI = new AI();
					currAI->m_Position = COORD{ (short)i,(short)index };
					currAI->m_Character = 'A';
					currAI->m_ColorInHex = 0x0B;
					currAI->m_curState = Patrol;
					currAI->m_Target = &player;
					currAI->m_CharHealth = 150;
					currAI->m_damage = 10;

					allAI.push_back(currAI);
					break;


				}

			}
			index++;
		}
	}

	Initializing();
}
void renderControls(Console& g_Console, Character* player)
{
	COORD SurvivorHearts;
	SurvivorHearts.Y = 43;
	SurvivorHearts.X = 38;
	for (int i = 0; i < player->m_CharHealth / 10; i++)//Hearts for survivor
	{
		SurvivorHearts.X++;
		g_Console.writeToBuffer(SurvivorHearts, 3, 0x4);
	}
	//Controls for Survivor
	g_Console.writeToBuffer(25, 43, "Survivor", 0xF);//
	g_Console.writeToBuffer(25, 45, "Movement Controls", 0xF);
	g_Console.writeToBuffer(43, 45, 65, 0x3);//a
	g_Console.writeToBuffer(44, 44, 87, 0x3);//w
	g_Console.writeToBuffer(45, 45, 68, 0x3);//d
	g_Console.writeToBuffer(44, 46, 83, 0x3);//s
	g_Console.writeToBuffer(80, 43, ":Ability Controls:", 0xF);
	g_Console.writeToBuffer(75, 44, "Shoot", 0xF);
	g_Console.writeToBuffer(100, 44, "J", 0x3);
	g_Console.writeToBuffer(75, 45, "Melee Attack", 0xF);
	g_Console.writeToBuffer(100, 45, "K", 0x3);
	g_Console.writeToBuffer(75, 46, "Collect Items", 0xF);
	g_Console.writeToBuffer(100, 46, "G", 0x3);
	g_Console.writeToBuffer(75, 47, "Use HealthPots", 0xF);
	g_Console.writeToBuffer(100, 47, "H", 0x3);
	g_Console.writeToBuffer(135, 43, ":Number of items:", 0xF);
	g_Console.writeToBuffer(130, 44, "Health Potions", 0x3);
	g_Console.writeToBuffer(155, 44, std::to_string(healthPots), 0xF);
	g_Console.writeToBuffer(130, 45, "KeyFragments", 0x3);
	g_Console.writeToBuffer(155, 45, std::to_string(keyFragments) + "/4", 0xF);
}
void renderCompleted(Console& g_Console)
{
	std::string line;
	std::fstream file("MainMenu/singleplayercompleted.txt");
	int index = 0;
	while (!file.eof())
	{
		for (int y = 0; y < 52; y++)
		{
			std::getline(file, line);
			for (int x = 0; x <(int)line.length(); x++)
			{
				if (line[x] == '8')
				{
					g_Console.writeToBuffer(x, y, (char)219, 0x4);
				}
				else if (line[x] == '!')
					g_Console.writeToBuffer(x, y, line[x], 0x4);
				else if (line[x] == '@')
					g_Console.writeToBuffer(x, y, line[x], 0x4);
				else if (line[x] == ':')
					g_Console.writeToBuffer(x, y, line[x], 0x4);
				else
					g_Console.writeToBuffer(x, y, line[x], 0x0F);

			}
		}
	}
	file.close();
	processInput();
}
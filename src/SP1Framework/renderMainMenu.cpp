#include "RenderMainMenu.h"

int i = 0;
double bounce = 0;
extern double g_dElapsedTime;
void renderMainMenu(Console& g_Console,EGAMESTATES& g_eGameState,bool g_abKeyPressed[], irrklang::ISoundEngine* engine, irrklang::ISoundSource* bgm, irrklang::ISoundSource* solo)
{
	std::string line;
	std::fstream file("MainMenu/startmenuupdated.txt");
	COORD newCOORD;
	newCOORD.Y = 0;
	newCOORD.X = 0;
	std::string selection[5];
	bool bSomethingHappened = false;
	if (file.is_open())
	{
		while (!file.eof())
		{
			for (int i = 0; i < 52; i++)
			{
				std::getline(file, line);
				for (int i = 0; i < (int)line.length(); i++)
				{
					if (line[i] == '#')
					{
						line[i] = (char)219;
						g_Console.writeToBuffer(newCOORD, line[i], 0xF);
						g_Console.writeToBuffer(newCOORD, line[i + 1], 0xF);
					}
					else if (line[i] == '3')
					{
						line[i] = (char)177;
						g_Console.writeToBuffer(newCOORD, line[i], 0xF);
					}
					else
					{
						g_Console.writeToBuffer(newCOORD, line[i], 0x0);
					}
				}
				g_Console.writeToBuffer(newCOORD, line, 0x4);
				newCOORD.Y += 1;
			}

			if (bounce > g_dElapsedTime)
				return;

			if (g_abKeyPressed[K_DOWN] && i < 4)
			{
				bSomethingHappened = true;
				i++;
			}
			else if (g_abKeyPressed[K_UP] && i > 0)
			{
				bSomethingHappened = true;
				i--;
			}
			if (i == 0)
			{
				g_Console.writeToBuffer(70, 6, ">", 0x3);
				g_Console.writeToBuffer(71, 7, ">", 0x3);
				g_Console.writeToBuffer(70, 8, ">", 0x3);
			}
			else if (i == 1)
			{
				g_Console.writeToBuffer(70, 13, ">", 0x3);
				g_Console.writeToBuffer(71, 14, ">", 0x3);
				g_Console.writeToBuffer(70, 15, ">", 0x3);
			}
			else if (i == 2)
			{
				g_Console.writeToBuffer(70, 20, ">", 0x3);
				g_Console.writeToBuffer(71, 21, ">", 0x3);
				g_Console.writeToBuffer(70, 22, ">", 0x3);
			}
			else if (i == 3)
			{
				g_Console.writeToBuffer(70, 27, ">", 0x3);
				g_Console.writeToBuffer(71, 28, ">", 0x3);
				g_Console.writeToBuffer(70, 29, ">", 0x3);
			}
			else if (i == 4)
			{
				g_Console.writeToBuffer(70, 35, ">", 0x3);
				g_Console.writeToBuffer(71, 36, ">", 0x3);
				g_Console.writeToBuffer(70, 37, ">", 0x3);
			}
			
			if (g_abKeyPressed[K_SPACE])
			{
				
				switch (i)
				{
				case 0:
				{
					i = 0;
					resetMultiplayer();
					g_eGameState = S_GAME;
					engine->stopAllSounds();
					engine->play2D(bgm, true);
					break;
				}
				case 1:
				{
					i = 1;
					resetSingleplayer();
					g_eGameState = S_SINGLEPLAYER;
					engine->stopAllSounds();
					engine->play2D(solo, true);
					break;
				}
				case 2:
				{
					i = 2;
					g_eGameState = S_INSTRUCTIONS;
					break;
				}
				
				case 3:
				{
					i = 3;
					resetTutorial();
					g_eGameState = S_TUTORIAL;
					break;
				}
				case 4:
				{
					i = 4;
					g_bQuitGame = true;
					break;
				}
				}
			}
			if (bSomethingHappened)
			{
				bounce = g_dElapsedTime + 0.225;
			}
		}
	}
	else
	{
		file.close();
	}
}
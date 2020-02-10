#include "RenderClassSelection.h"

void renderClassSelection(Console& g_Console,EGAMESTATES& g_eGameState,bool g_abKeyPressed[])
{
	std::string line;
	std::fstream file("MainMenu/characterscreen.txt");
	if (file.is_open())
	{
		while (!file.eof())
		{
			for (int y = 0; y < 52; y++)
			{
				std::getline(file, line);
				for (int x = 0; x < (int)line.length(); x++)
				{
					if (line[x] == '8')
					{
						line[x] = (char)219;
						if(y == 0)
							g_Console.writeToBuffer(x, y, (char)219, 0x0);
						else
							g_Console.writeToBuffer(x, y, (char)219, 0xF);
					}
					else if (line[x] == '?')
					{
						line[x] = 3;
						g_Console.writeToBuffer(x,y, (char)3, 0x4);
					}
					else if (line[x] == ' ')
					{
						g_Console.writeToBuffer(x,y, line[x], 0x0);
					}
					else
					{
						g_Console.writeToBuffer(x,y, line[x], 0xF);
					}
				}
			}
		}
		if (g_abKeyPressed[K_ONE])
		{
			g_eGameState = S_GAME;
		}
		if (g_abKeyPressed[K_TWO])
		{
			g_eGameState = S_GAME;
		}
		if (g_abKeyPressed[K_THREE])
		{
			g_eGameState = S_GAME;
		}
		if (g_abKeyPressed[K_FOUR])
		{
			g_eGameState = S_GAME;
		}
	}
	else
	{
		file.close();
	}

}
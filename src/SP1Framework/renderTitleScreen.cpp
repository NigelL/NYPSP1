#include "RenderTitleScreen.h"

void renderTitleScreen(Console& g_Console)
{
	std::string line;
	std::fstream file("MainMenu/startscreen.txt");
	COORD newCOORD;
	newCOORD.Y = 0;
	newCOORD.X = 0;
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
						g_Console.writeToBuffer(newCOORD, line[i], 0x4);
						g_Console.writeToBuffer(newCOORD, line[i + 1], 0x4);
					}
					else if (line[i] == 'f')//&& (playerTwo->m_CharHealth >= 0))
					{
						line[i] = (char)178;
						g_Console.writeToBuffer(newCOORD, line[i], 0x4);
					}
					else
					{
						g_Console.writeToBuffer(newCOORD, line[i], 0x0);
					}
				}
				g_Console.writeToBuffer(newCOORD, line, 0x4);
				newCOORD.Y += 1;
			}
		}
	}
	else
	{
		file.close();
	}
}
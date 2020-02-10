#include "RenderInstruction.h"

void renderInstruction(Console& g_Console,EGAMESTATES& g_eGameState,bool g_abKeyPressed[])
{
	std::string line;
	std::fstream file("MainMenu/Instruction.txt");
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

					g_Console.writeToBuffer(100, 22, (char)234, 0xD);
					g_Console.writeToBuffer(91, 24, (char)193, 0x3);
					g_Console.writeToBuffer(91, 26, (char)195, 0x3);
					g_Console.writeToBuffer(91, 28, (char)194, 0x3);
					g_Console.writeToBuffer(91, 30, (char)180, 0x3);
					{
						g_Console.writeToBuffer(newCOORD, line[i], 0x4);
					}
				}
				g_Console.writeToBuffer(newCOORD, line, 0x4);
				newCOORD.Y += 1;
			}
		}
		if (g_abKeyPressed[K_ESCAPE])
		{
			g_eGameState = S_MAINMENU;
		}
	}
	else
	{
		file.close();
	}
}
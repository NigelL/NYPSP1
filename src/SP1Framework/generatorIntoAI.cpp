#include "GeneratorIntoAI.h"

std::vector <int> xCoord;
std::vector <int> yCoord;
COORD generatorCOORD;
int generatorNum = 0;
int counter = 0;

void convertToAI(Character* AIone,Character* AItwo,int** entireMapChar)
{
	for (int y = 0; y < 42; y++)
	{
		for (int x = 0; x < 180; x++)
		{
			if (entireMapChar[y][x] == 2)
			{
				generatorNum++;
				xCoord.push_back(x);
				yCoord.push_back(y);
				entireMapChar[y][x] = 10;
				if (generatorNum == 1)
				{
					AIone->m_Position.X = x;
					AIone->m_Position.Y = y;
				}
				else
				{
					AItwo->m_Position.X = x;
					AItwo->m_Position.Y = y;
				}
			}
		}
	}
}
std::vector <node> runPathFinder(Character playerTwo)
{
		std::vector <node> path;
		generatorCOORD.X = xCoord[counter];
		generatorCOORD.Y = yCoord[counter];
		pathFinder(generatorCOORD, playerTwo.m_Position);
		path = retracePath();
		if (counter == 1)
		{
			counter = 0;
		}
		else 
			counter++;

		return path;
}
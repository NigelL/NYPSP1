#include "TrapBuilder.h"
#include <iostream>

#define STARTINDEX 4
#define MAX_LIMIT 3

int pressCounter = 0,currentTrap = 0;

double trapBounce;



/*
EGAMESTATES Build(bool* keyPressed,Entity** mapData,Console& gConsole,double& trapTime,int& trapBeingDisplayed) {
	if (trapBounce < trapTime) {
		if (keyPressed[K_FIRE1]) {

			COORD currentPoint = gConsole.getMouseXY();

			if (currentPoint.Y > 1 && currentPoint.Y < 41 && currentPoint.X > 1 && currentPoint.X < 179) {
				int evalValue = 0;
				switch (currentTrap + 3 ) {
				case 3:
					evalValue = 195;
					break;
				case 4:
					evalValue = 180;
					break;
				case 5:
					evalValue = 193;
					break;
				case 6:
					evalValue = 194;
					break;

				}

				mapData[currentPoint.Y][currentPoint.X].m_Character = evalValue;
				pressCounter++;
				if (pressCounter >= MAX_LIMIT) {
					return EGAMESTATES::S_GAME;
				}
			}
			trapBounce = trapTime + 0.25;

		}
		else if (keyPressed[K_TAB]) {
			currentTrap = (((currentTrap + 1) % STARTINDEX) + STARTINDEX) % STARTINDEX;
			trapBeingDisplayed = currentTrap + 3;
			trapBounce = trapTime + 0.25;

		}
		 
	}

	return EGAMESTATES::S_NULL;

	
}
*/
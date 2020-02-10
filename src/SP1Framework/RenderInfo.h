#pragma once
#include "Framework\console.h"
#include "Character.h"
#include <string>

class RenderData {
public:	
	COORD startCOORD;
	double startTime;
	double coolDownTime;
	std::string renderInfo;

};

class RenderInstruction {
public:
	static int renderIndex;
	static std::vector<RenderData> renderStartTimes;
	static std::vector<COORD> renderCOORD;
	static COORD instructionCOORD;

	static void UpdateCoolDown();


	static void RenderCoolDown( double mag, double elapsedTime,std::string action,double offsetX);
	static void DecreaseIndex() {
		for (int i = 0; i < (int)renderStartTimes.size(); i++) {
			renderStartTimes[i].startCOORD.Y += 2;
		}
		renderIndex--;
	}

	static void IncreaseIndex() {
		renderIndex++;
	}
};
void storeinsruct(Console& g_Console, Character* playerOne, Character* playerTwo);




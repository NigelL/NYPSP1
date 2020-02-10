#include "RenderInfo.h"

extern int pressCount;

std::vector<RenderData> RenderInstruction::renderStartTimes;
std::vector<COORD> RenderInstruction::renderCOORD;
int RenderInstruction::renderIndex;
COORD RenderInstruction::instructionCOORD = COORD{150 , 43};

void RenderInstruction::UpdateCoolDown() {
	for (int i = 0; i < (int)renderStartTimes.size(); i++) {
		double coolDown = (double)((renderStartTimes[i].coolDownTime - 0.02) / (double)((renderStartTimes[i].coolDownTime))) * (renderStartTimes[i].coolDownTime);
		renderStartTimes[i].coolDownTime = coolDown;
	}
}

void RenderInstruction::RenderCoolDown(double mag, double elapsedTime,std::string action,double offsetX) {

	COORD offsetInstruction = instructionCOORD;
	offsetInstruction.X -= (short)offsetX;
	offsetInstruction.Y += ((SHORT)renderIndex) * 2;
	IncreaseIndex();
	renderStartTimes.push_back(RenderData{ offsetInstruction , elapsedTime,mag ,action});
	

}


void storeinsruct(Console& g_Console, Character* playerOne, Character* playerTwo)
{
	COORD SurvivorHearts;
	SurvivorHearts.Y = 43;
	SurvivorHearts.X = 38;
	for (int i = 0; i < playerTwo->m_CharHealth / 50; i++)//Hearts for survivor
	{
		SurvivorHearts.X++;
		g_Console.writeToBuffer(SurvivorHearts, 3, 0x4);
	}
	//Controls for Survivor
	g_Console.writeToBuffer(25, 43, "Survivor : ", 0xF);//
	g_Console.writeToBuffer(25, 45, "Movement Controls : ", 0xF);
	g_Console.writeToBuffer(43, 45, 65, 0x3);//a
	g_Console.writeToBuffer(44, 44, 87, 0x3);//w
	g_Console.writeToBuffer(45, 45, 68, 0x3);//d
	g_Console.writeToBuffer(44, 46, 83, 0x3);//s

	g_Console.writeToBuffer(25, 50, "Rotation Controls / Place : ", 0xF);
	g_Console.writeToBuffer(55, 50, "R", 0x3);
	
	

	if (playerTwo->m_damage != 0) {
		g_Console.writeToBuffer(25, 47, "Ability : ", 0xF);
		g_Console.writeToBuffer(55, 47, "Q", 0x3);
		g_Console.writeToBuffer(25, 48, "Attack", 0xF);
		g_Console.writeToBuffer(55, 48, "F", 0x3);

	}
	else {
		g_Console.writeToBuffer(25, 48, "Stop Fixing generator", 0xF);
		g_Console.writeToBuffer(55, 48, "F", 0x3);

		g_Console.writeToBuffer(25, 49, "Generator : ", 0xF);
		g_Console.writeToBuffer(55, 49, "w", 0x3);
		g_Console.writeToBuffer(4, 45, "Generator Bar", 0xF);
	}


	COORD KillerHearts;
	KillerHearts.Y = 43;
	KillerHearts.X = 110;
	for (int i = 0; i < playerOne->m_CharHealth / 50; i++)// hearts for killer
	{
		KillerHearts.X++;
		g_Console.writeToBuffer(KillerHearts, 3, 0x4);
	}
	g_Console.writeToBuffer(100, 43, "Killer", 0xF);
	g_Console.writeToBuffer(105, 45, "Movement Controls", 0xF);
	g_Console.writeToBuffer(123, 45, 27, 0x3);//arrow left
	g_Console.writeToBuffer(124, 44, 24, 0x3);//arrow up
	g_Console.writeToBuffer(125, 45, 26, 0x3);//arrow right
	g_Console.writeToBuffer(124, 46, 25, 0x3);//arrow down
	if (playerTwo->m_damage != 0) {
		g_Console.writeToBuffer(105, 47, "Shoot", 0xF);
		g_Console.writeToBuffer(120, 47, "P", 0x3);
	}
	g_Console.writeToBuffer(105, 48, "Break", 0xF);
	g_Console.writeToBuffer(120, 48, "L", 0x3);
	g_Console.writeToBuffer(105, 49, "Blackout", 0xF);
	g_Console.writeToBuffer(120, 49, ";", 0x3);
	g_Console.writeToBuffer(105, 50, "Attack", 0xF);
	g_Console.writeToBuffer(120, 50, "' (quotation)", 0x3);
	COORD GeneratorPos;
	GeneratorPos.Y = 46;
	GeneratorPos.X = 4;
	for (int i = 0; i < pressCount; i++)
	{
		GeneratorPos.X++;
		g_Console.writeToBuffer(GeneratorPos, (char)220, 0x2);
		g_Console.writeToBuffer(4 + pressCount, 46, 0x4);
	}

restartLoop:
	for (int i = 0; i < (int)RenderInstruction::renderStartTimes.size(); i++) {

		if (RenderInstruction::renderStartTimes[i].coolDownTime <= 0) {
			RenderInstruction::renderStartTimes.erase(RenderInstruction::renderStartTimes.begin() + i);
			RenderInstruction::DecreaseIndex();
			goto restartLoop;
		}
		
		for (int j = 0; j < RenderInstruction::renderStartTimes[i].coolDownTime; j++) {		
			COORD c = RenderInstruction::renderStartTimes[i].startCOORD;
			c.X += j;
			g_Console.writeToBuffer(c, (char)219, 0x09);

		}
		COORD c = RenderInstruction::renderStartTimes[i].startCOORD;
		c.Y -= 1;
		g_Console.writeToBuffer(c, RenderInstruction::renderStartTimes[i].renderInfo, 0x09);


	}
}
#include "Rotation.h"
#include "PathFinding.h"
#include "Values.h"

extern node** grid;

bool FindInVector(std::vector<COORD> coordList,COORD theCOORD) {
	for (int i = 0; i < (int)coordList.size(); i++) {
		if (coordList[i].X == theCOORD.X && coordList[i].Y == theCOORD.Y) {
			return true;
		}
	}

	return false;
	//return (std::find(coordList.begin(), coordList.end(), theCOORD) != coordList.end());
}

double DegToRad(double angle) {
	return (angle *3.14159 / 180);
}


void Rotate(COORD coord,COORD startCoord,COORD dirCOORD,COORD prevDirCOORD,int index,Entity** mazeData,const int boundX,const int boundY,std::vector<COORD> coordForChange) {
	
	
	double angleToRad = DegToRad(90);
	
	 
	if (coord.X <= 1 || coord.X >= (boundX - 2) || coord.Y <= 1 || coord.Y >= boundY - 2) {
		return;
	}
	if (index >= 2) {
		index = 0;
		coord = startCoord;		
	}

	COORD cRight;
	cRight.Y = coord.Y;
	cRight.X = coord.X + 1;


	COORD cLeft;
	cLeft.Y = coord.Y;
	cLeft.X = coord.X - 1;

	COORD cTop;
	cTop.Y = coord.Y - 1;
	cTop.X = coord.X;

	COORD cBottom;
	cBottom.Y = coord.Y + 1;
	cBottom.X = coord.X;
	
	if (dirCOORD.Y != 0) {
		
		if (prevDirCOORD.X == 1) {

			if (mazeData[coord.Y][coord.X - 1] == E_WALL && !FindInVector(coordForChange, cLeft)) {


				coordForChange.push_back(cLeft);
				index++;


				Rotate(cLeft, startCoord, dirCOORD, prevDirCOORD, index, mazeData, boundX, boundY, coordForChange);

			}

			if (mazeData[coord.Y][coord.X + 1]== E_WALL && !FindInVector(coordForChange, cRight)) {

				coordForChange.push_back(cRight);


				index++;
				Rotate(cRight, startCoord, dirCOORD, prevDirCOORD, index, mazeData, boundX, boundY, coordForChange);
			}

		}
		else {

			if (mazeData[coord.Y][coord.X + 1] == E_WALL && !FindInVector(coordForChange, cRight)) {

				coordForChange.push_back(cRight);


				index++;
				Rotate(cRight, startCoord, dirCOORD, prevDirCOORD, index, mazeData, boundX, boundY, coordForChange);
			}

			if (mazeData[coord.Y][coord.X - 1] == E_WALL && !FindInVector(coordForChange, cLeft)) {


				coordForChange.push_back(cLeft);
				index++;


				Rotate(cLeft, startCoord, dirCOORD, prevDirCOORD, index, mazeData, boundX, boundY, coordForChange);

			}

			
		}

		
	}
	else
	{

		if (mazeData[coord.Y - 1][coord.X]  == E_WALL && !FindInVector(coordForChange, cTop)) {

			coordForChange.push_back(cTop);
			index++;
			Rotate(cTop,startCoord , dirCOORD,prevDirCOORD, index, mazeData, boundX, boundY, coordForChange);
		}
		
		if (mazeData[coord.Y + 1][coord.X]== E_WALL && !FindInVector(coordForChange, cBottom)) {
			
			coordForChange.push_back(cBottom);
			index++;
			Rotate(cBottom, startCoord, dirCOORD,prevDirCOORD, index, mazeData, boundX, boundY, coordForChange);
		}
		
		
	}
	  
	

	if (coordForChange.size() > 1) {

		if (coordForChange[1].X - coordForChange[0].X != 0) {
			for (int i = 1; i < (int)coordForChange.size(); i++) {
				int diffCurrent = coordForChange[i].X - coordForChange[i - 1].X;
				if ((mazeData[coordForChange[i].Y][coordForChange[i].X].m_Character != E_GENERATOR.m_Character)) {
					mazeData[coordForChange[i].Y][coordForChange[i].X] = E_BLANK;


					coordForChange[i].X = coordForChange[0].X;
					coordForChange[i].Y = coordForChange[0].Y + diffCurrent;

					mazeData[coordForChange[i].Y][coordForChange[i].X] = E_WALL;
				}
			}
		}
		else {
			for (int i = 1; i < (int)coordForChange.size(); i++) {
				if ((mazeData[coordForChange[i].Y][coordForChange[i].X].m_Character != E_GENERATOR.m_Character)) {
					mazeData[coordForChange[i].Y][coordForChange[i].X] = E_BLANK;

					int diffCurrent = coordForChange[i].Y - coordForChange[i - 1].Y;
					coordForChange[i].Y = coordForChange[0].Y;
					coordForChange[i].X = coordForChange[0].X + diffCurrent;
					mazeData[coordForChange[i].Y][coordForChange[i].X] = E_WALL;
				}
			}
		}
		
	}
	return;

}
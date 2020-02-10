
#include "PathFinding.h"
#include "Entity.h"

//Creating of Variables needed
extern Entity** singleplayerMap;
node** grid;

bool found = false; 
int nodeIndex = 0;
int iterationMaxCount = 20,iteration;

node startNode, endNode,currentnode;
node* memoryAddress;



void Initializing()
{
	grid = new node*[42];
	for (int y = 0; y < 42; y++)
	{
		grid[y] = new node[180];
	}

	
		for (int y = 0; y < 42; y++)
		{
			for (int x = 0; x < 180; x++)
			{

				if (singleplayerMap[y][x].m_Character != 32)
				{
					grid[y][x].obstacle = true;
				}
				grid[y][x].xPos = x;
				grid[y][x].yPos = y;
				grid[y][x].g_Cost = 0;
				grid[y][x].h_Cost = 0;
				grid[y][x].f_Cost = 0;
			}
		}
	
}
/*
std::vector<node> pathFinder(COORD start, COORD end,std::vector<node>& OPEN,std::vector<node>& CLOSED)
{
	iteration = 0;

	startNode.xPos = start.X;
	startNode.yPos = start.Y;
	endNode.xPos = end.X;
	endNode.yPos = end.Y;
	OPEN.push_back(startNode);
	if (endNode.obstacle) {
		return std::vector<node>();
	}

	while (!OPEN.empty())
	{
		currentnode = OPEN[0];



		for (int i = 1; i < OPEN.size(); i++) {
			if (OPEN[i].f_Cost < currentnode.f_Cost)
			{
				currentnode = OPEN[i];
			}
			else if (OPEN[i].f_Cost == currentnode.f_Cost && OPEN[i].h_Cost < currentnode.h_Cost)
			{
				currentnode = OPEN[i];
			}
		}

		OPEN.erase(std::remove(OPEN.begin(), OPEN.end(), currentnode));
		CLOSED.push_back(currentnode);
		if (currentnode == endNode || iteration >= iterationMaxCount) {
			if (currentnode == endNode) {
				OPEN.clear();
				CLOSED.clear();
			}
			return retracePath();
		}

		std::vector <node*> neighbours = findingNeighbour(currentnode);
		//int counterPossible = 0;
		for (int i = 0; i < neighbours.size(); i++)
		{
			if (neighbours[i]->obstacle || std::find(CLOSED.begin(), CLOSED.end(), *neighbours[i]) != CLOSED.end()) {

				continue;
			}

			int cost = currentnode.g_Cost + calculateDistance(currentnode, *neighbours[i]);
			if (cost < neighbours[i]->g_Cost || std::find(OPEN.begin(), OPEN.end(), *neighbours[i]) == OPEN.end()) {
				neighbours[i]->g_Cost = cost;
				neighbours[i]->h_Cost = calculateDistance(endNode, *neighbours[i]);
				neighbours[i]->parent = &grid[currentnode.yPos][currentnode.xPos];
				if (std::find(OPEN.begin(), OPEN.end(), *neighbours[i]) == OPEN.end()) {
					OPEN.push_back(*neighbours[i]);
				}
			}
		}

		iteration++;

	}

}
*/

std::vector<node> pathFinder(COORD start, COORD end)
{
	std::vector <node> OPEN;
	std::vector <node> CLOSED;

	startNode.xPos = start.X;
	startNode.yPos = start.Y;
	endNode.xPos = end.X;
	endNode.yPos = end.Y;
	OPEN.push_back(startNode);

	if (endNode.obstacle) {
		return std::vector<node>();
	}

	while (!OPEN.empty())
	{
		currentnode = OPEN[0];
		
		for (int i = 1; i < (int)OPEN.size(); i++) {
			if (OPEN[i].f_Cost < currentnode.f_Cost)
			{
				currentnode = OPEN[i];
			}
			else if (OPEN[i].f_Cost == currentnode.f_Cost && OPEN[i].h_Cost < currentnode.h_Cost)
			{
				currentnode = OPEN[i];
			}
		}
		
		OPEN.erase(std::remove(OPEN.begin(), OPEN.end(), currentnode));
		CLOSED.push_back(currentnode);
		if (currentnode == endNode) {

			return retracePath();
		}

		std::vector <node*> neighbours = findingNeighbour(currentnode);
		//int counterPossible = 0;
		for (int i = 0; i < (int)neighbours.size(); i++)
		{
			if (neighbours[i]->obstacle || std::find(CLOSED.begin(),CLOSED.end(), *neighbours[i]) != CLOSED.end()) {
				
				continue;
			}

			int cost = currentnode.g_Cost + calculateDistance(currentnode, *neighbours[i]);
			if (cost < neighbours[i]->g_Cost || std::find(OPEN.begin(), OPEN.end(),*neighbours[i]) == OPEN.end()) {
				neighbours[i]->g_Cost = cost;
				neighbours[i]->h_Cost = calculateDistance(endNode, *neighbours[i]);
				neighbours[i]->f_Cost = neighbours[i]->h_Cost + neighbours[i]->g_Cost;
				neighbours[i]->parent = &grid[currentnode.yPos][currentnode.xPos];				
				if (std::find(OPEN.begin(), OPEN.end(), *neighbours[i]) == OPEN.end()) {
					OPEN.push_back(*neighbours[i]);
				}
			}
		}
		
	}
	return std::vector<node>();
}
std::vector <node*> findingNeighbour(node nodeA)
{
	std::vector <node*> neighbour;
	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			if (x == 0 && y == 0)
				continue;
			if (x !=  0 && y != 0)
				continue;

			int checkX = grid[nodeA.yPos + y][nodeA.xPos + x].xPos;
			int checkY = grid[nodeA.yPos + y][nodeA.xPos + x].yPos;
			neighbour.push_back(&(grid[checkY][checkX]));
		}
	}
	return neighbour;
}
int calculateDistance(node nodeA, node nodeB)
{
	int dstX = abs(nodeA.xPos - nodeB.xPos);
	int dstY = abs(nodeA.yPos - nodeB.yPos);

	if (dstX>dstY)
		return 14 * dstY + 10 * abs((dstX - dstY));
	return 14 * dstX + 10 * abs((dstY - dstX));
}
std::vector<node> retracePath()
{
	std::vector <node> path = std::vector<node>();
	node currNode = currentnode;
	while (currNode != startNode)
	{
		path.push_back(currNode);
		if (currNode.parent != NULL) {
			currNode = *currNode.parent;
		}
		else {
			break;
		}
	}
	if (path.size() > 0) {
		std::reverse(path.begin(), path.end());
	}

	return path;
}
//bool compareNode(node nodeA, node nodeB)
//{
//	if (nodeA.f_Cost() < nodeB.f_Cost())
//		return true;
//	else if (nodeA.f_Cost() == nodeB.f_Cost())
//	{
//		if (nodeA.h_Cost < nodeB.h_Cost)
//			return true;
//	}
//	return false;
//}
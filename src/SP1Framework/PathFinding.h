#pragma once
#include <Windows.h>
#include <algorithm>
#include <vector>

template<class T>
class Heap {
public:
	T left, right, root,current;

};

struct node
{
	node* left, *right, *root;

	node() {

	}
	node(int fCost) {
		f_Cost = fCost;

		left = new node();
		right = new node();
		root = new node();
	}
	bool obstacle = false; //block you can pass thru or not
	int g_Cost = 0;//Distance from starting point
	int h_Cost = 0;//Distance from ending Point
	int f_Cost;

	int xPos = 0;
	int yPos =0;
	node* parent = nullptr;

	bool operator==(const node& nodeB)
	{
		if (obstacle != nodeB.obstacle)
			return false;
		if (xPos != nodeB.xPos) 
			return false;		
		if (yPos != nodeB.yPos)
		   return false;


		return true;
	}
	bool operator!=(const node& nodeB)
	{
		return !(*this == nodeB);
	}

	
};

struct compareNode
{
	bool operator() (node nodeA, node nodeB)
	{
		if (nodeA.f_Cost < nodeB.f_Cost)
			return true;
		else if (nodeA.f_Cost == nodeB.f_Cost)
		{
			if (nodeA.h_Cost < nodeB.h_Cost)
				return true;
		}
		return false;
	}
};

void Initializing();

std::vector<node> pathFinder(COORD start,COORD end);
std::vector<node> pathFinder(COORD start, COORD end, std::vector<node>& OPEN, std::vector<node>& CLOSED);
std::vector <node*> findingNeighbour(node nodeA);
int calculateDistance(node nodeA, node nodeB);
std::vector<node> retracePath();
//bool compareNode(node nodeA, node nodeB);
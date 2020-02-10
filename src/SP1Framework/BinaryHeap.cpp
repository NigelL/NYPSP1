#include "BinaryHeap.h"

void MakeHeap(std::vector<node>& heap,int index) {
	
	
	//left < root swap    right < root swap 
	
	if (index >= (int)heap.size() / 2) {
		return;
	}

	if (2 * index + 1 <= (int)heap.size() - 1) {

		heap[index].left = &heap[2 * index + 1];
		heap[index].left->root = &heap[index];
		
		if (heap[index].left->f_Cost < heap[index].left->root->f_Cost) {
			int rootFCost = heap[index].left->root->f_Cost;

			heap[index].left->root->f_Cost = heap[index].left->f_Cost;

			heap[index].left->f_Cost = rootFCost;		
			
		}
			
	}

	if (2 * index + 2 <= (int)heap.size() - 1) {

		heap[index].right = &heap[2 * index + 2];
		heap[index].right->root = &heap[index];
			
		if (heap[index].right->f_Cost < heap[index].right->root->f_Cost) {
			int rootFCost = heap[index].right->root->f_Cost;

			heap[index].right->root->f_Cost = heap[index].right->f_Cost;

			heap[index].right->f_Cost = rootFCost;
		}
		

	}
	MakeHeap(heap, index + 1);
	
		
	

	

	

}
void SwapInHeap(Heap<node>& a, Heap<node>& b) {
	Heap<node> storedA = a;

	a.current.f_Cost = b.current.f_Cost;

	b.current.f_Cost = storedA.current.f_Cost;
}

void InsertHeap(std::vector<Heap<node>>& heap, Heap<node> nodeInsert) {



	heap.push_back(nodeInsert);
	if (heap.size() <= 1) {
		return;
	}

	int parentN = (heap.size() - 2) / 2;
	int leftChild = (parentN * 2) + 1;
	int rightChild = (parentN * 2) + 2;

	int currentNode = heap.size() - 1;
	//currentNode.root = heap[parentN].current;


	while (true) {
		heap[currentNode].root = heap[parentN].current;

		if (heap[currentNode].current.f_Cost < heap[parentN].current.f_Cost || heap[currentNode].current.h_Cost < heap[parentN].current.h_Cost) {
			SwapInHeap(heap[currentNode], heap[parentN]);
			//currentNode.current.f_Cost = heap[parentN].current.f_Cost;
			//Swap the root and the current node
			//std::cout << "Current Node : " << currentNode.current.f_Cost << "Parent Node : " << heap[parentN].current.f_Cost << std::endl;
			currentNode = parentN;
			parentN = (parentN - 1) / 2;
		}
		else {
			break;
		}

		if (currentNode <= 0) {
			break;
		}


	}


}
node PopHeap(std::vector<Heap<node>>& heap) {

		node startNode = heap[0].current;
		heap.erase(heap.begin());

		int index = 0,currentIndex = 0;
	
		heap[currentIndex].current = heap[heap.size() - 1].current;
		while (true) {
			int leftChild = 2 * index + 1;
			int rightChild = 2 * index + 2;

			if (leftChild >= (int)heap.size() || rightChild >= (int)heap.size()) {
				break;
			}

			if (heap[leftChild].current.f_Cost < heap[rightChild].current.f_Cost) {
				if (heap[leftChild].current.f_Cost < heap[currentIndex].current.f_Cost) {
					SwapInHeap(heap[leftChild], heap[currentIndex]);
					currentIndex = leftChild;
				}
		
			}
			else {
				if (heap[rightChild].current.f_Cost < heap[currentIndex].current.f_Cost) {
					SwapInHeap(heap[rightChild], heap[currentIndex]);
					currentIndex = rightChild;
				}
			}

			index++;
		
		}
	

		return startNode;

	}



/*
void MakeHeap(std::vector<int>& heap, int index) {


	//left < root swap    right < root swap 

	if (index >= heap.size() / 2) {
		return;
	}

	if (2 * index + 1 <= heap.size() - 1) {

		heap[index].left = &heap[2 * index + 1];
		heap[index].left->root = &heap[index];

		if (heap[index].left->f_Cost < heap[index].left->root->f_Cost) {
			int rootFCost = heap[index].left->root->f_Cost;

			heap[index].left->root->f_Cost = heap[index].left->f_Cost;

			heap[index].left->f_Cost = rootFCost;

		}

	}

	if (2 * index + 2 <= heap.size() - 1) {

-		heap[index].right = &heap[2 * index + 2];
		heap[index].right->root = &heap[index];

		if (heap[index].right->f_Cost < heap[index].right->root->f_Cost) {
			int rootFCost = heap[index].right->root->f_Cost;

			heap[index].right->root->f_Cost = heap[index].right->f_Cost;

			heap[index].right->f_Cost = rootFCost;
		}


	}
	MakeHeap(heap, index + 1);

}


void VisualiseHeap(std::vector<node> heap, Console& g_Console) {

	COORD startC = { 90,0 };
	//g_Console.writeToBuffer(startC, "123", 0x03);

	
	

	for (int i = 0; i < heap.size(); i++) {

		if (heap[i].left) {
			COORD c = { startC.X - (i + 1) * 5, startC.Y + (i + 1) * 5 };
			g_Console.writeToBuffer(c, " hey", 0x03);
		}
		if (heap[i].right) {
			COORD c = { startC.X + (i + 1) * 5, startC.Y + (i + 1) * 5 };
			g_Console.writeToBuffer(c, " hey", 0x03);
		}
	}
	
}
*/

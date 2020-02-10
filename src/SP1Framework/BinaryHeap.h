#pragma once
#include <vector>
#include "PathFinding.h"
#include "Framework\console.h"






void MakeHeap(std::vector<node>& heap, int index);
void InsertHeap(std::vector<Heap<node>>& heap, Heap<node> nodeInsert);
void SwapInHeap(Heap<node>& a, Heap<node>& b);

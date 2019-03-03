#pragma once

#include <SFML\Graphics.hpp>;
#include "DoubleLinkedList.h"

using namespace sf;

class KnightsTourSolver
{
private:
	bool SolveFunction(Vector2i location, int moveNumber, int width, int height, int** board);
	bool IsSafe(Vector2i location, int width, int height, int** board);
	DoubleLinkedList<Vector2i>* BuildLinkedList(DoubleLinkedList<Vector2i> & linkedList, int** board, int width, int height, int findNumber = 0);
public:
	static const int POSSIBLE_MOVES = 8;

	Vector2i _moves[POSSIBLE_MOVES] = { Vector2i(-2,1),Vector2i(-2,-1),
										Vector2i(2, 1), Vector2i(2,-1),
										Vector2i(1, 2), Vector2i(1,-2),
										Vector2i(-1,2),Vector2i(-1,-2) };

	int** _board; //store the solution here.
	DoubleLinkedList<Vector2i> _linkedList; //store the solution here aswell(but in a different format)

	bool SolveRecursive(Vector2i startingPoint, int width, int height);//ints the board here


	KnightsTourSolver();
	~KnightsTourSolver();
};


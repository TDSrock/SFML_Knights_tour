#include "KnightsTourSolver.h"

bool KnightsTourSolver::SolveFunction(Vector2i location, int moveNumber, int width, int height, int ** board)
{
	if (moveNumber == width * height)
		return true;
	for (size_t i = 0; i < POSSIBLE_MOVES; i++)
	{
		Vector2i next = location + _moves[i];
		if (IsSafe(next, width, height, board)) {
			board[next.x][next.y] = moveNumber;
			if (SolveFunction(next, moveNumber + 1, width, height, board)) {
				return true;
			}
			else {
				board[next.x][next.y] = -1;//Not this path
			}
		}
	}
	return false;
}

bool KnightsTourSolver::IsSafe(Vector2i location, int width, int height, int ** board)
{
	return (location.x >= 0 && location.x < width && location.y >= 0 &&
		location.y < height && board[location.x][location.y] == -1);
}

DoubleLinkedList<Vector2i>* KnightsTourSolver::BuildLinkedList(DoubleLinkedList<Vector2i>& linkedList, int ** board, int width, int height, int findNumber)
{
	if (findNumber == width * height) {
		return &linkedList;
	}
	for (size_t x = 0; x < width; x++)
	{
		for (size_t y = 0; y < height; y++)
		{
			if (board[x][y] == findNumber) {
				linkedList.append(Vector2i(x, y));
				return BuildLinkedList(linkedList, board, width, height, findNumber + 1);
			}
		}
	}
	return NULL;
}

bool KnightsTourSolver::SolveRecursive(Vector2i startingPoint, int width, int height)
{
	//setup
	_board = new int*[height];
	for (size_t x = 0; x < width; x++)
	{
		_board[x] = new int[width];
		for (size_t y = 0; y < height; y++)
		{
			_board[x][y] = -1;
		}
	}
	//start point needs to start as 0
	_board[startingPoint.x][startingPoint.y] = 0;
	//start the solver
	if (SolveFunction(startingPoint, 1, width, height, _board)) {
		printf(" >>> Successful! <<< ");
		//setup the linked list
		BuildLinkedList(_linkedList, _board, width, height);
		return true;
	}
	else {
		printf(" >>> Not possible! <<< ");
		return false;
	}
}

KnightsTourSolver::KnightsTourSolver()
{
}


KnightsTourSolver::~KnightsTourSolver()
{
}

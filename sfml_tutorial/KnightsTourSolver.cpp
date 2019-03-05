#include "KnightsTourSolver.h"

bool KnightsTourSolver::Neighbour(Vector2i startingPosition, Vector2i lastPosition)
{
	Vector2i helper = startingPosition - lastPosition;
	int absSum = abs(helper.x) + abs(helper.y);
	return absSum == 3;
}

int KnightsTourSolver::GetDegree(Vector2i location, int width, int height, int ** board)
{
	Vector2i testPos;
	int count = 0;
	for (int i = 0; i < POSSIBLE_MOVES; i++)
		testPos = Vector2i(location.x + _moves[i].x, location.y + _moves[i].y);
		if (IsSafe(testPos, width, height, board))
			count++;

	return count;
}

Vector2i KnightsTourSolver::NextMove(int ** board, Vector2i * position, int width, int height)
{
	printf("\nstart next move\n");
	int min_deg_idx = -1, min_deg = POSSIBLE_MOVES + 1;
	Vector2i nextPoint;

	int start = rand() % POSSIBLE_MOVES;
	for (int count = 0; count < POSSIBLE_MOVES; count++)
	{
		int i = (start + count) % POSSIBLE_MOVES;
		nextPoint = Vector2i(position->x + _moves[i].x, position->y + _moves[i].y);
		//printf("Testing point { %i, %i }\n", nextPoint.x, nextPoint.y);
		if (IsSafe(nextPoint, width, height, board)) {
			int c = GetDegree(nextPoint, width, height, board);
			printf("degree %i min deg %i  min deg idx %i\n", c, min_deg, min_deg_idx);
			if (c < min_deg) {
				min_deg_idx = i;
				min_deg = c;
			}
		}
	}

	if (min_deg_idx == -1) {
		return Vector2i(-1, -1);
	}

	nextPoint = Vector2i(position->x + _moves[min_deg_idx].x, position->y + _moves[min_deg_idx].y);

	//mark that move
	board[nextPoint.x][nextPoint.y] = board[position->x][position->y] + 1;

	return nextPoint;
}

bool KnightsTourSolver::SolveFunctionBruteForce(Vector2i location, int moveNumber, int width, int height, int ** board)
{
	if (moveNumber == width * height)
		return true;
	for (size_t i = 0; i < POSSIBLE_MOVES; i++)
	{
		Vector2i next = location + _moves[i];
		if (IsSafe(next, width, height, board)) {
			board[next.x][next.y] = moveNumber;
			if (SolveFunctionBruteForce(next, moveNumber + 1, width, height, board)) {
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

bool KnightsTourSolver::SolveRecursiveBruteForce(Vector2i startingPoint, int width, int height)
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
	if (SolveFunctionBruteForce(startingPoint, 1, width, height, _board)) {
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

bool KnightsTourSolver::SolveFunctionWarnsdorff(Vector2i startingPoint, int width, int height)//not function properly, ohhwell.
{
	//setup
	_board = new int*[width];
	for (size_t x = 0; x < width; x++)
	{
		_board[x] = new int[height];
		for (size_t y = 0; y < height; y++)
		{
			_board[x][y] = -1;
		}
	}
	//start point needs to start as 0
	_board[startingPoint.x][startingPoint.y] = 0;

	Vector2i position = Vector2i(startingPoint);

	//keeping picking next points using Warnsdorff's  heursitic
	for (int i = 0; i < width*height; i++) {
		printf("\nTHIS LINE: %i : { %i, %i}\n", i, position.x, position.y);
		position = NextMove(_board, &position, width, height);
		if (position.x == -1) {

			printf(" >>> Not possible! <<< ");
			return false;
		}
	}

	if (!Neighbour(startingPoint, position)) {
		printf(" >>> Not Neightbors! <<< ");
		return false;
	}

	printf(" >>> Successful! <<< ");
	//setup the linked list
	BuildLinkedList(_linkedList, _board, width, height);

	return true;
}

KnightsTourSolver::KnightsTourSolver()
{
}

KnightsTourSolver::~KnightsTourSolver()
{
}

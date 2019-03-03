#include "ChessBoard.h";
#include "Possition.h";
#include <cstdlib>;
#include <iostream>
#include <iomanip>

using namespace std;

ChessBoard::ChessBoard(RenderWindow &window)
{
	_width = window.getSize().x / _boardTileCount; 
	_height = window.getSize().y / _boardTileCount;
	_knightRenderer.Initialize("Textures/Knight.png", _width, _height, _startingPosition);

	_sprites.emplace_back(&_knightRenderer);
	InitializeTiles(_width, _height);
	//if (_solver.SolveFunctionWarnsdorff(_startingPosition, _boardTileCount, _boardTileCount)) {//currently not working.
	if (_solver.SolveRecursiveBruteForce(_startingPosition, _boardTileCount, _boardTileCount)) {
		PrintBoardState(_solver._board);
		_solver._linkedList.display();
		_currentGoalNode = _solver._linkedList.GetHead();
	}

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear(Color(255, 255, 255, 255));
		Update();
		Draw(window);
		LateUpdate();
		window.display();
	}
}

void ChessBoard::InitializeTiles(int width, int height)
{
	
	for (int x = 0; x < _boardTileCount; x++)
	{
		for (int y = 0; y < _boardTileCount; y++)
		{
			RectangleShape tile(Vector2f(width, height));
			tile.setPosition(x * width, y * height);

			Color c = ((x + y) % 2) == 0 ? Color(50, 50, 50, 255) : Color(0, 100, 100, 255);
			tile.setFillColor(c);

			_tiles.emplace_back(tile);
		}
	}
}

void ChessBoard::PrintBoardState(int ** _state)
{
	int number = _boardTileCount * _boardTileCount;
	int digits = 0; 
	do { number /= 10; digits++; } while (number != 0);
	cout << "\n ";
	for (int i = 0; i < _boardTileCount * digits + 2; i++)
	{
		cout << "- ";
	}
	cout << "\n";
	for (int x = 0; x < _boardTileCount;x++) {
		cout << "| ";
		for (int y = 0; y < _boardTileCount;y++)
			cout << setw(digits) << setfill('0') << _state[y][x] << " | ";
		cout << "\n ";
		for (int i = 0; i < _boardTileCount * digits + 2; i++)
		{
			cout << "- ";
		}
		cout << "\n";
	}
}

void ChessBoard::Update()
{
	Time deltatime = _deltaClock.restart();
	for (vector<SpriteRenderer*>::iterator it = _sprites.begin();
		it < _sprites.end(); ++it)
	{
		(*it)->Update(deltatime);
	}
}

void ChessBoard::LateUpdate() {
	if (_knightRenderer.IsAtGoal()) {
		if (_currentGoalNode != NULL) {
			//send the knight to his next position
			if (_currentGoalNode->next != NULL) {
				_currentGoalNode = _currentGoalNode->next;
			}
			else {
				printf("Tour complete, going back to intial node\n");
				_currentGoalNode = _solver._linkedList.GetHead();
			}
			_knightRenderer.MoveTo(Vector2f(_currentGoalNode->data.x * _width, _currentGoalNode->data.y * _height));
		}
	}
}

void ChessBoard::Draw(RenderWindow &window)
{
	for (vector<RectangleShape>::iterator it = _tiles.begin();
		it != _tiles.end(); ++it)
	{
		window.draw(*it);
	}

	for (vector<SpriteRenderer*>::iterator it = _sprites.begin();
		it != _sprites.end(); ++it)
	{
		(*it)->Draw(window);
	}
	DrawChessBoard(window);
}

void ChessBoard::DrawChessBoard(RenderWindow &window)
{

}

ChessBoard::~ChessBoard()
{
	//delete everything on the heap.
}

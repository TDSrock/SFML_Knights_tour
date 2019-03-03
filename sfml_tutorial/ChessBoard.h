#ifndef _CHESSBOARD_
#define _CHESSBOARD_

#include <SFML\Graphics.hpp>
#include "Knight.h"
#include "KnightsTourSolver.h"

using namespace sf;
using std::vector;

class ChessBoard
{
private:
	int								_boardTileCount = 6;//tiles in both dimensions
	Vector2i						_startingPosition = Vector2i(0, 0); //starting possition for knights tour solving
	vector<RectangleShape>			_tiles;
	vector<SpriteRenderer*>			_sprites;
	Knight							_knightRenderer;
	Clock							_deltaClock;
	Uint32							_width, _height;
	KnightsTourSolver				_solver;
	void PrintBoardState(int** _state);
	void Update();
	void LateUpdate();
	void InitializeTiles(int w, int h);
	void Draw(RenderWindow &window);
	void DrawChessBoard(RenderWindow &window);

public:
	ChessBoard(RenderWindow &window); //constructor
	~ChessBoard(); //destructor
};

#endif

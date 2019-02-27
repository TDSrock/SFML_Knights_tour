#ifndef _CHESSBOARD_
#define _CHESSBOARD_

#include <SFML\Graphics.hpp>
#include "Knight.h"

using namespace sf;
using std::vector;

class ChessBoard
{
private:
	int							_boardTileCount = 4;
	Vector2i					_startingPosition = Vector2i(3, 2); //starting possition
	int**						_boardState;
	vector<RectangleShape>		_tiles;
	vector<SpriteRenderer*>		_sprites;
	Knight						_knightRenderer;
	Clock						_deltaClock;
	Uint32						_width, _height;
	void PrintBoardState(int** _state);
	void Update();
	void InitializeTiles(int w, int h);
	void Draw(RenderWindow &window);
	void DrawChessBoard(RenderWindow &window);

public:
	ChessBoard(RenderWindow &window); //constructor
	~ChessBoard(); //destructor
};

#endif

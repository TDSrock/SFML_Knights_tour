#include "ChessBoard.h";
#include "Possition.h";
#include <cstdlib>;

ChessBoard::ChessBoard(RenderWindow &window)
{
	

	_width = window.getSize().x / _boardTileCount; 
	_height = window.getSize().y / _boardTileCount;
	_knightRenderer.Initialize("Textures/Knight.png", _width, _height, _startingPosition);

	_sprites.emplace_back(&_knightRenderer);
	InitializeTiles(_width, _height);

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
		window.display();
	}
}

void ChessBoard::InitializeTiles(int width, int height)
{
	_boardState = new int*[_boardTileCount];
	
	for (int x = 0; x < _boardTileCount; x++)
	{
		_boardState[x] = new int[_boardTileCount];
		for (int y = 0; y < _boardTileCount; y++)
		{
			//setup the boardstate intialy for each index to -1
			_boardState[x][y] = -1;

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
	for (size_t i = 0; i < _boardTileCount; i++)
	{
		for (size_t j = 0; j < _boardTileCount; j++)
		{

		}
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
	if (_knightRenderer.IsAtGoal()) {
		sleep(sf::seconds(0.5f));
		_knightRenderer.MoveTo(Vector2f((rand() % (_boardTileCount)) * _width, (rand() % (_boardTileCount)) * _height));
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

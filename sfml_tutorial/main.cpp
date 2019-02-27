#include <SFML\Graphics.hpp>;
#include "ChessBoard.h";
#include <iostream>;
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(1024, 1024), "SFML Tutorial", Style::Titlebar | Style::Close);
	window.setFramerateLimit(60);	
	std::cout << "Start\n";
	ChessBoard board(window);
	return 0;
}
#include "SpriteRenderer.h"

void SpriteRenderer::Initialize(String path, float width, float height)
{
	_rectangle = RectangleShape(Vector2f(width, height));
	_rectangle.setPosition(Vector2f(0, 0));

	_texture.loadFromFile(path);
	_rectangle.setTexture(&_texture);
}

void SpriteRenderer::Update(Time deltaTime)
{
	_rectangle.setPosition(this->_position);
}

void SpriteRenderer::Draw(RenderWindow &window)
{
	window.draw(_rectangle);
}
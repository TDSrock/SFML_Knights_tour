//make sure that this header file is only defined once
#ifndef _SPRITERENDERER_
#define _SPRITERENDERER_

#include <SFML\Graphics.hpp>

//include namespaces that we know we are going to use a lot. 
using namespace sf;

	class SpriteRenderer
	{
	protected:
		Vector2f		_position;
		RectangleShape	_rectangle;
		Texture			_texture;

	public:
		void Initialize(String path, float width, float height);
		virtual void Update(Time deltaTime);
		virtual void Draw(RenderWindow &window);
	};
#endif
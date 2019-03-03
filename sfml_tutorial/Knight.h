#ifndef _KNIGHT_ //make sure that this header file is only defined once
#define _KNIGHT_
#include "SpriteRenderer.h";
	//if not public, the inheriting of SpriteRenderer would make this Update function inaccessible
	//for further information, see https://bit.ly/2OGCENo and https://bit.ly/2GcOk9S
	class Knight : public SpriteRenderer
	{
	private:
		float _ignoreUpdateSeconds = 0;//used to keep the knight standing still for a bit
	public:
		Vector2i _arrayPosition;
		Vector2f _goalPosition;
		float _speed;
		void Initialize(String path, float width, float height, Vector2i startingPos);
		//override the Update function from SpriteRenderer
		void Update(Time deltaTime);
		void MoveTo(Vector2f goal);
		bool IsAtGoal();
	};
#endif
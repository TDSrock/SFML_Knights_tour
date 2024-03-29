#include "Knight.h";
#include <math.h>;

void Knight::Initialize(String path, float width, float height, Vector2i startingPos)
{
	_speed = 500 / width * height;//speed is relative to the size of the knight
	_arrayPosition = startingPos;
	_position = Vector2f(startingPos.x * width, startingPos.y * height);
	SpriteRenderer::Initialize(path, width, height);
	_goalPosition = Vector2f(startingPos.x * width, startingPos.y * height);
}

void Knight::Update(Time deltaTime)
{
	//call the base class's Update function
	SpriteRenderer::Update(deltaTime);
	if (_ignoreUpdateSeconds >= 0) {
		_ignoreUpdateSeconds-= deltaTime.asSeconds();
		return;
	}
	//update the knight's position
	//if the knight is not where we want him to be
	if (_goalPosition != _position) {
		float frameSpeed = _speed * deltaTime.asSeconds();
		Vector2f delta = _goalPosition - _position;
		float distance = sqrtf(delta.x * delta.x + delta.y * delta.y);
		//printf("distance is now %f, closing in with %f speed\n", distance, frameSpeed);
		if (distance <= frameSpeed) {
			//if our speed would get us there, set us there
			//printf("Reached destination\n\n");
			_position = _goalPosition;
			//printf("Ne: {%f, %f}\n", _goalPosition.x, _goalPosition.y);
			//printf("Neo: {%f, %f}\n", _position.x, _position.y);
		}
		else {
			//otherwise keep moving closer
			Vector2f normal = delta / distance;
			_position += frameSpeed * normal;
		}
	}
}

void Knight::MoveTo(Vector2f goal)
{
	_ignoreUpdateSeconds = 0.5f;
	_goalPosition = goal;
	printf("New move to command, moving to: {%f, %f}\n", goal.x, goal.y);
	printf("That maps to array possitions: {%i, %i}\n", static_cast<int>(goal.x / _rectangle.getSize().x), static_cast<int>(goal.y / _rectangle.getSize().y));
}

bool Knight::IsAtGoal()
{
	return _goalPosition == _position;
}


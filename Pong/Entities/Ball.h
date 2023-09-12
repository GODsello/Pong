#pragma once

#include "../GameObject/GameObject.h"
#include "../Constants.h"
#include "Player.h";
#include <vector>

class Ball : public GameObject
{
public:
	Ball(unsigned int id,
		float xPos, float yPos, float width, float height, 
		float velocity, float* deltaTime);

	void Render(SDL_Renderer* renderer);
	void Update();

	void OnCollision(SDL_Rect collision);

private:
	float xDir, yDir;
	float velocity;
	float* deltaTime;
};


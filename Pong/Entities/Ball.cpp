#include "Ball.h"

Ball::Ball(unsigned int id,
	float xPos, float yPos, float width, float height, float velocity, float *deltaTime)
	:GameObject(id, xPos, yPos, width, height)
{
	rect.x = xPos;
	rect.y = yPos;
	rect.w = width;
	rect.h = height;

	this->deltaTime = deltaTime;
	this->velocity = velocity;

	srand((unsigned)time(NULL));

	yDir = rand() % 10 < 5 ? -0.5f : 0.5f;
	xDir = rand() % 10 < 5 ? -1.0f : 1.0f;
}

void Ball::Render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
}

void Ball::Update()
{
	xPos += xDir * velocity * *deltaTime;
	yPos += yDir * velocity * *deltaTime;


	// Stops ball for getting stuck in the border
	if (yPos < 0.0f)
	{
		yPos = 1.0f;
		yDir *= -1.0f;
	}
	if (yPos + height > SCREEN_HEIGHT)
	{
		yPos = SCREEN_HEIGHT - height - 1.0f;
		yDir *= -1.0f;
	}

	rect.x = xPos;
	rect.y = yPos;
}

void Ball::OnCollision(SDL_Rect collision)
{
	velocity += 0.03f;
	float midBall = rect.y + rect.h / 2.0f;
	float midCollided = collision.y + collision.h / 2.0f;

	yDir = midBall < midCollided ? -0.5 : 0.5;

	yPos += yDir * velocity * *deltaTime;
	xPos -= xDir * velocity * *deltaTime;
	xDir *= -1;
}
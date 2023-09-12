#include "Player.h"

Player::Player(unsigned int id,
	float xPos, float yPos, float width, float height, float velocity)
	:GameObject(id, xPos, yPos, width, height)
{
	this->xPos = xPos;
	this->yPos = yPos;
	this->velocity = velocity;
	rect.x = xPos;
	rect.y = yPos;
	rect.w = width;
	rect.h = height;
}

void Player::Render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &rect);
}

void Player::Update()
{

}

void Player::MoveUp(float deltaTime)
{
	yPos -= velocity * deltaTime;
	if (yPos < 0) {
		yPos = 0;
	}
	rect.y = yPos;
}

void Player::MoveDown(float deltaTime)
{
	yPos += velocity * deltaTime;
	if (yPos + rect.h > SCREEN_HEIGHT) {
		yPos = SCREEN_HEIGHT - rect.h;
	}
	rect.y = yPos;
}

void Player::OnCollision(SDL_Rect collision) 
{

}
#include "AI.h"

AI::AI()
{
	this->handledPlayer = nullptr;
	this->ball = nullptr;
	this->threshold = 10.0f;
}

AI::AI(Player* player, Ball* ball, float threshold)
{
	this->handledPlayer = player;
	this->ball = ball;
	this->threshold = threshold;
}

AI::~AI()
{
	handledPlayer = nullptr;
	ball = nullptr;
}

void AI::MovePlayer(float deltaTime)
{
	if (ball->GetXDir() > 0.0f && ball->GetRect()->x > SCREEN_WIDTH / 2.0f)
	{
		float midBall = ball->GetRect()->y + ball->GetRect()->h / 2.0f;
		float midPlayer = handledPlayer->GetRect().y + handledPlayer->GetRect().h / 2.0f;

		if (midBall > midPlayer + threshold)
		{
			handledPlayer->MoveDown(deltaTime);
		}
		else if(midBall < midPlayer - threshold) {
			handledPlayer->MoveUp(deltaTime);
		}
	}
}
#pragma once

#include "../Entities/Ball.h";
#include "../Entities/Player.h";

class AI
{
public:
	AI();
	AI(Player* player, Ball* ball, float threshold);
	~AI();

	/*
		Moves player based on ball position and direction
	*/
	void MovePlayer(float deltaTime);

private:
	Player* handledPlayer;
	Ball* ball;

	float threshold;
};


#pragma once

#include <SDL.h>
#include <vector>
#include <string>
#include <SDL_ttf.h>

#include "Window.h";
#include "GameObject/GameObject.h";
#include "Entities/Ball.h";
#include "Entities/Player.h";
#include "AI/AI.h";
#include "Score.h";

#include "Constants.h";

class App
{
public:
	App();
	~App();

	bool OnInit();
	void OnLoop();
	void OnUpdate();
	void OnShutdown();
	void HandleEvents();

	void CheckCollisions();

	void LoadEntities();

private:
	void DeleteEntities();
	bool CheckWin();

	Window* window;
	float deltaTime;
	std::vector<GameObject*> entities;
	Player* player;
	Player* playerRight;
	Ball* ball;

	AI* ai;
	Score* score;
	Font* font;

	bool hasWin;
	bool hasMoved;
	bool pause;
};


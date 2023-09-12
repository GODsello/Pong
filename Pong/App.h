#pragma once

#include <SDL.h>
#include <vector>

#include "Window.h";
#include "GameObject/GameObject.h";
#include "Entities/Ball.h";
#include "Entities/Player.h";

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
	Window* window;
	float deltaTime;
	std::vector<GameObject*> entities;
	Player* player;
	Player* playerRight;
};


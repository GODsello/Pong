#include "App.h"

App::App(){
	window = new Window();
	player = nullptr;
	playerRight = nullptr;
	deltaTime = 0.0f;
}

App::~App(){
	OnShutdown();
}

bool App::OnInit()
{
	return window->Init("Pong", SCREEN_WIDTH, SCREEN_HEIGHT);
}

void App::OnUpdate()
{
	for(GameObject * g : entities)
	{
		g->Update();
	}
}

void App::OnLoop()
{
	bool quit = false;
	
	SDL_Event event;

	while (!quit)
	{
		float startTime = SDL_GetTicks();
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		HandleEvents();

		OnUpdate();

		CheckCollisions();

		//Clear screen
		SDL_SetRenderDrawColor(window->GetRenderer(), 0x0, 0x00, 0x00, 0x00);
		SDL_RenderClear(window->GetRenderer());

		for (GameObject* g : entities)
		{
			g->Render(window->GetRenderer());
		}

		SDL_RenderPresent(window->GetRenderer());
		
		deltaTime = (SDL_GetTicks() - startTime);
		if (deltaTime < TICKS_PER_FRAME)
		{
			SDL_Delay(TICKS_PER_FRAME - deltaTime);
		}
		deltaTime = (SDL_GetTicks() - startTime);
	}
}

void App::CheckCollisions()
{
	for (GameObject* entity1 : entities) {
		for (GameObject* entity2 : entities)
		{
			if (entity1->GetId() == entity2->GetId())
			{
				continue;
			}

			if (SDL_HasIntersection(entity1->GetRect(), entity2->GetRect()))
			{
				entity1->OnCollision(*entity2->GetRect());
			}
		}
	}
}

void App::OnShutdown()
{
	entities.clear();

	delete window;
	window = nullptr;
}

void App::HandleEvents()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_W])
	{
		player->MoveUp(deltaTime);
	}
	if (currentKeyStates[SDL_SCANCODE_S]) {
		player->MoveDown(deltaTime);
	}
	if (currentKeyStates[SDL_SCANCODE_UP])
	{
		playerRight->MoveUp(deltaTime);
	}
	if (currentKeyStates[SDL_SCANCODE_DOWN]) {
		playerRight->MoveDown(deltaTime);
	}
}

void App::LoadEntities() {
	Ball* ball = new Ball(entities.size(),
		SCREEN_WIDTH/2.0f - ballConstants.width/2.0f , 
		SCREEN_HEIGHT/2.0f - ballConstants.height/2.0f,
		ballConstants.width, ballConstants.height, 
		0.5f, 
		&deltaTime);
	entities.push_back(ball);

	player = new Player(entities.size(), 
		SCREEN_WIDTH*(0.5f/10.0f), SCREEN_HEIGHT/2.0f - playerConstants.height/2.0f,
		playerConstants.width, playerConstants.height, 
		1.0f);
	entities.push_back(player);

	playerRight = new Player(entities.size(), 
		SCREEN_WIDTH * (9.5f / 10.0f),
		SCREEN_HEIGHT/2.0f - playerConstants.height/2.0f,
		playerConstants.width, playerConstants.height, 
		1.0f);
	entities.push_back(playerRight);
}
#include "App.h"

App::App(){
	window = new Window();
	player = nullptr;
	playerRight = nullptr;
	ball = nullptr;
	deltaTime = 0.0f;
	hasWin = false;
	hasMoved = false;
	ai = nullptr;
	score = nullptr;
	pause = false;
	font = nullptr;
	onePlayer = true;
}

App::~App(){
	OnShutdown();
}

bool App::OnInit()
{
	// Create window
	bool result = window->Init("Pong", SCREEN_WIDTH, SCREEN_HEIGHT);

	font = new Font(window->GetRenderer());
	result = font->LoadFont();
	score = new Score(font);
	mainMenu = new MainMenu(font);
	pauseMenu = new Pause(font);

	return result;
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
		if (hasWin)
		{
			LoadEntities();
		}

		float startTime = SDL_GetTicks();
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			{
				pauseMenu->ResetMenu();
				pause = !pause;
			}
			if (pause)
			{
				int pauseResult = pauseMenu->HandleMenuEvents(&event);
				switch (pauseResult)
				{
				case RESUME:
					pause = false;
					break;
				case QUIT:
					quit = true;
					break;
				default:
					break;
				}
			}
		}

		if (!pause)
		{
			HandleEvents();

			if (hasMoved)
			{
				OnUpdate();

				CheckCollisions();
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor(window->GetRenderer(), 0x0, 0x00, 0x00, 0x00);
		SDL_RenderClear(window->GetRenderer());

		score->RenderScore();

		for (GameObject* g : entities)
		{
			g->Render(window->GetRenderer());
		}

		if (pause)
		{
			pauseMenu->RenderMenu();
		}

		SDL_RenderPresent(window->GetRenderer());

		hasWin = CheckWin();
		if (hasWin)
		{
			DeleteEntities();
			hasMoved = false;
		}
		
		// FPS handle
		deltaTime = (SDL_GetTicks() - startTime);
		if (deltaTime < TICKS_PER_FRAME)
		{
			SDL_Delay(TICKS_PER_FRAME - deltaTime);
		}
		deltaTime = (SDL_GetTicks() - startTime);
	}
}

int App::OnMainMenuLoop()
{
	bool stopLoop = false;
	int selected = -1;

	SDL_Event event;

	while (!stopLoop)
	{
		float startTime = SDL_GetTicks();
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				stopLoop = true;
				selected = MAIN_QUIT;
			}
			if (selected < 0)
			{
				selected = mainMenu->HandleMenuEvents(&event);
				if (selected >= 0)
				{
					stopLoop = true;
				}
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor(window->GetRenderer(), 0x0, 0x00, 0x00, 0x00);
		SDL_RenderClear(window->GetRenderer());

		mainMenu->RenderMenu();

		SDL_RenderPresent(window->GetRenderer());

		deltaTime = (SDL_GetTicks() - startTime);
		if (deltaTime < TICKS_PER_FRAME)
		{
			SDL_Delay(TICKS_PER_FRAME - deltaTime);
		}
		deltaTime = (SDL_GetTicks() - startTime);
	}
	return selected;
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

	delete ai;
	ai = nullptr;

	delete score;
	score = nullptr;

	delete pauseMenu;
	pauseMenu = nullptr;

	delete font;
	font = nullptr;

	delete window;
	window = nullptr;
}

void App::HandleEvents()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_W])
	{
		player->MoveUp(deltaTime);
		hasMoved = true;
	}
	if (currentKeyStates[SDL_SCANCODE_S]) {
		player->MoveDown(deltaTime);
		hasMoved = true;
	}

	if (onePlayer)
	{
		ai->MovePlayer(deltaTime);
	}
	else {
		if (currentKeyStates[SDL_SCANCODE_UP])
		{
			playerRight->MoveUp(deltaTime);
			hasMoved = true;
		}
		if (currentKeyStates[SDL_SCANCODE_DOWN]) {
			playerRight->MoveDown(deltaTime);
			hasMoved = true;
		}
	}
}

void App::ResetState(bool onePlayer)
{
	this->onePlayer = onePlayer;
	hasWin = false;
	pause = false;
	hasMoved = false;
	score->ResetScore();
}

void App::LoadEntities() {
	ball = new Ball(entities.size(),
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

	if (onePlayer)
	{
		ai = new AI(playerRight, ball, 20.0f);
	}
}

void App::DeleteEntities()
{
	for (GameObject* g : entities) {
		delete g;
	}
	entities.clear();

	ball = nullptr;
	player = nullptr;
	playerRight = nullptr;
}

bool App::CheckWin() 
{
	float ballPos = ball->GetRect()->x;
	float ballWidth = ball->GetRect()->w;

	if (ballPos + ballWidth < 0.0f)
	{
		score->AddPlayerRightScore();
		return true;
	}

	if (ballPos + ballWidth > SCREEN_WIDTH)
	{
		score->AddPlayerScore();
		return true;
	}

	return false;
}
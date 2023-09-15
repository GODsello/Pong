#pragma once

#include "../Font/Font.h";

class MainMenu
{
public:
	MainMenu(Font* font);
	~MainMenu();

	int HandleMenuEvents(SDL_Event* e);
	void RenderMenu();
	void ResetMenu() { selected = MAIN_ONE_PLAYER; };
private:
	Font* font;
	LTexture* title;
	LTexture* onePlayer;
	LTexture* twoPlayers;
	LTexture* quit;
	LTexture* onePlayerSelected;
	LTexture* twoPlayersSelected;
	LTexture* quitSelected;

	int selected;

};


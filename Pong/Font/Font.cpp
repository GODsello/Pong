#include "Font.h"

Font::Font(SDL_Renderer* renderer)
{
	smallFont = nullptr;
	mediumFont = nullptr;
	bigFont = nullptr;
	this->renderer = renderer;
}

bool Font::LoadFont()
{
	smallFont = TTF_OpenFont("Font/pixelfont.ttf", SMALL_FONT);
	if (smallFont == NULL)
	{
		printf("Failed to load smallFont SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	mediumFont = TTF_OpenFont("Font/pixelfont.ttf", MEDIUM_FONT);
	if (mediumFont == NULL)
	{
		printf("Failed to load mediumFont SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	bigFont = TTF_OpenFont("Font/pixelfont.ttf", BIG_FONT);
	if (bigFont == NULL)
	{
		printf("Failed to load bigFont SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	return true;
}

LTexture* Font::CreateTexture(int fontSize, std::string text, SDL_Color color)
{
	SDL_Surface* surface = nullptr;
	switch (fontSize)
	{
	case SMALL_FONT:
		surface = TTF_RenderText_Solid(smallFont, text.c_str(), color);
		break;
	case MEDIUM_FONT:
		surface = TTF_RenderText_Solid(mediumFont, text.c_str(), color);
		break;
	case BIG_FONT:
		surface = TTF_RenderText_Solid(smallFont, text.c_str(), color);
		break;
	default:
		surface = TTF_RenderText_Solid(smallFont, text.c_str(), color);
		break;
	}

	if (surface == NULL) return NULL;

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == NULL) return NULL;

	LTexture* tex = new LTexture();
	tex->width = surface->w;
	tex->height = surface->h;
	tex->texture = texture;

	SDL_FreeSurface(surface);

	return tex;
}

void Font::RenderTexture(LTexture* texture, int xPos, int yPos) 
{
	SDL_Rect srcRect = { 0, 0, texture->width, texture->height };
	SDL_Rect dstRect = { xPos, yPos, texture->width, texture->height };

	SDL_RenderCopy(renderer, texture->texture, &srcRect, &dstRect);
}

void Font::ClearTexture(LTexture* texture)
{
	if (texture != NULL && texture->texture != NULL)
	{
		SDL_DestroyTexture(texture->texture);
		delete texture;
	}
}

Font::~Font()
{
	TTF_CloseFont(smallFont);
	TTF_CloseFont(mediumFont);
	TTF_CloseFont(bigFont);
	smallFont = nullptr;
	mediumFont = nullptr;
	bigFont = nullptr;
	renderer = nullptr;
}
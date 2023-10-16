#pragma once

#include <string>
#include <sstream>

#include "Font/Font.h";

class Score
{
public:
	Score(Font* font);
	~Score();

	/*
		Adds 1 to the left player score
	*/
	void AddPlayerScore();

	/*
		Adds 1 to the right player score
	*/
	void AddPlayerRightScore();

	/*
		Sets both scores to zero
	*/
	void ResetScore();

	/*
		Renders score text texture
	*/
	void RenderScore();


private:
	/*
		Destroys font and texture
	*/
	void ClearTexture();

	/*
		Updates score texture to new value
	*/
	void UpdateScoreText();

	unsigned int playerScore;
	unsigned int playerRightScore;

	Font* font;
	LTexture* texture;

	std::ostringstream scoreText;
};


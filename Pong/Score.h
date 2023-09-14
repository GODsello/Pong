#pragma once

#include <string>
#include <sstream>
#include "Font/Font.h";

class Score
{
public:
	Score(Font* font);
	~Score();

	void AddPlayerScore();
	void AddPlayerRightScore();

	void RenderScore();

	void ResetScore();

private:
	unsigned int playerScore;
	unsigned int playerRightScore;

	Font* font;
	LTexture* texture;

	std::ostringstream scoreText;

	void ClearTexture();
	void UpdateScoreText();
};


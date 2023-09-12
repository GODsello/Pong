#pragma once

const float SCREEN_WIDTH = 1024;
const float SCREEN_HEIGHT = 768;

const int FPS = 60;
const int TICKS_PER_FRAME = 1000 / FPS;

//const char* TITLE = "Pong";

struct {
	float width = 20.0f;
	float height = 20.0f;
} ballConstants;

struct {
	float width = 20.0f;
	float height = 150.0f;
} playerConstants;
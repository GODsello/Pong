#include "App.h";

int main(int argc, char* args[])
{
	App app;
	if (app.OnInit())
	{
		app.LoadEntities();
		app.OnLoop();
		app.OnShutdown();
	}
	return 0;
}
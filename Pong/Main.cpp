#include "App.h";

int main(int argc, char* args[])
{
	App app;
	if (app.OnInit())
	{
		int selected = -1;
		while (selected != MAIN_QUIT)
		{
			selected = app.OnMainMenuLoop();
			if (selected != MAIN_QUIT)
			{
				app.ResetState(selected == MAIN_ONE_PLAYER);
				app.LoadEntities();
				app.OnLoop();
				app.DeleteEntities();
			}
		}
		app.OnShutdown();
	}
	return 0;
}
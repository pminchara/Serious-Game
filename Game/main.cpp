#include"Game.h"

int main()
{
	const int GLmajorVersion = 4;
	const int GLminorVersion = 4;

	Game game("SeriousGame", 1920, 1080, GLmajorVersion, GLminorVersion, false);

	//main loop
	while (!game.getWindowShouldClose())
	{
		//update input
		game.update();
		game.render();
	}

	return 0;
}
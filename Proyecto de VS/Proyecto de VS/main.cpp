#include "GameController.h"

#define FONT_PATH "C:\\Windows\\Fonts\\arial.ttf"

using namespace sf;

int main()
{
	srand(time(NULL));

	GameController gameController;

	gameController.MainLoop();

    return 0;
}

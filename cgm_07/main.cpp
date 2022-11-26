#include <iostream>
#include "settings.h"

bool windowCreate(Settings);
bool windowLoop(double*);
void windowDestroy();

bool graphicsStart(Settings);
void graphicsLoop();
void graphicsTerminate();

void gameLoad(Settings);
void gameLoop(double);
void gameUnload();

int main()
{
    std::cout << "Engine starting...\n";

    Settings settings = Settings();

    if (windowCreate(settings) && graphicsStart(settings))
    {
        gameLoad(settings);
        double dtime = 0;
        while (windowLoop(&dtime))
        {
            gameLoop(dtime);
            graphicsLoop();
        }
        gameUnload();
        graphicsTerminate();
        windowDestroy();
    }

    std::cout << "Engine terminated.\n";

    return 0;
}
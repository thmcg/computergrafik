#include <iostream>
#include "settings.h"

bool windowCreate(Settings);
bool windowLoop();
void windowDestroy();

bool graphicsStart(Settings);
void graphicsLoop();
void graphicsTerminate();

int main()
{
    std::cout << "Engine starting...\n";

    Settings settings = Settings();

    if (windowCreate(settings) && graphicsStart(settings))
    {
        while (windowLoop())
        {
            graphicsLoop();
        }
        graphicsTerminate();
        windowDestroy();
    }

    std::cout << "Engine terminated.\n";

    return 0;
}
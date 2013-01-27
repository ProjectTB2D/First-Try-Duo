#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "src/global.h"
#include "src/Core.h"

int main()
{

    g_core = new Core();
    g_core->run();

    delete g_core;

    return 0;
}

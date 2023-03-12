#include <grrlib.h>
#include <stdlib.h>

#include "misc/splashscreens.h"

int main(int argc, char **argv) {
    // Initialise the Graphics & Video subsystem
    GRRLIB_Init();

    // Initialise the Wiimotes
    WPAD_Init();

    SplashScreens();

    GRRLIB_Exit();
    exit(0);
}
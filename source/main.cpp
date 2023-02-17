#include <grrlib.h>

#include <stdlib.h>
#include <wiiuse/wpad.h>

#include "SplashScreen_Sacrebleu_jpg.h"

GRRLIB_texImg *GFX_SplashScreenSacrebleu;

int main(int argc, char **argv) {
    // Initialise the Graphics & Video subsystem
    GRRLIB_Init();

    // Initialise the Wiimotes
    WPAD_Init();

    //Load splashscreen
    GFX_SplashScreenSacrebleu = GRRLIB_LoadTextureJPG(SplashScreen_Sacrebleu_jpg);

    // Set up fade effect
    int alpha = 0;
    bool fading_in = true;

    // Loop forever
    while(1) {

        GRRLIB_DrawImg( 0, 0, GFX_SplashScreenSacrebleu, 0, 1, 1, RGBA(255,255,255,alpha));

        WPAD_ScanPads();  // Scan the Wiimotes

        // If [HOME] was pressed on the first Wiimote, break out of the loop
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_A) {
            fading_in = false;
        }

        // ---------------------------------------------------------------------
        // Place your drawing code here
        // ---------------------------------------------------------------------


        // Update alpha value
        if (fading_in) {
            alpha += 5;
            if (alpha >= 255) {
                alpha = 255;
            }
        } else {
            alpha -= 5;
            if (alpha <= 0) {
                alpha = 0;
            }
        }

        GRRLIB_Render();  // Render the frame buffer to the TV
    }

    GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB

    exit(0);  // Use exit() to exit a program, do not use 'return' from main()
}

#include <grrlib.h>

#include <stdlib.h>
#include <wiiuse/wpad.h>
#include <vector>

#include "SplashScreen_Sacrebleu_jpg.h"
#include "SplashScreen_leReminder_png.h"

// Declare static functions
static void ExitGame();

static std::vector<GRRLIB_texImg *> SplashScreenList;
GRRLIB_texImg *GFX_SplashScreenSacrebleu;
GRRLIB_texImg *GFX_SplashScreenleReminder;

int main(int argc, char **argv) {
    // Initialise the Graphics & Video subsystem
    GRRLIB_Init();

    // Initialise the Wiimotes
    WPAD_Init();

    //Load splashscreens
    GFX_SplashScreenleReminder = GRRLIB_LoadTexturePNG(SplashScreen_leReminder_png);
    GFX_SplashScreenSacrebleu = GRRLIB_LoadTextureJPG(SplashScreen_Sacrebleu_jpg);
    SplashScreenList = { GFX_SplashScreenleReminder, GFX_SplashScreenSacrebleu };

    // Set up fade effect
    int splashScreenIndex = 0;
    int alpha = 0;
    bool fading_in = true;

    // Loop forever
    while(1) {

        if (splashScreenIndex <= 1)
        GRRLIB_DrawImg( 0, 0, SplashScreenList[splashScreenIndex], 0, 1, 1, RGBA(255,255,255,alpha));

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
                splashScreenIndex += 1;
                if(splashScreenIndex <= 1)
                    fading_in = true;
            }
        }

        GRRLIB_Render();  // Render the frame buffer to the TV
    }

    ExitGame();
    return 0;
}

static void ExitGame() {
    // Free all memory used by textures.
    for (auto &TexIter : SplashScreenList) {
        GRRLIB_FreeTexture(TexIter);
    }
    SplashScreenList.clear();

    // Deinitialize GRRLIB & Video
    GRRLIB_Exit();

    // Exit application
    exit(0);
}

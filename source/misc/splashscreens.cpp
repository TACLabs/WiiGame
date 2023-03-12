#include "splashscreens.h"
#include "SplashScreen_Sacrebleu_jpg.h"
#include "SplashScreen_leReminder_png.h"

// Define the variable
std::vector<GRRLIB_texImg *> SplashScreenList;

void SplashScreens() {
    GRRLIB_texImg *GFX_SplashScreenSacrebleu = GRRLIB_LoadTextureJPG(SplashScreen_Sacrebleu_jpg);
    GRRLIB_texImg *GFX_SplashScreenleReminder = GRRLIB_LoadTexturePNG(SplashScreen_leReminder_png);
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
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)
            break;

        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_A)
            fading_in = false;

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
    
    FreeSplashScreens();
}

void FreeSplashScreens() {
    // Free all memory used by textures.
    for (auto &TexIter : SplashScreenList) {
        GRRLIB_FreeTexture(TexIter);
    }
    SplashScreenList.clear();
}
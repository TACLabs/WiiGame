#ifndef SPLASHSCREENS_H
#define SPLASHSCREENS_H

#include <grrlib.h>
#include <wiiuse/wpad.h>
#include <vector>

// Declare the variable as extern
extern std::vector<GRRLIB_texImg *> SplashScreenList;

void SplashScreens();
void FreeSplashScreens();

#endif // SPLASHSCREENS_H
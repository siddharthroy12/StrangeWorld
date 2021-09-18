#ifndef APP_HPP
#define APP_HPP

#include "raylib.h"

#ifdef IMPL

bool shouldExit = false;
Vector2 mousePos = { 0 };

#else

extern bool shouldExit;
extern Vector2 mousePos;

#endif

#endif
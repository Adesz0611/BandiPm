/*
 *  (C) 2020 Adam Hunyadvari
 *      <adesz@jss.hu>
 */
#pragma once
#include "curses.h"
typedef struct _Logo {
    char *filename;
} Logo;

Logo logo;

void logo_draw(WINDOW *win, int xMax);

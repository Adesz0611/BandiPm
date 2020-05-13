/*
 *  (C) 2020 Adam Hunyadvari
 *      <adesz@jss.hu>
 */
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "curses.h"

void curses_init(void)
{
    curses = (Curses *)malloc(sizeof(*curses));
    memset(curses, 0, sizeof(*curses));

    initscr();
    cbreak();
    noecho();
    curs_set(0);
}

void curses_resize(int signr)
{
    
}

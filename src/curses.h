/*
 *  (C) 2020 Adam Hunyadvari
 *      <adesz@jss.hu>
 */
#pragma once
#include <ncurses.h>
typedef struct {
    int termX;
    int termY;
} Curses;

Curses *curses;

void curses_init(void);

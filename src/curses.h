/*
 *  (C) 2020 Adam Hunyadvari
 *      <adesz@jss.hu>
 */
#pragma once
#include <ncurses.h>

#ifdef __unix__
#include <signal.h>
#endif

typedef struct {
    int termX;
    int termY;
} Curses;

Curses *curses;

void curses_init(void);
int curses_checkTerminalHasColors(void);
int curses_checkTerminalSize(void);
#ifdef __unix__
#ifdef SIGWINCH
void curses_resize(int signr);
#endif
#endif
void curses_clean(void);

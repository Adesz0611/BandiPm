/*
 *  (C) 2020 Adam Hunyadvari
 *      <adesz@jss.hu>
 */
#ifndef DRAW_H
#define DRAW_H

#include "curses.h"
#ifdef __unix__
#include <signal.h>
#endif

void draw_logo(WINDOW *win, int xMax);
void draw_printMiddle(char *text, int y, WINDOW *win, int xWinMax);
void draw_menu(WINDOW *win, int highlight, char *choices[], int xWinMax, int choices_num);
void draw_quitmenu(WINDOW *win, int highlight, int yAsk, int xAsk);
void draw_options(WINDOW *win, int highlight, bool askbefq, int yMax, int xMax, int beatbutton_options);
void draw_creator(WINDOW *win, int yWinMax, int xWinMax, char *copyright);

#endif /* DRAW_H */

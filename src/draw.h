/* Created by Adesz */
#include "main.h"

#ifdef __unix__
#include <signal.h>
#endif

void draw_logo(WINDOW *win, int xMax);
// TODO: this function shouldn't be here
#ifdef __unix__
#ifdef SIGWINCH
void draw_resize(int signr);
#endif
#endif
void draw_printMiddle(char *text, int y, WINDOW *win, int xWinMax);
void draw_menu(WINDOW *win, int highlight, char *choices[], int xWinMax, int choices_num);
void draw_quitmenu(WINDOW *win, int highlight, int yAsk, int xAsk);
void draw_options(WINDOW *win, int highlight, bool askbefq, int yMax, int xMax, int beatbutton_options);
void draw_creator(WINDOW *win, int yWinMax, int xWinMax, char *copyright);

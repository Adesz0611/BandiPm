/* Created by Adesz */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <ncurses.h>

void init_screen();
void init_checkTerminalHasColors();
void init_cleanup();
void init_checkTerminalSize(int yMax, int xMax);
void init_configFile(FILE *conf, bool *askbefq, int *beatbutton);

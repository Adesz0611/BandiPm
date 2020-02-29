/* Created by Adesz */
#include "init.h"

void init_screen()
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
}

void init_checkTerminalHasColors()
{
	if(!has_colors())
	{
		endwin();
		printf("Terminal does not support colors!\n");
		exit(1);
	}
}

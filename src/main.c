/* Created by Adesz */
#include "main.h"
#include "init.h"
#include "draw.h"
#include "structs.h"

int yMax, xMax, winyMax, winxMax;

int main (int argc, const char *argv[]) {
	// Initialize
	init_screen();
	init_checkTerminalHasColors();

	// Return the max size of terminal
	getmaxyx(stdscr, yMax, xMax);
	
	// Create main window
	WINDOW *win = newwin(yMax-2, xMax-6, 1, 3);
	winyMax = getmaxyx(win, winyMax, winxMax);

	logo.filename = "logo.txt";
	draw_logo(win, xMax);
	
	// Draw window border
	box(win, 0, 0);
	refresh();
	wrefresh(win);

	// Clear and close
	getch();
	getch();
	endwin();

	return 0;
}

/* Created by Adesz */
#include "main.h"
#include "init.h"
#include "draw.h"
#include "input.h"

int yMax, xMax, yWinMax, xWinMax;
char *choices[] = { "  Start  ", " Options ", "  About  ", "   Quit  " };
int choice, highlight = 0;

int main (int argc, const char *argv[]) {
	// Initialize
	init_screen();
	init_checkTerminalHasColors();

	// Return the max size of terminal
	getmaxyx(stdscr, yMax, xMax);
	
	// Create main window
	WINDOW *win = newwin(yMax-2, xMax-6, 1, 3);
	getmaxyx(win, yWinMax, xWinMax);

	logo.filename = "logo.txt";
	draw_logo(win, xMax);
	
	// Draw window border
	box(win, 0, 0);
	refresh();
	wrefresh(win);

	keypad(win, true);

	// Menu loop
	while(1)
	{
		draw_menu(win, highlight, choices, xWinMax);
		choice = wgetch(win);
		input(choice, &highlight);
		if(choice == 10)
			{
				if(choices[highlight] == choices[3])
					break;
			}
	}

	// Clear and close
	endwin();

	return 0;
}

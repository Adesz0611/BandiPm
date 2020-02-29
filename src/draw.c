/* Created by Adesz */
#include "draw.h"
#include <stdint.h>

void draw_logo(WINDOW *win, int xMax)
{
	FILE *file = fopen(logo.filename, "r");
	if(file != NULL)
		{
			int row = 3;
			char line[128];
			while (fgets(line, sizeof line, file) != NULL)
				{
					mvwprintw(win, row, xMax / 2 - 62 / 2, "%s", line);
					row++;
				}
			fclose(file);
		}
	else
		{
			perror(logo.filename);
		}
}

void draw_printMiddle(char *text, int y, WINDOW *win, int xWinMax)
{
	mvwprintw(win, y, xWinMax / 2 - strlen(text) / 2, text);
}

void draw_menu(WINDOW *win, int highlight, char *choices[], int xWinMax)
{
	for(int i = 0; i < 4; i++)
		{
			if(i == 0)
				wattron(win, A_BOLD);
			if(i == highlight)
				wattron(win, A_REVERSE);
			mvwprintw(win, i + 12, xWinMax / 2 - strlen(choices[i]) / 2, choices[i]);
				wattroff(win, A_REVERSE);
				wattroff(win, A_BOLD);
		}
}

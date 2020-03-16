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

void draw_menu(WINDOW *win, int highlight, char *choices[], int xWinMax, int choices_num)
{
	for(int i = 0; i < choices_num; i++)
		{
			// Make "Start" text Bold
			if(i == 0)
				wattron(win, A_BOLD);
			if(i == highlight)
				wattron(win, A_REVERSE);
			mvwprintw(win, i + 12, xWinMax / 2 - strlen(choices[i]) / 2, choices[i]);
				wattroff(win, A_REVERSE);
				wattroff(win, A_BOLD);
		}
}

void draw_quitmenu(WINDOW *win, int highlight, int yAsk, int xAsk)
{
	// IF highlighted is 0, so 'Igen'
	if(!highlight)
		wattron(win, A_REVERSE);
	mvwprintw(win, yAsk - 2, xAsk - 4 - 2 - 5, "Igen");
	wattroff(win, A_REVERSE);
	if(highlight)
		wattron(win, A_REVERSE);
	mvwprintw(win, yAsk - 2, xAsk - 3 - 2, "Nem");
	wattroff(win, A_REVERSE);
}

void draw_creator(WINDOW *win, int yWinMax, int xWinMax, char *copyright)
{
	mvwprintw(win, yWinMax - 2, xWinMax - strlen(copyright) - 2, copyright);
}

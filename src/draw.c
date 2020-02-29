#include "draw.h"

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

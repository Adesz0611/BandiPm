/* Created by Adesz */
#include "input.h"

void input(int choice, int *highlight)
{	
	switch(choice)
		{
			case KEY_UP:
				*highlight = *highlight - 1;
			if(*highlight == -1)
				*highlight = 0;
			break;

			case KEY_DOWN:
				*highlight = *highlight + 1;
			if(*highlight == 4)
				*highlight = 3;
			break;
			
			default:
				break;
		}
}

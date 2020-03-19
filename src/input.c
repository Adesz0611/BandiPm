/* Created by Adesz */
#include "input.h"
#include <stdint.h>

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

void input_quitmenu(int choice, int *highlight)
{
	switch(choice)
		{
			case KEY_LEFT:
				*highlight = *highlight - 1;
				if(*highlight < 0)
					*highlight = 0;
				break;
			case KEY_RIGHT:
				*highlight = *highlight + 1;
				if(*highlight > 1)
					*highlight = 1;
				break;
			default:
				break;
		}
}

void input_options(int choice, int *highlight, bool *askbefq)
{
	switch(choice)
		{
			case KEY_UP:
				*highlight = *highlight - 1;
				if(*highlight < 0)
					*highlight = 0;
				break;
			case KEY_DOWN:
				*highlight = *highlight + 1;
				if(*highlight > 3)
					*highlight = 3;
				break;
			case KEY_LEFT:
				if(!*highlight)
					*askbefq = !*askbefq;
				else if(*highlight == 3)
					*highlight = *highlight - 1;
				break;
			case KEY_RIGHT:
				if(!*highlight)
					*askbefq = !*askbefq;
				else if(*highlight == 2)
					*highlight = *highlight + 1;
				break;
		}
}

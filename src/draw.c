/*
 *  (C) 2020 Adam Hunyadvari
 *      <adesz@jss.hu>
 */
#include <stdint.h>
#include <string.h>
#include "draw.h"
#include "curses.h"

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
    // IF highlighted is 0, so 'Yes'
    if(!highlight)
        wattron(win, A_REVERSE);
    mvwprintw(win, yAsk - 2, xAsk - 4 - 2 - 5, "Yes");
    wattroff(win, A_REVERSE);
    if(highlight)
        wattron(win, A_REVERSE);
    mvwprintw(win, yAsk - 2, xAsk - 3 - 2, "No");
    wattroff(win, A_REVERSE);
}

void draw_options(WINDOW *win, int highlight, bool askbefq, int yMax, int xMax, int beatbutton_options)
{
    // "Ask before quit" option
    if(highlight == 0)
    {    
        for(int i = 0; i < 7; i++)
            mvwprintw(win, 4, 23 + i, " ");
        wattron(win, A_REVERSE);
    }
    
    if(askbefq)
        mvwprintw(win, 4, 23, "<True>");
    else
        mvwprintw(win, 4, 23, "<False>");
    wattroff(win, A_REVERSE);
    
    if(highlight == 1)
        wattron(win, A_REVERSE);
    if(beatbutton_options == 10) // 10 = ENTER
        mvwprintw(win, 5, 23, "ENTER (%d)", beatbutton_options);
    else
        mvwprintw(win, 5, 23, "%c (%d)", (int)beatbutton_options, beatbutton_options);
    wattroff(win, A_REVERSE);

    if(highlight == 2)
        wattron(win, A_REVERSE);
    mvwprintw(win, yMax - 2, xMax - 13, "Apply");
    wattroff(win, A_REVERSE);

    if(highlight == 3)
        wattron(win, A_REVERSE);
    mvwprintw(win, yMax - 2, xMax - 6, "Quit");
    wattroff(win, A_REVERSE);
}

void draw_creator(WINDOW *win, int yWinMax, int xWinMax, char *copyright)
{
    mvwprintw(win, yWinMax - 2, xWinMax - strlen(copyright) - 2, copyright);
}

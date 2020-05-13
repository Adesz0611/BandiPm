/*
 *  (C) 2020 Adam Hunyadvari
 *      <adesz@jss.hu>
 */
#include "input.h"
#include "draw.h"
#include "logo.h"
#include <sys/time.h>
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

int input_fillBpmArray(int *i, struct timeval start, struct timeval stop, float *millisec, int *bpmInt, int (*ertek)[], WINDOW *bpm_win)
{
    for(*i = 9; *i > -1; (*i)--)
    {
        if(input_bpm(start, stop, millisec, bpmInt, ertek, *i, bpm_win))
            return 1;
        mvwprintw(bpm_win, 4, 7, "SZAMOLUNK! (%d)", *i);
    }

    return 0;
}

int input_bpm(struct timeval start, struct timeval stop, float *millisec, int *bpm, int (*ertek)[], int i, WINDOW *bpm_win)
{
    gettimeofday(&start, NULL);
    //while(wgetch(bpm_win) != 10);
    while(1)
    {
        switch(wgetch(bpm_win))
        {
            case 10:
                break;
            case (int)'q':
                return 1;
            default:
                continue;
        }
        break;
    }
    gettimeofday(&stop, NULL);
    *millisec = (float)(((long)((stop.tv_sec - start.tv_sec) * 1000000) + stop.tv_usec) - start.tv_usec);
    *millisec /= 1000000;
    *bpm = 60 / *millisec;
    (*ertek)[i] = *bpm;
    return 0;
}

void input_backToMain(WINDOW *actualWin, WINDOW *mainWin, int main_xMax)
{
    wclear(actualWin);
    wrefresh(actualWin);
    logo_draw(mainWin, main_xMax);
    box(mainWin, 0, 0);
    refresh();
}

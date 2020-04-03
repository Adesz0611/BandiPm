/* Created by Adesz */
#include "input.h"
#include "draw.h"
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

void input_bpm(struct timeval start, struct timeval stop, float *millisec, int *bpm, int ertek[], int i, WINDOW *bpm_win)
{
    gettimeofday(&start, NULL);
    wgetch(bpm_win);
    gettimeofday(&stop, NULL);
    *millisec = (float)(((long)((stop.tv_sec - start.tv_sec) * 1000000) + stop.tv_usec) - start.tv_usec);
    *millisec /= 1000000;
    *bpm = 60 / *millisec;
    ertek[i] = *bpm;
}

void input_backToMain(WINDOW *actualWin, WINDOW *mainWin, int main_xMax)
{
    wclear(actualWin);
    wrefresh(actualWin);
    draw_logo(mainWin, main_xMax);
    box(mainWin, 0, 0);
    refresh();
}

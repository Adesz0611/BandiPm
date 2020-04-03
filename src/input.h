/* Created by Adesz */
#include "main.h"

void input(int choice, int *highlight);
void input_quitmenu(int choice, int *highlight);
void input_options(int choice, int *highlight, bool *askbefq);
void input_bpm(struct timeval start, struct timeval stop, float *millisec, int *bpm, int ertek[], int i, WINDOW *bmp_win);
void input_backToMain(WINDOW *actualWin, WINDOW *mainWin, int main_xMax);

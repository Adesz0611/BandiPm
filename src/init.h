/*
 *  (C) 2020 Adam Hunyadvari
 *      <adesz@jss.hu>
 */
#pragma once
#include <stdio.h>
#include <stdbool.h>

void init_checkTerminalHasColors(void);
void init_cleanup(void);
void init_checkTerminalSize(int yMax, int xMax);
void init_configFile(FILE *conf, bool *askbefq, int *beatbutton);

/*
 *  (C) 2020 Adam Hunyadvari
 *      <adesz@jss.hu>
 */
#include <stdio.h>
#include <stdlib.h>

#include "init.h"
#include "curses.h"

void init_checkTerminalHasColors(void)
{
    if(!has_colors())
    {
        endwin();
        printf("Terminal does not support colors!\n");
        exit(1);
    }
}

void init_cleanup(void)
{
    endwin();
    exit(EXIT_SUCCESS);
}

void init_checkTerminalSize(int yMax, int xMax)
{
    if(yMax < 20 || xMax < 75)
    {
        endwin();
        printf("Terminal size is less than the min size!\n");
        exit(1);
    }
}

void init_configFile(FILE *conf, bool *askbefq, int *beatbutton)
{
    if((conf = fopen("bpmprog.dat", "rb")) == NULL)
    {
        conf = fopen("bpmprog.dat", "wb");
        fwrite(askbefq, sizeof(*askbefq), 1, conf);
        fwrite(beatbutton, sizeof(*beatbutton), 1, conf);
        fclose(conf);
        conf = fopen("bpmprog.dat", "rb");
    }
    fread(askbefq, sizeof(*askbefq), 1, conf);
    fread(beatbutton, sizeof(*beatbutton), 1, conf);
    fclose(conf);
}

void clean(void)
{
    endwin();
}

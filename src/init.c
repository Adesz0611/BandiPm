/*
 *  (C) 2020 Adam Hunyadvari
 *      <adesz@jss.hu>
 */
#include <stdio.h>
#include <stdlib.h>

#include "init.h"
#include "curses.h"

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

/*
 *  (C) 2020 Adam Hunyadvari
 *      <adesz@jss.hu>
 */
#include <stdio.h>
#include "version.h"

void version_print(void)
{
    printf("%s version: %s\n", PROGRAM_NAME, VERSION);
}

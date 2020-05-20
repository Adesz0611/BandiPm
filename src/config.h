/*
 *  (C) 2020 Adam Hunyadvari
 *      <adesz@jss.hu>
 */
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CONF_PATH "bpmprog.dat"

typedef struct _Config{
   FILE *file; // File that will be contain the config
   
   // Ask before quit
   bool askbefq_buffer; // This will be the buffer, that you overwrite in options menu
   bool askbefq_file; // This will be written to config file
   wchar_t beatbutton_buffer;
   wchar_t beatbutton_file;
} Config;

Config *config;

void config_init(void);
void config_load(void);
void config_save(void);

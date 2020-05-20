/*
 *  (C) 2020 Adam Hunyadvari
 *      <adesz@jss.hu>
 */
#include <string.h>

#include "config.h"
#include "defs.h"

void config_init(void)
{
    config = (Config *)malloc(sizeof(config));
    memset(config, 0, sizeof(*config));
}

void config_load(void)
{
    if((config->file = fopen(CONF_PATH, "rb")) == NULL)
    {
        // If file doesn't exist make it
        config->file = fopen(CONF_PATH, "wb");

        // Prepare variables that will be written to config file
        config->askbefq_file = true;
        config->beatbutton_file = ENTER;

        // Finally, write default configs to file
        fwrite(&config->askbefq_file, sizeof(config->askbefq_file), 1, config->file);
        fwrite(&config->beatbutton_file, sizeof(config->beatbutton_file), 1, config->file);

        // Then close the config file
        fclose(config->file);
    }
    else
    {
        // If file exist then load the configs
        fread(&config->askbefq_file, sizeof(config->askbefq_file), 1, config->file);
        fread(&config->beatbutton_file, sizeof(config->beatbutton_file), 1, config->file);

        // Then close the config file
        fclose(config->file);
    }
}

void config_save(void)
{
    config->file = fopen(CONF_PATH, "wb");
    
    fwrite(&config->askbefq_file, sizeof(config->askbefq_file), 1, config->file);
    fwrite(&config->beatbutton_file, sizeof(config->beatbutton_file), 1, config->file);
    
    fclose(config->file);
}

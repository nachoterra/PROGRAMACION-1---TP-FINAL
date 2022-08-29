/* 
 * File:   file_admin.c
 * Author: gonzalo 
 * Created on 13 de diciembre de 2018, 17:14
 */

#include "file_admin.h"


uint8_t* read_config (uint8_t *file_name,FILE *file, uint8_t array_copied[])
{
    uint8_t *score,i;
    
    file = fopen (file_name,"r");
    if (file == NULL)
    {
        fprintf (stderr, "El archivo no existe");
        return (NULL);
    }
    else 
    {
        score = (fgets(array_copied,MAX_LENGHT,file));
    }
    fclose (file);
    
    return score;
}


uint8_t modify_config (uint8_t *file_name, FILE *file, uint8_t array_to_write[])
{
    uint8_t i = 0;
    
    file = fopen (file_name,"w");
    if (file == NULL)
    {
        fprintf (stderr, "El archivo no existe");
        return 1;
    }
    else
    {
        while (array_to_write[i] != '\0')
        {
               putc (array_to_write[i],file);
               i++;
        }
    }
 
    fclose (file);
    return 0;
}



#include "defines.h"
#include "vars.h"

/* analise command */
static int str_begins_with(char** a, char* b)
{
    while(*b)
    {
        if(**a != *b)
            return 0;
        (*a)++;
        b++;
    }
    return 1;
}

int handle_command(char* str)
{
    if(str_begins_with(&str, "direction "))
    {
        if(str_begins_with(&str, "forward"))
        {
            direction = 1;
            return 1;
        }
        else
            if(str_begins_with(&str, "back"))
            {
                direction = 0;
                return 1;
            }
    }
    return 0;
}

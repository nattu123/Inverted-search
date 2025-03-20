#include "inv.h"1

Status search_database(char *arr)
{
    int index = hash_function(*arr);
    if(hash_table[index].hashlink == NULL)
    {
        return FAILURE;
    }
    mainnode_t *main_temp = hash_table[index].hashlink;
    while(main_temp)
    {
        
    }
}
#include "inv.h"

void save_database(char *arr)
{
    FILE *fptr = fopen(arr,"w");
    for(int i=0;i<Hash_Table_Size;i++)
    {
        mainnode_t *main_temp =  hash_table[i].hashlink;
        while(main_temp)
        {
            fprintf(fptr,"#%d;%s;%d;",i,main_temp->word,main_temp->filecount);
            subnode_t *sub_temp = main_temp->subnode_link;
            while(sub_temp)
            {
                fprintf(fptr,"%s;%d;",sub_temp->filename,sub_temp->word_count);
                sub_temp = sub_temp->subnode_link;
            }
            fprintf(fptr,"#\n");
            main_temp = main_temp->mainnode_link;
        }
    }
}
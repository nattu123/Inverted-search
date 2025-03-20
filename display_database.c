#include"inv.h"

void display_database()
{
    printf("------------INverted database----------------\n\n");
    printf("\n-------------------------------------------\n");
    for(int i=0;i<Hash_Table_Size;i++)
    {
        if(hash_table[i].hashlink == NULL)
        {
            continue;
        }
        else
        {
            mainnode_t *main_temp = hash_table[i].hashlink;
            while(main_temp)
            {
                subnode_t *sub_temp = main_temp->subnode_link;
                printf("word = %s, ",main_temp->word);
                while(sub_temp)
                {
                    printf("word count in file \"%s\" is %d\n",sub_temp->filename,sub_temp->word_count);
                    sub_temp = sub_temp->subnode_link;
                }
                main_temp = main_temp->mainnode_link;
            }
        }
        
    }
}
#include "inv.h"

Status search_database(char *arr)
{
    int index = hash_function(*arr);
    if (hash_table[index].hashlink == NULL)
    {
        return FAILURE;
    }

    mainnode_t *main_temp = hash_table[index].hashlink;
    while (main_temp)
    {
        if (strcmp(main_temp->word, arr) == 0)
        {
            printf("\n=============================================\n");
            printf("🔍 **Word Found!**\n");
            printf("📌 **Word:** \"%s\"  |  🗂 **Index:** %d\n", arr, index);
            printf("---------------------------------------------\n");

            subnode_t *sub_temp = main_temp->subnode_link;
            while (sub_temp)
            {
                printf("📄 **File:** %-15s | 🔢 **Occurrences:** %d\n",
                       sub_temp->filename, sub_temp->word_count);
                sub_temp = sub_temp->subnode_link;
                return SUCCESS;
            }
        }
        main_temp = main_temp->mainnode_link;
    }
    return FAILURE;
}

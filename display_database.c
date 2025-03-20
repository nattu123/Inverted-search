#include "inv.h"

void display_database()
{
    printf("\n");
    printf("==================================================\n");
    printf("|        📂 INVERTED SEARCH DATABASE 📂        |\n");
    printf("==================================================\n");

    int empty = 1;  // Flag to check if database is empty

    for (int i = 0; i < Hash_Table_Size; i++)
    {
        if (hash_table[i].hashlink == NULL)
        {
            continue;  // Skip empty indexes
        }

        empty = 0;  // Database is not empty

        printf("\n📌 **Index %d:**\n", i);  // Print index as a section

        mainnode_t *main_temp = hash_table[i].hashlink;
        while (main_temp)
        {
            printf("  🔹 **Word:** %-12s | 📂 **Files:** %d\n", main_temp->word, main_temp->filecount);
            printf("  -----------------------------------------\n");

            subnode_t *sub_temp = main_temp->subnode_link;
            while (sub_temp)
            {
                printf("    📄 File: %-15s | 📝 Word Count: %d\n", sub_temp->filename, sub_temp->word_count);
                sub_temp = sub_temp->subnode_link;
            }

            printf("  -----------------------------------------\n");
            main_temp = main_temp->mainnode_link;
        }
    }

    if (empty)
    {
        printf("\n🚨 **Database is empty!** Add words before displaying.\n");
    }

    printf("\n==================================================\n");
}

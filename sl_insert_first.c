#include "inv.h"

Status insert_first(slist **head,char *argv)
{
    slist *new_node = malloc(sizeof(slist));
    if(new_node == NULL)
    {
        printf("INFO : memory allocation failed\n");
        return FAILURE;
    }

    strcpy(new_node->arr,argv);
    new_node->next = *head;
    *head = new_node;
    return SUCCESS;
}

void print_list(slist *head)
{
    // printf("valid files added \n");

    while(head)
    {
        printf("%s\n",head->arr);
        head = head->next;
    }
}

#include "inv.h"

void delete_list(slist **head)
{
    slist *temp;

    while (*head)
    {
        temp = *head;            // Store the current node
        *head = (*head)->next;   // Move to the next node
        free(temp);              // Free the current node
    }

    *head = NULL;  // Ensure the head pointer is set to NULL after deletion
}


void delete_hashtable()
{
    for(int i =0;i<Hash_Table_Size;i++)
    {
        mainnode_t *main_temp = hash_table[i].hashlink;
        while(main_temp)
        {
            subnode_t *sub_temp = main_temp->subnode_link;
            while(sub_temp)
            {
                subnode_t *temp = sub_temp; // current node
                sub_temp = sub_temp->subnode_link; // next node
                free(temp); // free current node
            }
            mainnode_t *temp = main_temp;  
            main_temp = main_temp->mainnode_link;
            free(temp);
        }
        hash_table[i].hashlink = NULL;
    }
}
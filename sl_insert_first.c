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
    printf("valid files added \n");

    while(head)
    {
        printf("%s\n",head->arr);
        head = head->next;
    }
}
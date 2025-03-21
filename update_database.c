#include "inv.h"

Status validate_backupfile(char *arr)
{
    char *temp; 
    if(temp = strstr(arr,".txt"))
    {
        if(strcmp(temp,".txt")==0)return SUCCESS;
    }
    return FAILURE;
}

Status check_if_backupfile(FILE *fptr)
{
    fseek(fptr,0,SEEK_SET);
    if(fgetc(fptr) == '#')
    {
        fseek(fptr,-2,SEEK_END);
        if(fgetc(fptr) == '#')
        {
            printf("this file is a backup file\n");
            rewind(fptr);        
            return SUCCESS;
        }
        
    }
    return FAILURE;
}
Status check_if_in_flist(slist *head,char *fname)
{
    while(head)   
    {
        if(strcmp(head->arr,fname) == 0)return FAILURE;
        head = head->next;
    }
    return SUCCESS;
}

Status update_database(char *arr,slist **head)
{
    FILE *fptr = fopen(arr,"r");
    slist *new_head = NULL;
    if(fptr == NULL) 
    {
        printf("could not open the file \n");
    }
    char word[100], fname[50];
    int index;
    int file_count , wordcount; 
    
    if(check_if_backupfile(fptr) == SUCCESS)
    {
        while(fscanf(fptr,"#%d;%[^;];%d;",&index,word,&file_count)==3)
        {
            for(int i=1;i<=file_count;i++)
            {
                fscanf(fptr,"%[^;];%d;",fname,&wordcount);
                if(check_if_in_flist(new_head,fname) == SUCCESS)
                {
                    insert_first(&new_head,fname);
                    delete_from_list(head,fname);
                }
                else
                {
                    printf("the file \"%s\" is already present in the list\n",fname);
                }
            }
            fscanf(fptr,"#\n");
        }
    }
    create_database_parallel(new_head);
    printf("\n new_list \n");
    print_list(new_head);
    printf("\n f_list \n");
    print_list(*head);
    
    delete_list(&new_head);
    return SUCCESS;
}
                
                
void delete_from_list(slist **head, char *fname)
{
    if (*head == NULL)
    {
        return; // Empty list, nothing to delete
    }

    slist *temp = *head, *prev = NULL;

    //  Check if the first node needs to be deleted
    if (strcmp(temp->arr, fname) == 0)
    {
        *head = temp->next;
        free(temp);
        return;
    }

    //  Search for the node to be deleted
    while (temp != NULL && strcmp(temp->arr, fname) != 0)
    {
        prev = temp;
        temp = temp->next;
    }

    //If node was not found, return
    if (temp == NULL)
    {
        
        return;
    }

    // Unlink and delete the node
    prev->next = temp->next;
    free(temp);

printf("File \"%s\" deleted from the list.\n",fname);
}

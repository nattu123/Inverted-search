#include "inv.h"

int hash_function(char c)
{
    if(c>='A' && c<='Z')return c-'A';
    else if(c>='a' && c<='z')return c-'a';
    else if(c>='0' && c<='9')return 26;
    else return 27;

}

Status create_database(slist *head)
{
    while(head != NULL)
    {
        FILE *fptr; 
        fptr = fopen(head->arr,"r");
        if(fptr == NULL)
        {
            printf("error in opening the file %s",head->arr);
            return FAILURE;
        }
        printf("\nin file %s\n",head->arr);

        char arr[50];
        while(fscanf(fptr,"%49s",arr) == 1)
        {
            insert_into_hashtable(arr,head->arr);
        }
        fclose(fptr);
        head = head->next;
    }
    return SUCCESS;
}

Status insert_into_hashtable(char *arr,char *fname)
{
    int index = hash_function(*arr); // finding index
    printf("Inserting word: '%s' from file: '%s' at index: %d\n", arr, fname, index);
    mainnode_t *temp = hash_table[index].hashlink;

    while(temp)
    {
        if(strcmp(arr,temp->word)==0)
        {
            subnode_t *sub_temp = temp->subnode_link;

            while (sub_temp)
            {
                if(strcmp(sub_temp->filename,fname)==0)
                {
                    sub_temp->word_count++;
                    return SUCCESS;
                }
                sub_temp = sub_temp->subnode_link;
            }
            
            // if file note found create a new subnode
            subnode_t *new_sub_node = malloc(sizeof(subnode_t));
            if(!new_sub_node)
            {
                printf("subnode not created \n");
                return FAILURE;
            }

            new_sub_node->word_count = 1 ; 
            strcpy(new_sub_node->filename,fname);
            new_sub_node->subnode_link = temp->subnode_link;
            temp->subnode_link = new_sub_node;
            temp->filecount++;
            return SUCCESS;
        }
        temp = temp->mainnode_link; // next main node
    }

    // if word not found create a new mainnode
    mainnode_t *new_main_node = malloc(sizeof(mainnode_t));
    if(!new_main_node)
    {
        printf("memory allocation for the main noode failed");
        return FAILURE;
    }
    new_main_node->filecount = 1;  
    strcpy(new_main_node->word,arr);
    new_main_node->mainnode_link = hash_table[index].hashlink;
    hash_table[index].hashlink = new_main_node; // inserting recently created mainnode at first 
    new_main_node->subnode_link = NULL;
    // add this to the new subnode
    
    subnode_t *new_sub_node = malloc(sizeof(subnode_t));
    if(!new_sub_node)
    {
        printf("memeory allocation for subnode failed\n");
        free(new_main_node); // freess main node if memory allocation for subnode fails , prevennts memory leak in casse of failed mem allocation for subnode
        return FAILURE;
    }
    
    new_main_node->subnode_link = new_sub_node; // ataching subnode
    // subnode
    new_sub_node->subnode_link = NULL;
    new_sub_node->word_count = 1;
    strcpy(new_sub_node->filename,fname);
    return SUCCESS;
}


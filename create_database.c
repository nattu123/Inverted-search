#include "inv.h"

int hash_function(char c)
{
    if(c>='A' && c<='Z')return c-'A';
    else if(c>='a' && c<='z')return c-'a';
    else if(c>='0' && c<='9')return 26;
    else return 27;

}

void *insert_thread(void *arg)
{
    char *f_name = (char *)arg;
    FILE *fptr = fopen(f_name,"r");

    if(fptr == NULL)
    {
        printf("Eroor could not open file \"%s\" \n",f_name);
        return NULL;
    }
    char word[50];
    while(fscanf(fptr,"%s",word) == 1)
    {
        insert_into_hashtable(word,f_name);
    }
    fclose(fptr);
    return NULL;
}

Status create_database_parallel(slist *head)
{
    /* what if the files are so big and all the thread are occupied then it will get out of the inner while loop and
       wait for the threads to be completed */

    pthread_t threads[10]; // creating 10 threads , my device has 12 cores 
    int i;
    while(head)
    {
        i = 0;
        
        while(head && i<10)
        {
            if(pthread_create(&threads[i],NULL,insert_thread,head->arr) != 0)
            {
                printf("error could create thread for file : %s\n",head->arr);
                continue;
            }
            head = head->next;
            i++;
        }

        for(int j=0;j<i;j++)
        {
            pthread_join(threads[j],NULL);
        }
    }
}
// Status create_database(slist *head)
// {
//     while(head != NULL)
//     {
//         FILE *fptr; 
//         fptr = fopen(head->arr,"r");
//         if(fptr == NULL)
//         {
//             printf("error in opening the file %s",head->arr);
//             return FAILURE;
//         }
//         printf("\nin file %s\n",head->arr);

//         char arr[50];
//         while(fscanf(fptr,"%49s",arr) == 1)
//         {
//             insert_into_hashtable(arr,head->arr);
//         }
//         fclose(fptr);
//         head = head->next;
//     }
//     return SUCCESS;
// }



Status insert_into_hashtable(char *arr,char *fname)
{
    int index = hash_function(*arr); // finding index
    printf("Inserting word: '%s' from file: '%s' at index: %d\n", arr, fname, index);
    pthread_mutex_lock(&hash_table_mutex); // locking hashtable so other threads wont be accessing this 
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
                    pthread_mutex_unlock(&hash_table_mutex); // unlocking mutex before returning do that other threadscan use this hashtable
                    return SUCCESS;
                }
                sub_temp = sub_temp->subnode_link;
            }
            
            // if file note found create a new subnode
            subnode_t *new_sub_node = malloc(sizeof(subnode_t));
            if(!new_sub_node)
            {
                printf("subnode not created \n");
                pthread_mutex_unlock(&hash_table_mutex);
                return FAILURE;
            }
            
            new_sub_node->word_count = 1 ; 
            strcpy(new_sub_node->filename,fname);
            new_sub_node->subnode_link = temp->subnode_link;
            temp->subnode_link = new_sub_node;
            temp->filecount++;
            pthread_mutex_unlock(&hash_table_mutex); // unlocking mutex 
            return SUCCESS;
        }
        temp = temp->mainnode_link; // next main node
    }

    // if word not found create a new mainnode
    mainnode_t *new_main_node = malloc(sizeof(mainnode_t));
    if(!new_main_node)
    {
        printf("memory allocation for the main noode failed");
        pthread_mutex_unlock(&hash_table_mutex); // unlocking mutex before returning 
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
        pthread_mutex_unlock(&hash_table_mutex); // unlocking mutex before returning 
        return FAILURE;
    }
    
    new_main_node->subnode_link = new_sub_node; // ataching subnode
    // subnode
    new_sub_node->subnode_link = NULL;
    new_sub_node->word_count = 1;
    strcpy(new_sub_node->filename,fname);
    pthread_mutex_unlock(&hash_table_mutex); // unlocking after modification 
    return SUCCESS;
}

#ifndef INV_H
#define INV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


#define Hash_Table_Size 28 

extern pthread_mutex_t hash_table_mutex; //declaring a global mutex 

typedef enum{
    FAILURE,
    SUCCESS
}Status;


typedef struct Slist
{
    char arr[50];
    struct Slist *next; 
    
}slist; 

typedef struct hash
{
    int key;
    struct mainnode *hashlink;
}Hash_t;

typedef struct mainnode
{
    int filecount;
    char word[50];
    struct mainnode *mainnode_link;
    struct subnode *subnode_link;
}mainnode_t;

typedef struct subnode
{
    struct subnode *subnode_link; 
    int word_count;
    char filename[50];
}subnode_t;

extern Hash_t hash_table[Hash_Table_Size];

Status read_and_validate(int argc,char **argv,slist **head);
Status file_availability(char *argv);
Status check_if_file_empty(char *argv,FILE *fptr);  
Status insert_first(slist **head,char *argv);
Status check_duplicate(char *argv, slist **head);
void print_list(slist *head);
Status create_database_parallel(slist *head);
Status insert_into_hashtable(char *arr,char *fname);
void display_database();
int hash_function(char c);
Status search_database(char *arr);
void save_database(char *arr);
Status validate_backupfile(char *arr);
Status update_database(char *arr,slist **head);
void delete_list(slist **head);
void delete_from_list(slist **head,char *fname);
void delete_hashtable();
#endif
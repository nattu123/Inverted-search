#ifndef INV_H
#define INV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Hash_Table_Size 28 

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
    char filename[50];
    int word_count;
    struct subnode *subnode_link; 
}subnode_t;

Status read_and_validate(int argc,char **argv,slist **head);
Status file_availability(char *argv);
Status check_if_file_empty(char *argv,FILE *fptr);  
Status insert_first(slist **head,char *argv);
Status check_duplicate(char *argv, slist **head);
void print_list(slist *head);

#endif
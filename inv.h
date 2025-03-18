#ifndef INV_H
#define INV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
    FAILURE,
    SUCCESS
}Status;


typedef struct Slist
{
    char arr[50];
    struct SList *next; 

}slist; 

Status read_and_validate(int argc,char **argv);

#endif
#include "inv.h"


int main(int argc , char **argv) 
{
    slist *head = NULL;
    if(argc<=1)
    {
        fprintf(stderr,"argument count shoul be greater than one\n");
        return FAILURE;
    }
    if(read_and_validate(argc,argv,&head) == FAILURE)
    {
        fprintf(stderr,"files should be of .txt format");
        return FAILURE;
    }
    else
    {
        printf("read aand validate finishedd\n");
    }
    
    print_list(head);
   
    printf("1.Create Database\n");  
    printf("2.Dispaly database\n");  
    printf("3.Search database\n");  
    printf("4.update database\n");  
    printf("5.save database\n");  
    printf("6.Exit\n");
    printf("enter the choice : ");

    Hash_t *hash_table[Hash_Table_Size] = {NULL};


    int option;
    scanf("%d",&option);

    switch(option)
    {
        // case 1 : create_database() ;
    }

}
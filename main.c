#include "inv.h"

Hash_t hash_table[Hash_Table_Size] ;

void hash_table_init(Hash_t *hash_table)
{
    for(int i=0;i<Hash_Table_Size;i++)
    {
        hash_table[i].hashlink = NULL;
        hash_table[i].key = i;

    }
}

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
    
    
    
    
    int option;
    hash_table_init(hash_table);
    while(1)
    {
        printf("enter the choice : ");
        scanf("%d",&option);
        switch(option)
        {
            case 1 : 
                create_database(head) ;
                break;
            case 2 : 
                display_database();
                break;
            case 5 :
                exit(0)    ;
                break;
        }
        
    }
}
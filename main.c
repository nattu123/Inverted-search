#include "inv.h"

pthread_mutex_t hash_table_mutex = PTHREAD_MUTEX_INITIALIZER; // initialising mutex can also use pthread_mutex_init()

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
    printf("4.save database\n");  
    printf("5.update database\n");  
    printf("6.Exit\n");
    
    
    
    
    int option;
    hash_table_init(hash_table);
    int flag_create =0;
    while(1)
    {
        printf("enter the choice : ");
        scanf("%d",&option);
        char arr[100];
        switch(option)
        {
            case 1 : 
                if(flag_create)
                {
                    printf("can only create datbase once otherwise it would leas to overwrite\n");
                    break;
                }
                create_database_parallel(head) ;
                flag_create =1;
                break;
            case 2 : 
                display_database();
                break;
            case 3 :
                printf("ENter the word to be searched for : ");
                scanf("%s",arr);
                if(search_database(arr) == FAILURE)
                {
                    fprintf(stderr,"The word not found in the database\n");
                }
                break;
            
            case 4 :
                printf("Enter the name of the backup file : ");
                scanf("%s",arr);
                save_database(arr);
                break;
            
            case 5 :
                if(flag_create)
                {
                    printf("daTABASE already created could not update\n");
                    break;
                }
                printf("NEter the backup file : \n");
                scanf("%s",arr);
                if(validate_backupfile(arr) == FAILURE)
                {
                    printf("enter a valid .txt file \n");
                    break;
                }
                else
                {
                    printf("Backup file is validated \n");
                    update_database(arr,&head);

                }
                break;

            
            case 6 :
                delete_list(&head);
                delete_hashtable();
                printf("hashtable and file list ddeleted\n");
                exit(0);
                break;
        }
        
    }
}
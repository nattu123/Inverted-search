#include "inv.h"

Status read_and_validate(int argc,char **argv,slist **head)
{
     for(int i = 1;i<argc;i++)
    {
        char *temp;
        if(temp = strstr(argv[i],".txt"))
        {
            if(strcmp(".txt",temp)==0)
            {
                printf(" The file %s is validated\n",argv[i]);
                if(file_availability(argv[i])==SUCCESS)
                {
                    check_duplicate(argv[i],head);
                }
                
            }
            else
            {
                printf(" The file %s is not valid and will be ignored \n",argv[i]);
                
            }
            
        }
        else
        {
            printf(" The file \"%s\" is not valid  \n",argv[i]);
            return FAILURE;
        }
    }
    return SUCCESS;
}


Status file_availability(char *argv)
{
    
    FILE *fptr;
    fptr = fopen(argv,"r");
    if(fptr == NULL)
    {
        printf("could nott open the file \"%s\" make sure that the file exists\n",argv);
        return FAILURE;
    }
    else
    {
        printf("succcesfully opened the file \"%s\"\n",argv);
        if(check_if_file_empty(argv,fptr)== SUCCESS)
        {
            printf("FIle \"%s\" is not emppty \n",argv);
            return SUCCESS;
        }
        else
        {
            printf("FIle \"%s\" is emppty \n",argv);
            return FAILURE; 

        }

    }
}   


Status check_if_file_empty(char *argv,FILE *fptr)
{
    fseek(fptr,0,SEEK_END);
    if(ftell(fptr)) return SUCCESS;
    else return FAILURE;
}

Status check_duplicate(char *argv, slist **head)
{
    slist *temp = *head;

    while(temp != NULL)
    {
        if(strcmp(argv,temp->arr) == 0)
        {
            printf(" duplicate found for \"%s\" \n\n",argv);
            return FAILURE;
        }
        temp = temp->next;
    }

    insert_first(head,argv);

    return SUCCESS;
}
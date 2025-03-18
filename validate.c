#include "inv.h"

Status read_and_validate(int argc,char **argv)
{
    for(int i = 1;i<argc;i++)
    {
        char *temp;
        if(temp = strstr(argv[i],".txt"))
        {
            if(strcmp(".txt",temp)==0)
            {
                printf(" The file %s is validated\n",argv[i]);
                return SUCCESS;
            }

        }
        return FAILURE;
    }
}

#include "inv.h"


int main(int argc , char **argv) 
{
    if(argc<=1)
    {
        fprintf(stderr,"argument count shoul be greater than one\n");
        return FAILURE;
    }
    if(read_and_validate(argc,argv) == FAILURE)
    {
        fprintf(stderr,"files should be of .txt format");
    }
    else
    {
        printf("read aand validate finishedd");
    }
}
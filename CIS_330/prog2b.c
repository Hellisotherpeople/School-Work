#include <stdio.h> 
#include <printf.h> 
#include <stdlib.h> 
//Author = Allen Roush 

int awrite(char *f_in, char *f_out)
{
    FILE *file_in, *file_out;
    int buffer_size; 
    int *buffer = malloc(5*sizeof(int)); 
    
    
    file_in = fopen(f_in, "r");
    file_out = fopen(f_out, "w"); // Open the file 
    
    for(int i = 0; i< 5; i++){
        fread(buffer, sizeof(int), 5, file_in);
        for(int j = 0; j < 5; j++)
        {
            fprintf(file_out, "%d\n", buffer[j]);
        }
        fseek(file_in, 5*sizeof(int), SEEK_CUR); 
    }
    
    
	
    fclose(file_in);
    fclose(file_out); 
    free(buffer);
    
    return 0;
}
        
        
        
        
int main(int argc, char *argv[])
{
    
     
    if (argc != 3) 
    {
        printf("Please provide 2 arguments, the input filename and the output filename"); 
        exit(EXIT_FAILURE);
    }
    

    awrite(argv[1], argv[2]);
    
}



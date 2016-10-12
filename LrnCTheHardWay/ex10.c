#include <stdio.h> 

int main(int argc, char *argv[])
{
    int i = 0; 
    
    //go through each string in argv (argc is the number of arguments held in the argv array, which starts at 0 being the name of the program) 
    for (i = 1; i < argc; i++) {
        printf("arg %d: %s\n", i, argv[i]);
    }
    
    // let's make our own array of strings 
    char *states[] = {
        "California", "Oregon", "Washington", "Texas"};
    states[3] = argv[3];
    int num_states = 5; 
    
    for( i = 0; i < num_states; i++){
        printf("state %d: %s\n", i, states[i]);
    }
    
    return 0; 
}
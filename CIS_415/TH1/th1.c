#include "p1fxns.h"
#include <stdlib.h> // remove these when finished 
#include <stdio.h> // remove these when finished 
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>



static int getprocesses(int num, char **args){
	int i;
	int r = 0;
	int found = 0; 
	char *toCompare = "--number="; 
	char *thenum = "";

	for (i = 1; i < num; i++){
		if (p1strneq(args[i], toCompare, 9)){ // search each command line arg for "--number="
				thenum = &args[i][9]; // accept the very first number after the = 
				found = 1; 
			}
		}
	r = p1atoi(thenum); // convert that to an int and return it if we got this far 
	


	if (found == 0 && getenv("TH_NPROCESSES") != NULL){ // look for enviroment variable and use that. 
		r = p1atoi(getenv("TH_NPROCESSES"));
	}

	if(r == 0){
			p1perror(2, "Failed to specify nonzero --number= \n");
	}

	//printf("r returned %d", r);
	return r; 
}


static int getprocessors(int num, char **args){
	int i, r;
	int found = 0; 
	char *toCompare = "--processors="; 
	char *thenum = "";

	for (i = 1; i < num; i++){
		if (p1strneq(args[i], toCompare, 13)){ 
				thenum = &args[i][13]; 
				found = 1; 
			}
		}
	r = p1atoi(thenum); 
	


	if (found == 0 && getenv("TH_NPROCESSORS") != NULL){ // look for enviroment variable and use that. 
		r = p1atoi(getenv("TH_NPROCESSSORS"));
	}
	//printf("r returned %d", r);
	return r; 
}

static char* getcommand(int num, char **args){
	int i;
	int found = 0;
	char *r; 
	char *toCompare = "--command="; 
	char *thecommand = "";

	for (i = 1; i < num; i++){
		if (p1strneq(args[i], toCompare, 10)){ 
				thecommand = &args[i][10];
				found = 1; 
			}
		}
	r = thecommand; 

	if (found == 0){
		p1perror(2, "Failed to specify --command= \n");
		exit(0); 
	}

	return r; 
}

static void createthread(int nprocesses, char* command){

	pid_t pid[nprocesses];
	int h = 0;
	int k; 

	char **earray = malloc(sizeof(char *) * 500);


	for (k = 0; k < 500; k++)
	{
		earray[k] = malloc(sizeof(char) * 100);
	}

	int cur_loc = 0; 
	cur_loc = p1getword(command, cur_loc, earray[h]);

	while(cur_loc != -1){
		//printf("%s\n", earray[h]);
		h++; 
		cur_loc = p1getword(command, cur_loc, earray[h]);
	}
	//h++;
	free(earray[h]);
	earray[h] = NULL; 


	int i = 0; 
	for (i = 0; i < nprocesses; i++){

		pid[i] = fork(); 

		if(pid[i] < 0){ // fail case 
			p1perror(2, "Fork failed to create process\n");
		}

		else if (pid[i] == 0){ // child process 
			if (execvp(earray[0], earray) < 0){
				p1perror(2, "execute failed\n");
				//exit(1);
			}
		}
		else { // parent 
			for(i = 0; i < nprocesses; i++){
			waitpid(pid[i], 0, 0);
			} 
		}
	}

	for (k = 0; k < 500; k++){
		free(earray[k]);
	}
	free(earray);
	
}


int main(int argc, char**argv) {  
	struct timeval stime; 
	struct timeval etime;
	char* pbuffer = (char*)malloc(sizeof(char) * 300); // for the putstr 

	int nprocesses = getprocesses(argc, argv);
	int nprocessors = getprocessors(argc, argv);
	char* command = getcommand(argc, argv);
	//printf("getprocesses returned: %d", nprocesses);
	//printf("getprocessors returned: %d", nprocessors);
	//printf("getcommand returned: %s\n", command);
	gettimeofday(&stime, NULL);
	createthread(nprocesses, command);
	gettimeofday(&etime, NULL);

	pbuffer[0] = 0;
  	p1putstr(1 , "The elapsed time to execute ");
  	p1itoa(nprocesses, pbuffer);
  	p1putstr(1 , pbuffer);
  	p1putstr(1, " copies of \"");
  	p1putstr(1, command);
  	p1putstr(1, "\" is: ");
  	int secs = (((etime.tv_sec - stime.tv_sec)*1000000L + etime.tv_usec) - stime.tv_usec)/1000000;
  	int msecs = (((etime.tv_sec - stime.tv_sec)*1000000L + etime.tv_usec) - stime.tv_usec)/1000 - secs * 1000;

  	p1itoa(secs, pbuffer);
  	p1putstr(1, pbuffer);
  	p1putstr(1, (char*)".");
  	if(msecs < 100){
    p1putstr(1, (char*)"0");
    if(msecs < 10)
      p1putstr(1, (char*)"0");
  	}
  	p1itoa(msecs, pbuffer);
  	p1putstr(1, pbuffer);
  	p1putstr(1, "\n");
  	free(pbuffer);


}





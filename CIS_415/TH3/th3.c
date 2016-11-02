#include "p1fxns.h"
#include <stdlib.h> // remove these when finished 
#include <stdio.h> // remove these when finished 
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

// FIGURE OUT TIMING SHIT!!!!!!!!!!! 
int sigrecieve; 

void sigusr1(int); // forward decleration 

void sigalarm(int signum);


void sigchild(int signum);



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

static void createthread(int nprocesses, int nprocessors, char* command){ 

	 struct sigaction sa;
 	 struct itimerval timer;

 	timer.it_value.tv_sec = 0;
 	timer.it_value.tv_usec = 250000;
 	timer.it_interval.tv_sec = 0;
 	timer.it_interval.tv_usec = 250000;

 	 memset (&sa, 0, sizeof (sa));
 	 sa.sa_handler = &sigalarm;
 	 sigaction (SIGALRM, &sa, NULL);


	if(signal(SIGUSR1, sigusr1) == SIG_IGN){
		signal(SIGUSR1, SIG_IGN);
	}

	pid_t pid[nprocesses];
	int h = 0;
	int k; 
	int amountused = 0;

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

//For loop for nprocessors to create as many processes as you have processors 
	//Where do I wait, stop and start at? 
	int j = 0; 
	int s = 0; 
	int queue = 0; 
	signal(SIGUSR1, sigusr1);
	for (i = 0; i < nprocesses; i++){

		pid[i] = fork(); 

		if(pid[i] < 0){ // fail case 
			p1perror(2, "Fork failed to create process\n");
		}

		else if (pid[i] == 0){ // child process 
			while(!sigrecieve){ // REMOVE THE PAUSE FROM TH2 AS WELL 
			}
			if (execvp(earray[0], earray) < 0){
				p1perror(2, "execute failed\n");
				//exit(1);
			}
		}
	}

	int stillrunning = 1;
	for (; stillrunning != 0; ){ 

		for (amountused = 0; amountused < nprocessors; amountused++){
			//printf("pid= %i\n", pid[queue]);
			if(pid[queue] != 0) {

			  printf("%i\n", pid[queue]);
				kill(pid[queue], SIGUSR1);
				//kill(pid[queue], SIGSTOP);
				kill(pid[queue], SIGCONT);
			  queue++; 
			  if (queue >= nprocesses){
			  	queue = 0; 
			  	break;
			  } 
			//printf("I didn't wait 250 seconds");
			//printf("I didn't wait 250 seconds again1"); 
			}

		}
		setitimer (ITIMER_REAL, &timer, NULL); // Wait for 250 seconds 
		for (s = 0; s < nprocesses ; s++){
		//kill(pid[s], SIGSTOP);
		}
		stillrunning = 0; 
		for(j = 0; j < nprocesses; j++){
		  stillrunning += (waitpid(pid[j], NULL, WNOHANG) == 0) ? 1 : 0; 
		  //printf("Stillrunning = %i\n", stillrunning);
	    }
	}
	//for (k = 0; k < 500; k++){
	//	free(earray[k]);
	//}
	//ffree(earray);
	
}


int main(int argc, char**argv) {  
	//signal(SIGALRM, sigalarm);
	struct timeval stime; 
	struct timeval etime;
	char* pbuffer = (char*)malloc(sizeof(char) * 300); // for the putstr 

	int nprocesses = getprocesses(argc, argv);
	int nprocessors = getprocessors(argc, argv);
	char* command = getcommand(argc, argv);

	gettimeofday(&stime, NULL);
	createthread(nprocesses, nprocessors, command);
	gettimeofday(&etime, NULL);

	pbuffer[0] = 0;
  	p1putstr(1 , "The elapsed time to execute ");
  	p1itoa(nprocesses, pbuffer);
  	p1putstr(1 , pbuffer);
  	p1putstr(1, " copies of \"");
  	p1putstr(1, command);
  	p1putstr(1, "\" on ");
  	p1itoa(nprocessors, pbuffer);
  	p1putstr(1, pbuffer);
  	p1putstr(1, " processors is ");
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




void sigusr1(int signum){
	(void)signum; // SHUT UP ABOUT WARNINGS 
	sigrecieve++; 
	//printf("Hello!24553 ");
}

void sigalarm(int signum){
	(void)signum;
	//printf("Hello!");
	// figure out what processes are running, and dump that in to a new global pid array 
	// kill(gpid[], SIGSTOP) // DO THIS ONLY ON RUNNING PROCESSES 
	// RR stuff 
	// implement a global int "core" which is the current CPU in the PID array 
	// cores = (cores % processes) // THIS IS THE RR scheduling  
	// START NEW SET (Send BOTH sigcont and Sigusr1)
}

void sigchild(int signum){
	(void)signum;
	// find way to get PID from child process
	// Create a new global that stores finished processes's. 
}
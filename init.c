#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define NPROCESOS 6

int p[NPROCESOS];

void sighand(int sig){
printf("aqui tenemos que terminar todos los procesos \n");
	for(int i=0;i<NPROCESOS;i++){
		kill(p[i],9);
	}
	
}

int main(){
	int i=0;
	char spid[5];
	int pid= getpid();
	
	signal(SIGUSR1,sighand);
	sprintf(spid,"%d",pid);
	printf("el pid de init es %d \n",pid);
	
	for(i=0;i<NPROCESOS;i++){
	p[i]=fork();
		if(p[i]==0)
			execlp("xterm","xterm","-e","./getty",spid,NULL);
	}
	
	//cuando uno de los procesoos xxterm termina, debe relanzarlo
	for(i=0;i<NPROCESOS;i++)
		wait(NULL);
	
}
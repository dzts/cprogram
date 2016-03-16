#include <stdio.h>
#include <unistd.h>

int main(){
	pid_t fpid;
	int count;
	fpid=fork();
	if( fpid < 0 ){
		printf("error in fork!");
	}else if( fpid == 0 ){
		printf("I am the child process,my process id is %d\n",getpid());
		count++;
	}else{
		printf("I am the parent process,my process id is %d\n",getpid());
		count++;
	}
	printf("total result is %d\n",count);
	sleep(30);
	return 0;
}

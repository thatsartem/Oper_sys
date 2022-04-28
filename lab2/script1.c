#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
int main(){
	pid_t pid1, pid2, pidparent;
	if ((pid1 = fork())==0)
	{
		pid1 = getpid();
		printf("Parent process 1: pid = %d\n", getppid());
		printf("Child process 1: pid = %d\n", pid1);
		return 0;
	}
	if ((pid2=fork())==0)
	{
		pid2=getpid();
		printf("Child process 2: pid = %d\n", pid2);
		printf("Parent process 2: pid = %d\n", getppid());
		return 0;
	}
	system("ps -x");
	time_t lt;
	lt = time(NULL);
	printf (ctime(&lt));
	pidparent = getpid();
	printf("Child process 1: pid = %d\n", pidparent);
	printf("Parent process: pid = %d\n", getppid());
}

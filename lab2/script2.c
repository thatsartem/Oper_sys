#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <string.h>
#include <stdlib.h>

void* thread_func (void* vargp)
	{
		printf("child thread id: %lu\n", syscall(SYS_gettid));
		printf("child pid: %d\n", getpid());
	}
int main(){
	pthread_t thread_id1;
	pthread_t thread_id2;
	printf("parent thread id: %lu\n", syscall(SYS_gettid));
	time_t lt;
	lt = time(NULL);
	printf(ctime(&lt));
	pthread_create(&thread_id1, NULL, thread_func, NULL);
	pthread_join(thread_id1,NULL);
	pthread_create(&thread_id2, NULL, thread_func, NULL);
	pthread_join(thread_id2,NULL);
	//system("ps -x");
}

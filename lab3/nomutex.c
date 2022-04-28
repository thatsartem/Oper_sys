#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>

int count = 0;

void* thread_function() {
	printf ("Thread id %lu\n", syscall(SYS_gettid));
	int i;
	for(i=0; i<2; i++) {
		count++;
		printf("Current number: %d, thread id: %lu\n", count, syscall(SYS_gettid));
		sleep(1);
	}
}

int main(){
	pthread_t th[6];
	int i;
	for(i=0; i<6; i++) {
		pthread_create(&th[i], NULL, &thread_function, NULL);
	}
	
	for(i=0; i<6; i++) {
		pthread_join(th[i], NULL);
	}
	
	printf("Result %d\n", count);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>

pthread_barrier_t barrier;

void* thread_function() {
	printf ("Thread id%lu\n", syscall(SYS_gettid));
	pthread_barrier_wait(&barrier);
	printf("Hello\n");
}

int main(){
	pthread_t th[6];
	pthread_barrier_init(&barrier, NULL, 6);
	int i;
	
	for(i=0; i<6; i++){
		pthread_create(&th[i], NULL, &thread_function, NULL);
	}
	
	for(i=0; i<6;i++){
		pthread_join(th[i], NULL);
	}
	
	pthread_barrier_destroy(&barrier);
	return 0;
}

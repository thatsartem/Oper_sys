#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <semaphore.h>

sem_t semaphore;

int count = 0;

void* thread_func() {

	
	sem_wait(&semaphore);
	printf("Thread: %lu is busy\n",syscall(SYS_gettid));
	for(int i = 0; i<5;i++){
		sleep(1);
		printf("%d ",i);
		
		
	}
	
	printf("\n");
	printf("Thread: %lu isn't busy\n",syscall(SYS_gettid));
	sem_post(&semaphore);
	
}

int main(){
	pthread_t th[8];
	sem_init(&semaphore, 0, 4);
	int i;
	
	for(i=0; i<8; i++) {
		pthread_create(&th[i], NULL, &thread_func, NULL);
	}
	for(i=0; i<8; i++) {
		pthread_join(th[i], NULL);
	}
	sem_destroy(&semaphore);
	return 0;
}

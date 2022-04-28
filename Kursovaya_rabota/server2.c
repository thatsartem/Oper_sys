#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "erproc.h"
#include <string.h>
#include <sys/sysinfo.h>
#include <time.h>



double fizMem(){
 struct sysinfo s_info;
 sysinfo(&s_info);
    double total = s_info.totalram * s_info.mem_unit;
    double free = s_info.freeram * s_info.mem_unit;
    double res = free/total * 100;
 return res;
}

int getUptime(){
	int s[2];
	pipe(s);
	if (fork() == 0) {
		close(s[0]);
		dup2(s[1],1);
		close(s[1]);
		execlp("uptime", "uptime", "uptime", "-p", NULL);
		perror("uptime");
		exit(1);
	}
	return s[0];
	
}
char result1[256]; 
char result2[256]; 
int main() { 

unsigned int start_time =  clock(); // начальное время

int server = Socket(AF_INET, SOCK_STREAM, 0); 

struct sockaddr_in adr = {0}; 
adr.sin_family = AF_INET; 
adr.sin_port = htons(12345); 

Bind(server, (struct sockaddr *) &adr, sizeof adr); 

Listen(server, 5); 

socklen_t adrlen = sizeof adr; 

int fd; 

while (1){
	fd = Accept(server, (struct sockaddr *) &adr, &adrlen); 
	while(1){ 
		int task;
		ssize_t nread; 
		char buf[256]; 
		nread = read(fd, buf, 256); 
		if (nread == -1) { 
		perror("read failed"); 
		break;
		} 
		if (nread == 0) { 
		printf("EOF occured\n"); 
		break;
		}
		
		if(atoi(buf) == 1) {
			unsigned int end_time = clock(); // конечное время
			unsigned int search_time = end_time - start_time; // искомое время
			sprintf(result1,"%d\n",search_time);
			write(fd, &result1, 256);
			write(STDOUT_FILENO, result1, nread); 
			}else{
			double desc = fizMem();
			sprintf(result2,"%f%%\n",desc);
			write(fd, &result2, 256);
			write(STDOUT_FILENO, result2, nread); 
			}
		}		

} 


close(fd); 
sleep(150); 


close(server); 
return 0; 
}

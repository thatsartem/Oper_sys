#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "erproc.h"
#include <string.h>


int getTimeZone(){
	int s[2];
	pipe(s);
	if (fork() == 0) {
		close(s[0]);
		dup2(s[1],1);
		close(s[1]);
		execlp("date", "date", "+\"%Z %z\"", NULL);
		perror("date");
		exit(1);
	}
	return s[0];
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
int server = Socket(AF_INET, SOCK_STREAM, 0); 

struct sockaddr_in adr = {0}; 
adr.sin_family = AF_INET; 
adr.sin_port = htons(34543); 

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
			int desc = getUptime(); 
			read(desc, result1 , 256);
			write(fd, &result1, 256);
			write(STDOUT_FILENO, result1, nread); 
			}else{
			int desc = getTimeZone();
			read(desc, result2, 256);
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

#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <unistd.h> 
#include "erproc.h" 
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
int cManager(){ 
	int serverNumber; 
	printf("Choose server :\n[1]Server_1\n[2]Server_2\nEnter_number : "); 
	scanf("%d", &serverNumber); 
	if( serverNumber == 1 ){ 
		return 34543; 
	} 
	if( serverNumber == 2 ){ 
		return 12345; 
	} 
	printf("Not valid number"); 
	return cManager(); 
}
 
int main() { 
	int fd = Socket(AF_INET, SOCK_STREAM, 0); 

	struct sockaddr_in adr = {0}; 
	adr.sin_family = AF_INET; 
	adr.sin_port = htons( cManager() ); 
	Inet_pton(AF_INET, "127.0.0.1", &adr.sin_addr); 
	Connect(fd, (struct sockaddr *) &adr, sizeof adr); 
	char str[16]; 

while(1){ 
	printf("Enter number of task: 1 or 2 ");
	char buf[255];
	scanf("%s", &buf);
	write(fd, buf, 255); 
	ssize_t nread; 
	sleep(1);
	nread = read(fd, buf, 255); 
	if (nread == -1) { 
	perror("read failed"); 
	} 
	if (nread == 0) { 
	printf("EOF occured\n"); 
	}
	write(STDOUT_FILENO, buf, nread); 
	 

} 
printf("PASSED"); 


close(fd); 
return 0; 
}

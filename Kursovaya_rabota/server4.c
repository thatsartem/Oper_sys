#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <sys/sysinfo.h>

#define PORT 12345
#include <time.h>

typedef struct{
	int time;
	int desc;
} args;
	
int curTime(){
	int s[2];
	pipe(s);
	if (fork() == 0) {
		close(s[0]);
		dup2(s[1],1);
		close(s[1]);
		execlp("date", "date", "+\"%T\"", NULL);
		perror("date");
		exit(1);
	}
	return s[0];
}


double fizMem(){
 struct sysinfo s_info;
 sysinfo(&s_info);
    double total = s_info.totalram * s_info.mem_unit;
    double free = s_info.freeram * s_info.mem_unit;
    double res = free/total * 100;
 return res;
}
int server_fd;

void stop()
{
 close(server_fd);
 exit(0);
}

char result1[222]={0}; 
char result2[222]={0}; 
char lastresult[222]= "ok";
void *handle_req(void *t_args)
{

 args* parset = t_args;
 int fd = parset->desc;
 ssize_t nread; 

 while (1)
 {
    char buf[255] = {0};

  nread = read(fd, buf, 255);
  if (nread == -1 || nread == 0)
  {
   break;
  }
  int desct = curTime();
  char ttime[20];
  read(desct, ttime, 20);
  char finanswer1[270] = "ok";
  char finanswer2[270] = "ok";
  
  if(atoi(buf) == 1) {
			unsigned int end_time = clock(); // конечное время
			unsigned int search_time = end_time - parset->time; // искомое время
			sprintf(result1,"%d\n",search_time);
			if (strcmp(result1,lastresult) != 0) {
			sprintf(finanswer1,"%s %s",result1,ttime);
			write(fd, finanswer1 , 256);
			write(STDOUT_FILENO, result1, nread); 
			strcpy(lastresult, result1);
			} else {
			write(STDOUT_FILENO, "Same Answer\n", 12);
			write(fd,"Same answer\n",12);
			}
			
			}else if (atoi(buf) == 2){
			double desc = fizMem();
			sprintf(result2,"%f%%\n",desc);
			if(strcmp(result2,lastresult) != 0){
			sprintf(finanswer2,"%s %s",result2,ttime);
			write(fd,finanswer2 , 256);
			write(STDOUT_FILENO, result2, nread); 
			strcpy(lastresult, result2);
			}else {
			write(STDOUT_FILENO, "Same Answer\n", 12);
			write(fd,"Same answer\n",12);
			}
			}else{
			stop(1);
			}
			


 }

 pthread_exit(NULL);
}

void main()
{
 const unsigned int start_time =  clock(); // начальное время
 signal(SIGINT, stop);

 int req_fd;
 struct sockaddr_in address;
 int addrlen = sizeof(address);

 if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
 {
  perror("socket failed");
  exit(1);
 }

 address.sin_family = AF_INET;
 address.sin_addr.s_addr = INADDR_ANY;
 address.sin_port = htons(PORT);

 if (bind(server_fd, (struct sockaddr *)&address,
    sizeof(address)) < 0)
 {
  perror("bind failed");
  exit(1);
 }
 if (listen(server_fd, 3) < 0)
 {
  perror("listen");
  exit(1);
 }

 printf("Server started on port %d\n", PORT);

 while (1)
 {
  pthread_t tid;

  if ((req_fd = accept(server_fd, (struct sockaddr *)&address,
        (socklen_t *)&addrlen)) < 0)
  {
   perror("accept");
   exit(1);
  }
  args t_args;
  t_args.time = start_time;
  t_args.desc = req_fd;
  pthread_create(&tid, NULL, handle_req, (void *)&t_args);
  printf("req_fd=%d, tid=%ld\n", req_fd, tid);
 }
}

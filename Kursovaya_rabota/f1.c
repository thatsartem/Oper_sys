
   #include <stdio.h>
   #include <unistd.h>
   #include <stdlib.h>
   #include <sys/sysinfo.h>

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
	
double fizMem(){
 struct sysinfo s_info;
 sysinfo(&s_info);
    double total = s_info.totalram * s_info.mem_unit;
    double free = s_info.freeram * s_info.mem_unit;
    double res = free/total * 100;
 return res;
}

int main() {
	
	char str[100];
	read(getTimeZone(),str,100);
	printf("%s",str);
	
	printf("%f%%\n",fizMem());
	
}




		

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv) {

	FILE *f;
	char s;
	char *p;
	char buf[150];
	char fileName[80];
	int pid;
	long conv = strtol(argv[2], &p, 10);
	
	pid = conv;
	
	if (argc < 3) {
		printf("Enter name of the file and pid of the process");
		return 0;
		}
		
	f = fopen(argv[1], "rw");
	if(!f){
		printf("file doesn't exist. will be create new with this name\n");
		if(!(f = fopen(argv[1], "w"))){
		printf("Can't open file\n");
		return 0;
		}
		sprintf(buf, "%s %d %s %s", "pmap", pid, " >> ", argv[1]);
		system(buf);
		printf("Wriing is done\n");
		} else {
		printf ("File is exists. you can replace him (1) or edit name of result file (2):\n");
		s = getchar();
		if (s == '1') {
			fclose(f);
			remove(argv[1]);
			f = fopen(argv[1], "w");
			sprintf(buf, "%s %d %s %s", "pmap", pid, " >> ", argv[1]);
			system(buf);
			fclose(f);
			printf("Writing is done\n");
			return 0;
			}
		else if (s == '2') {
			fclose(f);
			while (1) {
				printf("Enter unique filename :\n");
				scanf("%s", &fileName);
				f = fopen(fileName, "rw");
			  if(!f){
			  	if(!(f = fopen(fileName, "w"))){
			  		printf("Can't open file\n");
			  		return 0;}
			  	sprintf(buf, "%s %d %s %s", "pmap", pid, " >> ", fileName);
			  	system(buf);
			  	fclose(f);
			  	printf("Writing is done\n");
			  	return 0;
			  	}
			  else printf("File with such name already exists\n");
		     }
		} else {
			printf("You can print only 1 or 2");
			return 0;
		}
		}
}

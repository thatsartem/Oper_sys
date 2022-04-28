#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv) {
	FILE *f;
	char s;
	char *p;
	int n;
	
	long conv = strtol(argv[2], &p, 10);
	n = conv;
	
	if (argc < 3) {
		printf("Enter a fileName and kolichestvo strok v gruppe");
		return 0;
	}
	
	if (f = fopen(argv[1], "r")){
		if (strcmp(argv[2], "0") == 0){
			s = fgetc(f);
			while(s != EOF){
			printf("%c",s);
			s = fgetc(f);
			}
		}
		else{
			while(1){
				for(int i = 0; i < n;){
					s = fgetc(f);
					if (s != EOF) {
						while(s != '\n') {
							printf("%c",s);
							s = fgetc(f);
						}
						printf("\n");
						i++;
					} else
					if (feof(f) != 0){
						printf("Reading is done\n");
						return 0;
					}
					else {
						printf("Reading ERROR\n");
						return 0;
					}
				}
				printf("\nPress any key\n");
				getchar();
			}
			}
		fclose(f);
		} else{
			printf("Can't open file\n");
		}
		return 0;
}

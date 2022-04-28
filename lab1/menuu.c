#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>

int main(){
	system("echo \"current user:\"");
	system("whoami");
	system("echo \"\"");
	
	system("echo \"Used Memory:\"");
	system("free -m -l");
	system("echo \"\"");
	
	system("echo \"Disk space:\"");
	system("df -k");
	system("echo \"\"");

	system("echo \"Running processes:\"");
	system("ps -e");
	system("echo \"\"");

	system("echo \"Processes started by the cur user:\"");
	system("ps -u $(whoami)");
	system("echo \"\"");
	
	system("echo \"System date and time:\"");
	system("date -u");
	system("echo \"\"");

	system("echo \"System start time:\"");
	system("uptime");
	system("echo \"\"");

	system("echo \"Manual in command top:\"");
	system("man top");
	system("echo \"\"");
	
	system("echo \"Displaying the name of the current directory:\"");
	system("pwd");
	system("echo \"\"");
	
	system("echo \"Create a folder:\"");
	system("mkdir new_folder_FROM_MENU");
	system("ls");
	system("echo \"\"");
	
	system("echo \"Program version info:\"");
	system("free -V");
	system("echo \"\"");
	
		
	
}

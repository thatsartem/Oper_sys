#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include<string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include<fcntl.h>


 char ch[] = "SHMEM_FOLDER";

void* SOCKET_NAME;

int determinant(int n, int mat[n][n])
{
    int i,j,i_count,j_count, count=0;
    int array[n-1][n-1], det=0;
    if(n==1) return mat[0][0];
    if(n==2) return (mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0]);

    for(count=0; count<n; count++)
    {
        i_count=0;
        for(i=1; i<n; i++)
        {
            j_count=0;
            for(j=0; j<n; j++)
            {
                if(j == count) continue;
                array[i_count][j_count] = mat[i][j];
                j_count++;
            }
            i_count++;
        }
        det += (pow(-1, count) * mat[0][count] * determinant(n-1,array)); 
    }
    return det;
}

void server(){
     	int server_socket;
        char buf[1024];
        int bytes_read;
        int sock;

        server_socket = socket(AF_UNIX, SOCK_DGRAM, 0);

        struct sockaddr srvr_name;

        srvr_name.sa_family = AF_UNIX;
        strcpy(srvr_name.sa_data, SOCKET_NAME);

        bind(server_socket, &srvr_name, strlen(srvr_name.sa_data) + sizeof(srvr_name.sa_family));

        struct sockaddr rcvr_name;
        rcvr_name.sa_family = AF_UNIX;
        strcpy(rcvr_name.sa_data, SOCKET_NAME);

        

        printf("Determinant is ");
        recvfrom(server_socket, buf, sizeof(buf), 0, &rcvr_name, NULL);
        int i =0;
        while (buf[i])
        {
            printf("%c", buf[i]);
            i++;
        }
   printf("\n");
        close(server_socket);
}

void sendSocket(char *message){
   

        int sender_socket;

        sender_socket = socket(AF_UNIX, SOCK_DGRAM, 0);

      
        struct sockaddr srvr_name;
        srvr_name.sa_family = AF_UNIX;
        strcpy(srvr_name.sa_data, SOCKET_NAME);
    
     


        sendto( sender_socket, message, strlen(message), 0, &srvr_name, strlen(srvr_name.sa_data) + sizeof(srvr_name.sa_family));

        close(sender_socket);
}

int main()
{

    int i, j, dim;
    int fd[2];
    pipe(fd);
    int fd_shm;
    if((fd_shm = shm_open("myshered.shm", O_RDWR|O_CREAT|O_TRUNC, 0777))<0){
        perror("Error");
        return(1);
    }

    SOCKET_NAME = (char*)mmap(0, 505, PROT_READ |PROT_WRITE, MAP_SHARED, fd_shm, 0);
    ftruncate(fd_shm,505);
   
     memcpy(SOCKET_NAME, ch, strlen(ch));
     
    pid_t pid=fork();
    if(pid)
    {
       
        close(fd[0]); 
        char buffer[100];
        printf("Enter n\n");
        scanf("%d",&dim);
     
        int matrix[dim][dim];
        printf("Enter matrix:\n");
        for(i = 0; i < dim; i++)
        {
            for(j = 0; j < dim; j++)
            {
        

                scanf("%d",&matrix[i][j]);
             
            }
        }
        
       
      
        write(fd[1],&dim,sizeof(double));  
        write(fd[1], matrix, dim*dim*sizeof(double));  
        close(fd[1]);
        server();
        shm_unlink(SOCKET_NAME);
    }
    else
    {
     
        close(fd[1]);  
        int dim;
        read(fd[0], &dim, sizeof(double)); 
        int matrix[dim][dim];  
        read(fd[0], matrix, dim*dim*sizeof(double));
        char ch[500];
        sprintf(ch,"%d", determinant(dim, matrix) );

        sendSocket(ch);
          
        close(fd[0]);
    }
    return 0;
}


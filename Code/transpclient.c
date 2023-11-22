#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 1000
#define PORT 8080
#define SA struct sockaddr

int findMin(char temp[MAX]) {
	int i,j,min,index;
	min=temp[0];
	index=0;
	for (j=0;j<strlen(temp);j++) {
		if(temp[j]<min) {
			min=temp[j];
			index=j;
		}
	}
	temp[index]=123;
	return(index);
}

void decrypt(char message[],char key[]){
	printf("Encrypted string: %s",message);
	int emlen=strlen(message);
	char temp[MAX];
	char arr[100][100];
	strcpy(temp,key);
	int klen=strlen(key);
	int rows=emlen/klen;
	int i,j,k;
	k=0;
	for (i=0;i<klen;i++) {
		int index=findMin(temp);
		int j;
		for (j=0;j<rows;j++) { {
				arr[j][index]=message[k++];
			}
		}
	}
	message[k]='\0';
	printf("\nArray Retrieved is\n");
	k=0;
	for (i=0;i<rows;i++) {
		for (j=0;j<klen;j++) {
			printf("%c ",arr[i][j]);
			//retrieving message 
			if(arr[i][j]!='-')
			message[k++]=arr[i][j];
		}
		printf("\n");
	}
	message[k]='\0';
}
   
int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    char buff[MAX];
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) 
        exit(0);
    printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
   
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0)
        exit(0);
    printf("Connected to the server..\n");
   
    bzero(buff, sizeof(buff));
    read(sockfd, buff, sizeof(buff));
    decrypt(buff,"hell");
    printf("From Server : %s\n", buff);
   
    close(sockfd);
}

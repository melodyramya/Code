#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 1000
#define PORT 8080
#define SA struct sockaddr

int findMin(char temp[MAX]) {
	int i,j,min,index;
	min=temp[0];
	index=0;
	for (j=0;j<strlen(temp)-1;j++) {
		if(temp[j]<min) {
			min=temp[j];
			index=j;
		}
	}
	temp[index]=123;
	return(index);
}

void encrypt(char message[MAX], char key[MAX]){
	int i,j,klen,flag=0,r,c,k=0;
	int mlen=strlen(message)-1;
	klen=strlen(key)-1;
	char arr[100][100];
	char temp[MAX];
	strcpy(temp,key);
	for(i=0; ;i++) {
		if(flag==1) 
			break;
		for (j=0;j<klen;j++) {
			if(k>=mlen) {
				flag=1;
				arr[i][j]='-';
				//printf("%d %d -",i,j);
			} else {
				arr[i][j]=message[k++];
			}
		}
	}
	r=i;
	c=j;
	//printf("%d %d",i,j);
	for (i=0;i<r;i++) {
		for (j=0;j<c;j++) {
			printf("%c ",arr[i][j]);
		}
		printf("\n");
	}
	k=0;
	for (i=0;i<klen;i++) {
		int index=findMin(temp);
		int j;
		for (j=0;j<r;j++) { {
				message[k++]=arr[j][index];
			}
		}
	}
	message[k]='\0';
	//printf("%s",message);
}

int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
    char buff[MAX];
    char key[MAX];
   
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
        exit(0);
    printf("Socket successfully created..\n");
    
    bzero(&servaddr, sizeof(servaddr));   
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
   
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0)
        exit(0);
    printf("Socket successfully binded..\n");
   
    if ((listen(sockfd, 5)) != 0)
        exit(0);
    printf("Server listening..\n");
    len = sizeof(cli);

    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0)
        exit(0);

    printf("Server has accepted the client...\n");
   
    bzero(buff, MAX);
    bzero(key,MAX);
    printf("Enter the string : ");
    int n = 0;
    while ((buff[n++] = getchar()) != '\n');
 	n=0;
 	printf("Enter the key : ");
    while ((key[n++] = getchar()) != '\n');
    encrypt(buff,key);
    write(connfd, buff, sizeof(buff));
   
    close(sockfd);
}



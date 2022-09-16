// server program for udp connection
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 5000
#define MAXLINE 1000

int main()
{
	char *IP;
	int buffer;
	int listenfd, len;
	struct sockaddr_in servaddr, cliaddr;
	bzero(&servaddr, sizeof(servaddr));

	// Create a UDP Socket
	listenfd = socket(AF_INET, SOCK_DGRAM, 0);		
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;

	// bind server address to socket descriptor
	bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	
	while(1){
		bzero(&buffer, sizeof(buffer));
		len = sizeof(cliaddr);
		recvfrom(listenfd, &buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr,&len);
		
		if(buffer == -1) break;
		
		printf("Client : %d\n", buffer);
		// Do some computation with buffer
		if(buffer%2 == 0) buffer = 0;
		else buffer = 1;
		printf("Server : %d\n", buffer);
		sendto(listenfd, &buffer, sizeof(buffer), 0,(struct sockaddr*)&cliaddr, sizeof(cliaddr)); 
	}
	
	close(listenfd);
	return 0;
}

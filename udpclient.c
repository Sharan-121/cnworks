// udp client driver program
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>

#define PORT 5000

// Driver code
int main()
{
	int buffer;
	int sockfd, n;
	struct sockaddr_in servaddr;
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;
	
	// create datagram socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	// connect to server
	if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		printf("\n Error : Connect Failed \n");
		exit(0);
	}

	while(1){
		bzero(&buffer, sizeof(buffer));
		scanf("%d", &buffer);
		sendto(sockfd, &buffer, sizeof(buffer), 0, (struct sockaddr*)NULL, sizeof(servaddr));
		
		if(buffer == -1) break;
		
		printf("Client : %d\n", buffer);
		bzero(&buffer, sizeof(buffer));
		recvfrom(sockfd, &buffer, sizeof(buffer), 0, (struct sockaddr*)NULL, NULL);
		
		printf("Server : ");
		if (buffer == 0) printf("Even\n");
		else printf("Odd\n");
	}
	
	close(sockfd);
	return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){

	char *ip = "127.0.0.1";
	int port = 10000;

	int sock;
	struct sockaddr_in addr;
	socklen_t addr_size;
	int buffer;
	int n;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0){
		perror("[-]Socket error");
		exit(1);
	}
	printf("[+]TCP server socket created.\n");

	memset(&addr, '\0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr.s_addr = inet_addr(ip);

	connect(sock, (struct sockaddr*)&addr, sizeof(addr));
	printf("Connected to the server.\n");

	while(1) {
		bzero(&buffer, sizeof(buffer));
		scanf("%d", &buffer);
		printf("Client: %d\n", buffer);
		send(sock, &buffer, sizeof(buffer), 0);

		if (buffer == -1) break;

		bzero(&buffer, sizeof(buffer));
		recv(sock, &buffer, sizeof(buffer), 0);
		
		printf("Server: ");
		if (buffer == 0) printf("Even\n");
		else printf("Odd\n");
	}

	close(sock);
	printf("Disconnected from the server.\n");

	return 0;

}

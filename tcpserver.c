#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


int main(){

	char *ip = "127.0.0.1";
	int port = 10000;

	int server_sock, client_sock;
	struct sockaddr_in server_addr, client_addr;
	socklen_t addr_size;
	int buffer;
	int n;

	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	while (server_sock < 0){
		server_sock = socket(AF_INET, SOCK_STREAM, 0);
	} 
	printf("[+]TCP server socket created.\n");

	memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = port;
	server_addr.sin_addr.s_addr = inet_addr(ip);

	n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
	while (n < 0){
		n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
	}
	printf("[+]Bind to the port number: %d\n", port);

	listen(server_sock, 5);
	printf("Listening...\n");
	addr_size = sizeof(client_addr);
	client_sock = accept(server_sock, (struct   sockaddr*)&client_addr, &addr_size);
	printf("[+]Client connected.\n");

	while(1) {
		bzero(&buffer, sizeof(buffer));
		recv(client_sock, &buffer, sizeof(buffer), 0);
		printf("Client: %d\n", buffer);
		
		if (buffer == -1) break;

		// Do some computation with buffer
		if (buffer%2 == 0) buffer = 0;
		else buffer = 1;

		printf("Server: %d\n", buffer);
		send(client_sock, &buffer, sizeof(buffer), 0);
	}

	close(client_sock);
	printf("[+]Client disconnected.\n\n");

	return 0;
}

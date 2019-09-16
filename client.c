#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 5984
#define BUFF_SIZE 4096

int main(int argc, const char *argv[])
{
	int sock = 0;
	struct sockaddr_in serv_addr;
	char *hello = "Hello from client";
	char buffer[BUFF_SIZE] = {0};

	/* [C1: point 1]
	 * Explain following in here.
	 * Attepmts to create an endpoint connection. Returns a negative if fails.
	 * If it does fail, program prints an error message and exits.
	 */
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	/* [C2: point 1]
	 * Explain following in here.
	 * sets ser_addr memory address to the value '0'
	 * sets the in address family, this case Ipv4
	 * sets the in port number
	 */ 
	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	/* [C3: point 1]
	 * Explain following in here.
	 * Converts the address 127.0.0.1 into a usable one and stores in into
	 * the serv_addr struct
	 */
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	/* [C4: point 1]
	 * Explain following in here.
	 * Attempts to make a connection to the server on the socket "sock"
	 */
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		printf("\nConnection Failed \n");
		return -1;
	}


	/* [C5: point 1]
	 * Explain following in here.
	 * Waits for the user to press a key to continue execution
	 */
	printf("Press any key to continue...\n");
	getchar();

	/* [C6: point 1]
	 * Explain following in here.
	 * Sends a hello message to the server
	 */
	send(sock , hello , strlen(hello) , 0 );
	printf("Hello message sent\n");

	/* [C7: point 1]
	 * Explain following in here.
	 * recieves and displays the message sent from the server
	 */
	read( sock , buffer, 1024);
	printf("Message from a server: %s\n",buffer );
	return 0;
}

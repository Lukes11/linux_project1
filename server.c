#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 5984
#define BUFF_SIZE 4096

int main(int argc, const char *argv[])
{
	int server_fd, new_socket;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[BUFF_SIZE] = {0};
	char *hello = "Hello from server";

	/* [S1: point 1]
	 * Explain following in here.
	 * When successful, socket returns a non-negative integer. If an endpoint can't be established, 
	 * then the socket fails, program exits.
	 * Created endpoint for communication
	 */
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	/* [S2: point 1]
	 * Explain following in here.
	 * Sets socket options with the socket server_fd. This returns 0 when successful, 
	 * so if it returns a non-zero, the program exits.  
	 */
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
		       &opt, sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	/* [S3: point 1]
	 * Explain following in here.
	 * sets the in address family, in this case Ipv4
	 * sets the in address
	 * sets the in port number
	 */
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );

	/* [S4: point 1]
	 * Explain following in here.
	 * Attempts to assign an address to the server_fd socket. If successfull, returns 0
	 * if successful and -1 if unsucssful. If it returns -1, program exits. 
	 */
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	/* [S5: point 1]
	 * Explain following in here.
	 * Marks the server_fd socket as accepting connections, and sets the maximum waiting que to be 3.
	 * Returns 0 if successful, -1 otherwise. If this returns -1, program exits. 
	 */
	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	/* [S6: point 1]
	 * Explain following in here.
	 * Extracts the first connection on the queue of waiting connections, and creates a new socket with the same properties, allocates a file descriptor.
	 */
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
				 (socklen_t*)&addrlen)) < 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}

	/* [S7: point 1]
	 * Explain following in here.
	 * Waits for the user to press a ket to continue the program
	 */
	printf("Press any key to continue...\n");
	getchar();

	/* [S8: point 1]
	 * Explain following in here.
	 * Uses the read system call the data from the file descriptor in new_socket that was 
	 * previously allocated into a buffer, up to 1024 bytes. 
	 * Then display this message. 
	 */
	read( new_socket , buffer, 1024);
	printf("Message from a client: %s\n",buffer );

	/* [S9: point 1]
	 * Explain following in here.
	 * Sends a message on the socket specified by the socket file deseriptor new_socket
	 */
	send(new_socket , hello , strlen(hello) , 0 );
	printf("Hello message sent\n");
	return 0;
}

#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	getopt(argc, argv, "s:");
	char* stringToEncrypt = optarg;
	printf("%s\n", stringToEncrypt);
	getopt(argc, argv, "k:");
	int key = atoi(optarg);
	printf("%d\n", key);
	long encryptResult = syscall(335, stringToEncrypt, key);
	printf("Result: %ld\n", encryptResult);
	return 0;
}

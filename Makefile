CC = gcc
CFLAGS += -g

syscall_test: syscall_test.c
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm -rf syscall_test

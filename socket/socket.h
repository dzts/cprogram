#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>

struct sockaddr_in s_socket_init(int port);

int s_socket();

int s_bind(int listen_fd,struct sockaddr_in addr);

int s_listen(int listen_fd,int backlog);

int s_accept(int listen_fd);

char* s_read(int fd,int read_size);

void s_connect(int server_fd,struct sockaddr_in server_addr);

void s_send(int fd,char * data);

void s_close(int fd);


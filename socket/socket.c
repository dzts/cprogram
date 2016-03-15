#include "socket.h"

struct sockaddr_in s_socket_init(int port){
	struct sockaddr_in addr;
	bzero(&addr,sizeof(addr));
    addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=INADDR_ANY;
	addr.sin_port=htons(port);
	return addr;
}

int s_socket(){
	int listen_fd=socket(AF_INET,SOCK_STREAM,0);
	if( -1 == listen_fd ){
		perror("fail to create socket!");
		exit(1);
	}
	return listen_fd;
}

int s_bind(int listen_fd,struct sockaddr_in addr){
	if( bind(listen_fd,(struct sockaddr*)&addr,sizeof(addr))== -1 ){
		perror("can't to bind");
		exit(1);
	}
}

int s_listen(int listen_fd,int backlog){
	if( listen(listen_fd,backlog)==-1 ){
		perror("can't to listen");
		exit(1);
	}
}

int s_accept(int listen_fd){
	struct sockaddr_in accept_addr;
	int size = sizeof(accept_addr);
	printf("server socket begin accept:\n");
	int accept_fd = accept(listen_fd,(struct sockaddr*)&accept_addr,&size);
	if( accept_fd < 0 ){
		perror("error:socket accept!exited!\n");
		exit(-1);
	}
	return accept_fd;
}

char* s_read(int accept_fd,int read_size){
    char *data = (char *)malloc(4096);
	int ret = read(accept_fd,data,read_size);
	return data;
}

void s_connect(int server_fd,struct sockaddr_in server_addr){
	int ret=connect(server_fd,(const struct sockaddr *)&server_addr,sizeof(struct sockaddr_in));
	if( ret<0 ){
		perror("error:socket connect!");
		exit(1);
	}
}

void s_send(int fd,char * data){
	send(fd,data,strlen(data),0);
}

void s_close(int fd){
	close(fd);
}

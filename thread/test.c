#include "../socket/socket.h"
#include <pthread.h>

struct ptr{
	pthread_t a;
	int fd;
}_ptr;

void send_msg(int fd){
	char* data;
	
    data = s_read(fd,10000);
    char* http_head = "HTTP/1.1 200\r\n";
    s_send(fd,http_head);
    char* s = "\r\nsdfasdfasdfasdfasdfasdf";
    s_send(fd,s);
    s_close(fd);
    free(data);
	pthread_t ptr=pthread_self();
	
	s_close(fd);
	pthread_detach(pthread_self());
	pthread_exit(&ptr);
}

int main(){
	struct sockaddr_in addr = s_socket_init(10000);
	int listen_fd = s_socket();
	s_bind(listen_fd,addr);
	s_listen(listen_fd,100);
	pthread_t parr[10];
	int b=0;
	for(b=0;b<10;b++){
		parr[b]=0;
	}
	while(1){
		int fd = s_accept(listen_fd);
		int i=0;
		
		while( 0 !=  pthread_create(&parr[i],NULL,(void *)&send_msg,(void *)fd) ){
			sleep(0.1);
		}
		
	}
}

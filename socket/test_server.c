#include "socket.h"
int main(){
	struct sockaddr_in addr = s_socket_init(10000);
	int listen_fd = s_socket();
	s_bind(listen_fd,addr);
	s_listen(listen_fd,100);
	while(1){
		int fd = s_accept(listen_fd);
		char* data;
		data = s_read(fd,10000);
		char* http_head = "HTTP/1.1 200\r\n";
		s_send(fd,http_head);
		char* s = "\r\nsdfasdfasdfasdfasdfasdf";
		s_send(fd,s);
		s_close(fd);
		free(data);
	}
}

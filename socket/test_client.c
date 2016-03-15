#include "socket.h"
int main(){
	struct sockaddr_in addr = s_socket_init(10000);
	int fd = s_socket();
	s_connect(fd,addr);
	char * data="adasdfasdf";
	s_send(fd,data);
}

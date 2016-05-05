#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <event2/event.h>
#include <string.h>

#define PORT        9500
#define BACKLOG     5
#define MEM_SIZE    1024

struct event_base* base;
struct sock_ev {
    struct event* read_ev;
    struct event* write_ev;
    char* buffer;
};

void release_sock_event(struct sock_ev* ev)
{
    event_del(ev->read_ev);
    free(ev->read_ev);
    free(ev->write_ev);
    free(ev->buffer);
    free(ev);
}

void on_write(int sock, short event, void* arg)
{
    char* buffer = (char*)arg;
    send(sock, buffer, strlen(buffer), 0);

    free(buffer);
}

void on_read(int sock, short event, void* arg)
{
    struct event* write_ev;
    int size;
    struct sock_ev* ev = (struct sock_ev*)arg;
    ev->buffer = (char*)malloc(MEM_SIZE);
    bzero(ev->buffer, MEM_SIZE);
    size = recv(sock, ev->buffer, MEM_SIZE, 0);
    printf("receive data:%s, size:%d\n", ev->buffer, size);
    if (size == 0) {
        release_sock_event(ev);
        close(sock);
        return;
    }
    event_set(ev->write_ev, sock, EV_WRITE, on_write, ev->buffer);
    event_base_set(base, ev->write_ev);
    event_add(ev->write_ev, NULL);
}

void on_accept(int sock,short event,void* arg)
{
	struct sockaddr_in cli_addr;
	int sin_size = sizeof(struct sockaddr_in);
    int newfd = accept(sock, (struct sockaddr*)&cli_addr, &sin_size);
	char *buffer = (char *)malloc(4080);
	read(newfd,buffer,4080);
	printf("%s\n",buffer);
	send(newfd,buffer,strlen(buffer),0);
	close(newfd);
}

int main(int argc, char* argv[])
{
    struct sockaddr_in my_addr;
    int sock;

    sock = socket(AF_INET, SOCK_STREAM, 0);
	if( sock == -1 ){
		printf("fail create socket!\n");
		exit;
	}
    int yes = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    if( -1 == bind(sock, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) ){
		printf("bind failed\n");
		exit;
	}
    if( -1 == listen(sock, BACKLOG) ){
		printf("listen failed\n");
		exit;
	}

    struct event_base* base = event_base_new();
    struct event *listen_ev = event_new(base, sock, EV_READ|EV_PERSIST, on_accept, NULL);
   	
    if( -1 == event_add(listen_ev, NULL) ){
		printf("failed\n");
	}
	printf("start\n");
	int e = event_base_dispatch(base);
	printf("%d\n",e);
    if( 1 ){
		printf("event_base_dispatch exec failed!\n");
		exit;
	}
	printf("end\n");
    return 0;
}

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <evutil.h>
#include <event.h>
#include <evhttp.h>

void http_request_handler(struct evhttp_request *req, void *arg) { 
    struct evbuffer * databuf = evbuffer_new(); 
    evbuffer_add_printf(databuf, "hello world");

    evhttp_send_reply_start(req,200,"OK");
    evhttp_send_reply_chunk(req,databuf);
    evhttp_send_reply_end(req);

　  evbuffer_free(databuf); 
}
 
int main() { 
    struct event_base *base = event_base_new(); 
    struct evhttp *httpd = evhttp_new(base); 
    evhttp_bind_socket(httpd,"0.0.0.0",19800); 
    evhttp_set_gencb(httpd, http_request_handler, NULL); 
    event_base_dispatch(base); 
}

#include <ev.h>
#include <errno.h>
#include "netutils.h"

static void on_accept(struct ev_loop *loop, ev_io *w, int revents);
static void on_read(struct ev_loop *loop, ev_io *w, int revents);

int
main(int arc, char **argv) {
    struct ev_loop *loop = ev_loop_new(0);
    int sock = new_tcp_server("0.0.0.0", 8080);
    ev_io listen;
    ev_io_init(&listen, on_accept, sock, EV_READ);
    ev_io_start(loop, &listen);
    ev_run(loop, 0);

    ev_loop_destroy(loop);
    return 0;
}

void on_accept(struct ev_loop *loop, ev_io *w, int revents) {
    if ((revents | EV_READ) == 0) {
        return ;
    }
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    int sock = accept(w->fd, (struct sockaddr*)&addr, &len);
    if (sock < 0) {
        perror("accept");
        return ;
    }
    set_nonblock(sock);
    char p[128];
    get_address(&addr, p, sizeof(p));
    fprintf(stderr, "accept connection from %s\n", p);
    ev_io *watcher = (ev_io*) malloc(sizeof(ev_io));
    ev_io_init(watcher, on_read, sock, EV_READ);
    ev_io_start(loop, watcher);
}

void on_read(struct ev_loop *loop, ev_io *w, int revents) {
    char buffer[4096];
    int n;
    while ((n = read(w->fd, buffer, sizeof(buffer))) > 0) {
        /*fprintf(stderr, "receive %d bytes\n", n);*/
        writen(w->fd, buffer, n);
    }
    if (n == 0) {
        fprintf(stderr, "connection is closed\n");
        ev_io_stop(loop, w);
        close(w->fd);
        free(w);
    } else if (n < 0 && errno != EWOULDBLOCK && errno != EAGAIN) {
        fprintf(stderr, "error on connection, close it\n");
        ev_io_stop(loop, w);
        close(w->fd);
        free(w);
    }
}

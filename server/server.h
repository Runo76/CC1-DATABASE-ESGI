#ifndef SERVER_H
#define SERVER_H

#define MAX_CLIENTS 100

typedef struct {
    char hostname[128];
    char sshkey[256];
} Client;

extern Client clients[MAX_CLIENTS];
extern int client_count;

#endif

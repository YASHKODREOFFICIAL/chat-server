#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <netinet/in.h>
#endif

#include <pthread.h>

// Client structure
typedef struct {
    int sockfd;
    char username[32];

#ifdef _WIN32
    struct sockaddr_in addr;
#else
    struct sockaddr_in addr;
#endif

} client_t;

// Shared mutex (extern declaration)
extern pthread_mutex_t clients_mutex;

// Function declarations
void *handle_client(void *arg);
void broadcast_message(char *msg, int sender_fd);
void add_client(client_t *client);
void remove_client(int sockfd);

#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#ifdef _WIN32
#include <winsock2.h>
#define close closesocket
#else
#include <unistd.h>
#endif

#include "client_handler.h"
#include "../common/constants.h"

// 🔥 DEFINE ONLY HERE (IMPORTANT)
client_t *clients[MAX_CLIENTS];
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

// Add client
void add_client(client_t *client) {
    pthread_mutex_lock(&clients_mutex);

    int added = 0;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (!clients[i]) {
            clients[i] = client;
            added = 1;
            break;
        }
    }

    pthread_mutex_unlock(&clients_mutex);

    if (!added) {
        printf("⚠️ Max clients reached\n");
        close(client->sockfd);
        free(client);
    }
}

// Remove client
void remove_client(int sockfd) {
    pthread_mutex_lock(&clients_mutex);

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i] && clients[i]->sockfd == sockfd) {
            clients[i] = NULL;
            break;
        }
    }

    pthread_mutex_unlock(&clients_mutex);
}

// Broadcast message
void broadcast_message(char *msg, int sender_fd) {
    pthread_mutex_lock(&clients_mutex);

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i] && clients[i]->sockfd != sender_fd) {
            send(clients[i]->sockfd, msg, strlen(msg), 0);
        }
    }

    pthread_mutex_unlock(&clients_mutex);
}

// Thread handler
void *handle_client(void *arg) {
    client_t *cli = (client_t *)arg;
    char buffer[BUFFER_SIZE];

    int name_len = recv(cli->sockfd, cli->username, USERNAME_LEN - 1, 0);

    if (name_len <= 0) {
        close(cli->sockfd);
        free(cli);
        return NULL;
    }

    cli->username[name_len] = '\0';

    printf("✅ %s joined\n", cli->username);

    while (1) {
        int len = recv(cli->sockfd, buffer, BUFFER_SIZE - 1, 0);

        if (len <= 0) {
            printf("❌ %s disconnected\n", cli->username);
            close(cli->sockfd);
            remove_client(cli->sockfd);
            free(cli);
            break;
        }

        buffer[len] = '\0';

        char msg[MAX_MESSAGE_LEN];
        snprintf(msg, sizeof(msg), "[%s]: %s", cli->username, buffer);

        printf("%s", msg);

        broadcast_message(msg, cli->sockfd);
    }

    return NULL;
}
#include <winsock2.h>
#include "../common/constants.h"

#include <stdio.h>

void *receive_messages(void *sockfd_ptr) {
    int sockfd = *(int *)sockfd_ptr;
    char buffer[BUFFER_SIZE];
    int len;

    while ((len = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[len] = '\0';
        printf("%s\n", buffer);
    }

    printf("Disconnected from server.\n");
    closesocket(sockfd);
    return NULL;
}
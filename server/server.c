#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#define close closesocket
#else
#include <arpa/inet.h>
#include <unistd.h>
#endif

#define PORT 9090

int main() {

#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }
#endif

    int server_fd, client_fd;
    struct sockaddr_in server, client;
    int c = sizeof(client);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        printf("Socket creation failed\n");
        return 1;
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Bind failed\n");
        return 1;
    }

    if (listen(server_fd, 5) < 0) {
        printf("Listen failed\n");
        return 1;
    }

    printf("🚀 Server running on port %d...\n", PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr*)&client, &c);

        if (client_fd < 0) {
            printf("Accept failed\n");
            continue;
        }

        char buffer[1024] = {0};
        int len = recv(client_fd, buffer, sizeof(buffer), 0);

        if (len > 0) {
            buffer[len] = '\0';
            printf("📩 Message: %s\n", buffer);
        }

        close(client_fd);
    }

#ifdef _WIN32
    WSACleanup();
#endif

    return 0;
}
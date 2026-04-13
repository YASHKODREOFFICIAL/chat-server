#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 3000
#define SERVER_PORT 9090

char messages[100][1024];
int msg_count = 0;

void send_to_c_server(char *msg) {
    SOCKET sock;
    struct sockaddr_in serv;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv.sin_family = AF_INET;
    serv.sin_port = htons(SERVER_PORT);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr*)&serv, sizeof(serv));

    char formatted[1024];
    sprintf(formatted, "%s\n", msg);

    send(sock, formatted, strlen(formatted), 0);
    closesocket(sock);
}

// Serve files
void serve_file(SOCKET client_fd, const char *filename, const char *type) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return;

    char content[5000];
    int size = fread(content, 1, sizeof(content), fp);

    char header[512];
    sprintf(header,
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: %s\r\n"
        "Access-Control-Allow-Origin: *\r\n\r\n",
        type);

    send(client_fd, header, strlen(header), 0);
    send(client_fd, content, size, 0);

    fclose(fp);
}

int main() {
    WSADATA wsa;
    SOCKET server_fd, client_fd;
    struct sockaddr_in server, client;
    int c;

    WSAStartup(MAKEWORD(2,2), &wsa);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&server, sizeof(server));
    listen(server_fd, 5);

    printf("🌐 Open http://192.168.0.103:%d\n", PORT);

    c = sizeof(struct sockaddr_in);

    while ((client_fd = accept(server_fd, (struct sockaddr*)&client, &c))) {

        char buffer[4096] = {0};
        recv(client_fd, buffer, sizeof(buffer), 0);

        printf("Request:\n%s\n", buffer);

        // -------- HTML --------
        if (strstr(buffer, "GET / ")) {
            serve_file(client_fd, "web/index.html", "text/html");
        }

        // -------- CSS --------
        else if (strstr(buffer, "GET /style.css")) {
            serve_file(client_fd, "web/style.css", "text/css");
        }

        // -------- JS --------
        else if (strstr(buffer, "GET /script.js")) {
            serve_file(client_fd, "web/script.js", "application/javascript");
        }

        // -------- OPTIONS --------
        else if (strstr(buffer, "OPTIONS")) {
            char res[] =
                "HTTP/1.1 200 OK\r\n"
                "Access-Control-Allow-Origin: *\r\n"
                "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n"
                "Access-Control-Allow-Headers: Content-Type\r\n\r\n";

            send(client_fd, res, strlen(res), 0);
        }

        // -------- POST /send --------
        else if (strstr(buffer, "POST /send")) {

            char *body = strstr(buffer, "\r\n\r\n");
            if (body) {
                body += 4;

                printf("Raw Body: %s\n", body);

                char msg[1024] = {0};
                sscanf(body, "{\"message\":\"%[^\"]\"}", msg);

                if (strlen(msg) > 0) {
                    printf("💬 Message: %s\n", msg);

                    strcpy(messages[msg_count++], msg);

                    send_to_c_server(msg);
                }
            }

            char res[] =
                "HTTP/1.1 200 OK\r\n"
                "Access-Control-Allow-Origin: *\r\n\r\nOK";

            send(client_fd, res, strlen(res), 0);
        }

        // -------- GET /messages --------
        else if (strstr(buffer, "GET /messages")) {
            char json[5000] = "[";
            for (int i = 0; i < msg_count; i++) {
                strcat(json, "\"");
                strcat(json, messages[i]);
                strcat(json, "\"");
                if (i < msg_count - 1) strcat(json, ",");
            }
            strcat(json, "]");

            char res[6000];
            sprintf(res,
                "HTTP/1.1 200 OK\r\n"
                "Access-Control-Allow-Origin: *\r\n"
                "Content-Type: application/json\r\n\r\n%s",
                json);

            send(client_fd, res, strlen(res), 0);
        }

        closesocket(client_fd);
    }
}
CC=gcc
CFLAGS=-Wall -Wextra -pthread

SERVER_SRC=server/server.c server/client_handler.c server/server_utils.c
CLIENT_SRC=client/client.c client/client_utils.c

all:
	gcc server/server.c server/server_utils.c server/client_handler.c -o build/server_app.exe -lws2_32
	gcc client/client.c client/client_utils.c -o build/client_app.exe -lws2_32
	gcc bridge/web_bridge.c -o build/web_bridge.exe -lws2_32

server:
	$(CC) $(CFLAGS) $(SERVER_SRC) -o server_app

client:
	$(CC) $(CFLAGS) $(CLIENT_SRC) -o client_app

clean:
	rm -f server_app client_app
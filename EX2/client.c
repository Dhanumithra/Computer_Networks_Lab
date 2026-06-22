#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>
int main()
{
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    char message[1024];
    char reply[1024];
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("WSAStartup failed\n");
        return 1;
    }
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
    {
        printf("Socket creation failed\n");
        return 1;
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    if(connect(sock,(struct sockaddr*) &server,sizeof(server)) <0) {
        printf("Error in connection\n");
    }
    printf("Connected to server\n");
    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    send(sock, message, strlen(message) + 1, 0);
    recv(sock, reply, sizeof(reply), 0);
    printf("Server replied: %s\n", reply);
    closesocket(sock);
    WSACleanup();
    return 0;
}
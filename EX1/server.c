#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
int main()
{
    WSADATA wsa;
    SOCKET serverfd, clientfd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buf[1024] = {0};
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("WSAStartup failed\n");
        return 1;
    }
    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd == INVALID_SOCKET)
    {
        printf("Error in socket creation\n");
        return 1;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    if (bind(serverfd, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR)
    {
        printf("Error in binding\n");
        return 1;
    }
    if (listen(serverfd, 3) == SOCKET_ERROR)
    {
        printf("Error in listening\n");
        return 1;
    }
    printf("Listening\n");
    clientfd = accept(serverfd, (struct sockaddr *)&address, &addrlen);
    if (clientfd == INVALID_SOCKET)
    {
        printf("Error in accepting\n");
        return 1;
    }
    printf("Client connected\n");
    recv(clientfd, buf, sizeof(buf) + 1, 0);
    printf("Received message : %s\n", buf);
    send(clientfd, "Hello from Server", 24, 0);
    closesocket(clientfd);
    closesocket(serverfd);
    WSACleanup();
    return 0;
}
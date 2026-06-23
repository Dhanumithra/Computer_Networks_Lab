#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <string.h>

int main()
{
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;

    char buffer[1024];
    char guess;

    WSAStartup(MAKEWORD(2,2), &wsa);

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    connect(sock,
            (struct sockaddr*)&server,
            sizeof(server));

    printf("Connected to Hangman Server\n");

    while(1)
    {
        memset(buffer, 0, sizeof(buffer));

        recv(sock,
             buffer,
             sizeof(buffer)-1,
             0);

        if(strcmp(buffer,"YOU_WIN")==0)
        {
            printf("\nYou Won!\n");
            break;
        }

        if(strcmp(buffer,"YOU_LOSE")==0)
        {
            printf("\nYou Lost!\n");
            break;
        }

        if(strcmp(buffer,"TIME_OVER")==0)
        {
            printf("\nTime Over!\n");
            break;
        }

        printf("\nWord : %s\n", buffer);

        printf("Enter Guess : ");
        scanf(" %c", &guess);

        send(sock,
             &guess,
             sizeof(guess),
             0);
    }

    closesocket(sock);
    WSACleanup();

    return 0;
}
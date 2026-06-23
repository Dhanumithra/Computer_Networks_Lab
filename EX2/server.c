#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <time.h>

int main()
{
    WSADATA wsa;
    SOCKET serverfd, clientfd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    char word[] = "NETWORK";
    char display[] = "_______";

    int chances = 6;
    time_t start, now;

    WSAStartup(MAKEWORD(2,2), &wsa);

    serverfd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(serverfd, (struct sockaddr*)&address, sizeof(address));

    listen(serverfd, 3);

    printf("Waiting for client...\n");

    clientfd = accept(serverfd,
                      (struct sockaddr*)&address,
                      &addrlen);

    printf("Client connected\n");

    start = time(NULL);

    while(chances > 0)
    {
        char guess;
        int found = 0;

        now = time(NULL);

        if(difftime(now, start) >= 60)
        {
            send(clientfd,
                 "TIME_OVER",
                 strlen("TIME_OVER"),
                 0);

            printf("Time Over\n");
            break;
        }

        send(clientfd, display, strlen(display), 0);

        recv(clientfd, &guess, sizeof(guess), 0);

        for(int i=0; i<strlen(word); i++)
        {
            if(word[i] == guess)
            {
                display[i] = guess;
                found = 1;
            }
        }

        if(!found)
            chances--;

        if(strcmp(word, display) == 0)
        {
            
            send(clientfd,
                 "YOU_WIN",
                 strlen("YOU_WIN"),
                 0);

            printf("Player Won\n");
            break;
        }

        if(chances == 0)
        {
            send(clientfd,
                 "YOU_LOSE",
                 strlen("YOU_LOSE"),
                 0);

            printf("Player Lost\n");
        }
    }

    closesocket(clientfd);
    closesocket(serverfd);
    WSACleanup();

    return 0;
}
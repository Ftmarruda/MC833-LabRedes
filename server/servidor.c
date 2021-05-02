#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <sqlite3.h>

#include "jsonParser.h"

#define MAX_SIZE 256

void emergencyExit();

int main(){

    typedef struct sockaddr_in sockaddr_in;
    typedef struct sockaddr sockaddr;
    ssize_t n;

    int serverSocket = 0, clientSocket = 0;
    char serverMessage[MAX_SIZE], request[MAX_SIZE];

    strcpy(serverMessage, "BEM-VINDO AO SUPERPAPO");
    //create the server socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    //define server address
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(50000);
    server_address.sin_addr.s_addr = INADDR_ANY;
    unsigned int len;
    len = sizeof(server_address);

    //define client adrr
    sockaddr client_address;


    //bind the socket to IP and port
    bind(serverSocket, (sockaddr *) &server_address, len);

    listen(serverSocket, 5); //can have 1 connection waiting at max

    //accept client connection
    
    while(clientSocket != -1){

        clientSocket = accept(serverSocket, (sockaddr *) &client_address, &len); //-> substituir valores de null por outras estruturas se quiser pegar o endereço do cliente
        printf("client socket: %d\n", clientSocket);
        close(serverSocket);

        again:
            while ( (n = recv(clientSocket, request, 600, 0)) > 0){
                printf("The client has requested: %s", request);
                printf("buffer size: %ld\n", n);

                if(!parse(request)){
                    strcpy(serverMessage, "The request failed!\n");
                }else{
                    strcpy(serverMessage, "Request processed succesfully!\n");
                }
                
                send(clientSocket, serverMessage, sizeof(serverMessage), 0);

                if (n < 0 && errno == 4)
                    goto again;
                else if (n < 0)
                    printf("str_echo: recv error");
            }
        //receive message from client
        close(clientSocket);	
    }
    
    return 0;
}

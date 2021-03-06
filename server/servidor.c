/*
    Este arquivo "liga" o servidor, setando a porta e o endereço ip. Após isso, conecta à um cliente e, à medida que mensagens são recebidas, direciona
    essas mensagens à função que realiza o parse do json.
*/

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

#include "jsonParser.h"

#define MAX_SIZE 1024

void emergencyExit();

int main(int argc, char *argv[ ]){

    if (argc != 2){
        printf("Erro de execução, olhe o README para mais informações!!\n");
        exit(1);
    }
    server_path = malloc((sizeof(argv[1])*sizeof(char))+1);
    strcpy(server_path, argv[1]);
    
    typedef struct sockaddr_in sockaddr_in;
    typedef struct sockaddr sockaddr;
    ssize_t n;

    int serverSocket = 0, clientSocket = -1;
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

    while(1){
        listen(serverSocket, 5); //can have 5 connection waiting at max

        clientSocket = accept(serverSocket, (sockaddr *) &client_address, &len); //-> substituir valores de null por outras estruturas se quiser pegar o endereço do cliente
        
        if(clientSocket != -1){
            if(fork() == 0){ //CHILD
                printf("client socket: %d\n", clientSocket);
                if(clientSocket == -1){
                    printf("The client has disconnected\n");
                }
                close(serverSocket);
                
                again:
                    while ( (n = recv(clientSocket, request, MAX_SIZE, 0)) > 0){
                        printf("The client has requested: %s", request);
                        printf("buffer size: %ld\n", n);

                        parse(request, clientSocket);

                        if (n < 0 && errno == 4)
                            goto again;
                        else if (n < 0)
                            printf("str_echo: recv error");
                    }
            }else{ //PARENT
                close(clientSocket);	
            }
        } 
    }
  
    return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

typedef struct Profile {
    char email[30];
    char name[30];
    char surname[30];
    char address[45];
    char course[30];
    char courseCompletionYear[4];
    char *professionalExperience[300]; //vetor de string
    char *skill[300]; //vetor de strings
} Profile;

Profile readProfile(char *email); //FUNÇÃO PRIORITÁRIA - FAZER PRIMEIRO
Profile removeProfile(char *email);


int main(){
    
    typedef struct sockaddr_in sockaddr_in;
    typedef struct sockaddr sockaddr;
    char *clientMessage = "OI, EU SOU O CLIENTE", response[256];
    int mySocket, connectionStatus;

    //creating a TCP socket
    mySocket = socket(AF_INET, SOCK_STREAM, 0);

    //socket address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(50000);
    server_address.sin_addr.s_addr = INADDR_ANY;//server address -> substituir pelo IP do servidor quando em outro computado

    connectionStatus = connect(mySocket, (sockaddr *) &server_address, sizeof(server_address));

    if(connectionStatus == -1){
        printf("Connection failed\n\n");
        close(mySocket);
        return 1;
    }

    //receive message from server;
    recv(mySocket, &response, sizeof(response), 0);
    printf("The server has responded: %s\n", response);

    close(mySocket);

    return 0;

}
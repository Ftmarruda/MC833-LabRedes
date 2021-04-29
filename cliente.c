#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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
    //creating a TCP socket
    int mySocket, connectionStatus;
    mySocket = socket(AF_INET, SOCK_STREAM, 0);

    //socket address
    typedef struct sockaddr_in sockaddr_in;
    typedef struct sockaddr sockaddr;
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(50000);
    server_address.sin_addr.s_addr = INADDR_ANY;//server address -> substituir pelo IP do servidor

    connectionStatus = connect(mySocket, (sockaddr *) &server_address, sizeof(server_address));

    if(connectionStatus == -1){
        printf("Connection failed\n\n");
        return 1;
    }

    return 0;

}
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
    char request[256], response[256];
    int serverSocket, status;

    strcpy(request, "QUERO CRIAR O PERFIL\n");
    strcpy(response, "\0");
    //creating a TCP socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    //socket address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(50000);
    server_address.sin_addr.s_addr = INADDR_ANY;//server address -> substituir pelo IP do servidor quando em outro computado

    status = connect(serverSocket, (sockaddr *) &server_address, sizeof(server_address));

    if(status == -1){
        perror("Connection failed\n\n");
        close(serverSocket);
        return 1;
    }

    //keep server communication
    while(1){
        //send request
        status = send(serverSocket, &request, sizeof(request), 0);
		if(status < 0){
			printf("Send failed, error code %d\n", status);
			return 1;
		}
		
		//receive message from server;
		status = recv(serverSocket, &response, sizeof(response), 0);
        if(status < 0){
			printf("Recv failed, error code %d\n", status);
			break;
		}
		
		printf("The server has responded: %s\n", response);

    }

    close(serverSocket);

    return 0;

}
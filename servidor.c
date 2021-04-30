#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include <sqlite3.h>
#include "dao.h"

int main(){

    typedef struct sockaddr_in sockaddr_in;
    typedef struct sockaddr sockaddr;

    char serverMessage[256], request[256];
    int serverSocket, clientSocket, status;

    strcpy(request, "\0");
    strcpy(request, "OI, EU SOU O SERVIDOR");
    //create the server socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    //define server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(50000);
    server_address.sin_addr.s_addr = INADDR_ANY;//server address -> substituir pelo IP do servidor quando em outro computador

    //bind the socket to IP and port
    bind(serverSocket, (sockaddr *) &server_address, sizeof(server_address));

    listen(serverSocket, 1); //can have 1 connection waiting at max

    //accept client connection
    clientSocket = accept(serverSocket, NULL, NULL); //-> substituir valores de null por outras estruturas se quiser pegar o endereço do cliente
    
    while(1){
        //receive message from client
        status = recv(clientSocket, &request, sizeof(request), 0);
        if(status < 0){
			printf("Recv failed, error code %d\n", status);
		}

        //send message
        status = send(clientSocket, &request, sizeof(request), 0);
		if(status < 0){
			printf("Send failed, error code %d\n", status);
			return 1;
		}
		
		printf("The client has requested: %s\n", request);

    }


    //receive message from client
    //recv(serverSocket, &request, sizeof(request), 0);

    //send message
    //send(clientSocket, &request, sizeof(request), 0);

    //close socket
    close(serverSocket);

    //createProfile("felipe@example.com", "Felipe", "Tiago", "Disneyland, Orlando", "Counter Strike University", "2022");
    //createProfile("gabriel@example.com", "Gabriel", "Silveira", "Unicamp, Barão Geraldo", "Counter Strike University", "2022");

    //addExperience("banana@example.com", "Trabalhei por dois anos na Conpec Corporation");
    //addExperience("felipe@example.com", "Faço cerveja");
    //addExperience("gabriel@example.com", "Sou coach");

    //addSkill("felipe@example.com", "HTML");
    //addSkill("felipe@example.com", "CSS");

    //addSkill("gabriel@example.com", "HTML");
    //addSkill("gabriel@example.com", "SQL");
    //addSkill("gabriel@example.com", "JavaScript");

    //addSkill("banana@example.com", "JavaScript");

    //removeProfile("gabriel@example.com");

    //listAllProfiles();
    //readProfile("felipe@example.com");
    //listProfilesBasedOnGraduationYear("2022");
    //listProfilesBasedOnSkill("Botar o pé atrás da cabeça");
    //listProfilesBasedOnEducation("Counter Strike University");
    
    return 0;
}

//------------------------------
//------||   FUNÇÕES    ||------
//------------------------------

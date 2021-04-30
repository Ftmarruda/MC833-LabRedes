#ifndef test
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#endif

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;
//Global variables
int serverSocket;
struct sockaddr_in server_address;
char request[256], response[256];

bool createProfile();
bool addExperience(char email[30], char professionalExperience[100]);
bool addSkill(char email[30], char skill[100]);
bool listProfilesBasedOnSkill(char skill[100]);
bool listProfilesBasedOnEducation(char education[100]);
bool listProfilesBasedOnGraduationYear(char graduationYear[4]);
bool listAllProfiles();
bool readProfile(char *email);
bool removeProfile(char *email);


bool createProfile(){
    char email[30], name[30], surname[30], address[100], education[100], graduationYear[4];
    printf("------------------------------------------\n\n");
    printf("\n        1. Criar perfil\n");
    printf("------------------------------------------\n\n");

    printf("-> Insira o email do perfil: ");
    scanf("%s", email);

    printf("-> Insira o primeiro nome do perfil: ");
    scanf("%s", name);

    printf("-> Insira o último nome do perfil: ");
    scanf("%s", surname);

    printf("-> Insira o último nome do perfil: ");
    scanf("%s", surname);

    printf("-> Insira o endereço do perfil: ");
    scanf("%s", address);

    printf("-> Insira o curso do perfil: ");
    scanf("%s", education);

    printf("-> Insira o ano de conclusão de curso do perfil: ");
    scanf("%s", graduationYear);

    printf("\n\nEnviando informações ao servidor\n");
    printf("-----------------Aguarde-----------------\n\n");
    int status;
    status = send(serverSocket, &request, sizeof(request), 0);
            if(status < 0){
                printf("Send failed, error code %d\n", status);
                return false;
            }
            
            //receive message from server;
            status = recv(serverSocket, &response, sizeof(response), 0);
            if(status < 0){
                printf("Recv failed, error code %d\n", status);
                return false;
            }
            printf("The server has responded: %s\n", response);
    return true;
}

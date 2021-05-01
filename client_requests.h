#ifndef test
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "JSONfier.h"
#endif

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;
//Global variables
int serverSocket;
struct sockaddr_in server_address;
char request[256], response[256];

bool createProfile();
bool addExperience();
bool addSkill();
bool listProfilesBasedOnSkill(char skill[100]);
bool listProfilesBasedOnEducation(char education[100]);
bool listProfilesBasedOnGraduationYear(char graduationYear[4]);
bool listAllProfiles();
bool readProfile(char *email);
bool removeProfile(char *email);


bool createProfile(){
    //char email[30], name[30], surname[30], address[100], education[100], graduationYear[4];
    Profile profile;
    int status;

    printf("------------------------------------------\n\n");
    printf("\n        1. Criar perfil\n");
    printf("------------------------------------------\n\n");

    printf("-> Insira o email do perfil: ");
    scanf("%s", profile.email);

    printf("-> Insira o primeiro nome do perfil: ");
    scanf("%s", profile.name);

    printf("-> Insira o último nome do perfil: ");
    scanf("%s", profile.surname);

    printf("-> Insira o endereço do perfil: ");
    scanf("%s", profile.address);

    printf("-> Insira o curso do perfil: ");
    scanf("%s", profile.education);

    printf("-> Insira o ano de conclusão de curso do perfil: ");
    scanf("%s", profile.graduationYear);

    printf("\n\nEnviando informações ao servidor\n");
    printf("-----------------Aguarde-----------------\n\n");
    
    //CRIA STRINGS JSON PARA AS REQUESTS AO SERVIDOR
    printf("%s", create(profile));

    /*
    status = send(serverSocket, &profile, sizeof(profile), 0);
    if(status < 0){
        printf("Send failed, error code %d\n", status);
        return false;
    }
            
    //receive message from server;
    status = recv(serverSocket, response, sizeof(response), 0);
    if(status < 0){
        printf("Recv failed, error code %d\n", status);
        return false;
    }

    printf("The server has responded: %s\n", response);*/

    return true;
}

bool addExperience(){
    char email[30], professionalExperience[100];
    printf("------------------------------------------\n\n");
    printf("\n    2. Adicionar experiência à perfil\n");
    printf("------------------------------------------\n\n");

    printf("-> Insira o email do perfil: ");
    scanf("%s", email);

    printf("-> Insira a experiência profissonal do perfil: ");
    scanf("%s", professionalExperience);
    return true;
}

bool addSkill(){
    char email[30], skill[100];
    printf("------------------------------------------\n\n");
    printf("\n    3. Adicionar habilidade à perfil\n");
    printf("------------------------------------------\n\n");

    printf("-> Insira o email do perfil: ");
    scanf("%s", email);

    printf("-> Insira a habilidade que deseja adicionar ao perfil: ");
    scanf("%s", skill);

    return true;
}

bool list_user(){

}

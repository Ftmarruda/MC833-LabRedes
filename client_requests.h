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

#define MAX_CARAC 100

//Global variables
int serverSocket;
struct sockaddr_in server_address;
char request[256], response[256];

bool createProfile();
bool addExperience();
bool addSkill();
bool listProfilesBasedOnSkill();
bool listProfilesBasedOnEducation();
bool listProfilesBasedOnGraduationYear();
bool listAllProfiles();
bool readProfile();
bool removeProfile();
void cleanBuffer();

void cleanBuffer(){
    int n;
    while((n = getchar()) != EOF && n != '\n' );
}

bool createProfile(){
    Profile profile;
    long int status;
    int aux;

    printf("\n\n------------------------------------------");
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
    char* json = create(profile);
    printf("%s\n", json);

    status = 0;
    while(status < sizeof(profile)){
        status = send(serverSocket, &json, sizeof(json), 0);
        printf("%ld\n", status);
        printf("%ld\n", sizeof(profile));
    }
    if(status < 0){
        printf("Send failed, error code %ld\n", status);
        return false;
    }
            
    //receive message from server;
    status = recv(serverSocket, response, sizeof(response), 0);
    if(status < 0){
        printf("Recv failed, error code %ld\n", status);
        return false;
    }

    printf("The server has responded: %s\n", response);

    return true;
}

bool addExperience(){
    char email[30], **professionalExperience, aux[MAX_CARAC];
    int num_experiencias;
    printf("\n\n------------------------------------------");
    printf("\n    2. Adicionar experiência à perfil\n");
    printf("------------------------------------------\n\n");

    printf("-> Insira o email do perfil: ");
    scanf("%s", email);
    
    printf("-> Quantas experiências você gostaria de adicionar?\nR: ");
    scanf("%d", &num_experiencias);
    professionalExperience = calloc(num_experiencias, sizeof(char*));

    int i;
    for(i = 0; i < num_experiencias; i++){
        professionalExperience[i] = calloc(MAX_CARAC, sizeof(char));
        printf("-> Insira a %d° experiência profissonal do perfil: ", i+1);
        scanf("%s", aux);
        if(sizeof(aux) > MAX_CARAC){
            printf("ERRO!!!! Número de caracteres excede o máximo permitido de %d caracteres. Tente novamente :)\n", MAX_CARAC);
            i--;
        }else{
            strcpy(professionalExperience[i], aux);
            printf("%s\n", professionalExperience[i]);
        }    
    }
    
    //Tratar os dados de professional experience para enviar ao servidor

    printf("\n\nEnviando informações ao servidor\n");
    printf("-----------------Aguarde-----------------\n\n");

    //COMUNICAÇÂO COM O SERVIDOR

    return true;
}

bool addSkill(){
    char email[30], **skill, aux[MAX_CARAC];
    int num_skills;
    printf("\n\n------------------------------------------");
    printf("\n    3. Adicionar habilidade à perfil\n");
    printf("------------------------------------------\n\n");

    printf("-> Insira o email do perfil: ");
    scanf("%s", email);

    printf("-> Quantas habilidades você gostaria de adicionar à %s?\nR: ", email);
    scanf("%d", &num_skills);
    skill = calloc(num_skills, sizeof(char*));

    int i;
    for(i = 0; i < num_skills; i++){
        skill[i] = calloc(MAX_CARAC, sizeof(char));
        printf("-> Insira a %d° habilidade do perfil: ", i+1);
        scanf("%s", aux);
        if(sizeof(aux) > MAX_CARAC){
            printf("ERRO!!!! Número de caracteres excede o máximo permitido de %d caracteres. Tente novamente :)\n", MAX_CARAC);
            i--;
        }else{
            strcpy(skill[i], aux);
            printf("%s\n", skill[i]);
        }    
    }

    printf("\n\nEnviando informações ao servidor\n");
    printf("-----------------Aguarde-----------------\n\n");

    //Tratamento dos dados e comunicação com o servidor

    return true;
}

bool readProfile(){
    char *email;
    printf("\n\n------------------------------------------");
    printf("\n    a. Ler perfil a partir de email\n");
    printf("------------------------------------------\n\n");

    printf("-> Insira o email do perfil: ");
    scanf("%s", email);

    printf("\n\nEnviando informações ao servidor\n");
    printf("-----------------Aguarde-----------------\n\n");

    //Tratamento dos dados e comunicação com o servidor

    return true;
}

bool listAllProfiles(){
    char *email;
    printf("\n\n------------------------------------------");
    printf("\n    b. Listar todos os perfis existentes\n");
    printf("------------------------------------------\n\n");

    printf("\n\nRecuperando informações do servidor\n");
    printf("-----------------Aguarde-----------------\n\n");

    //Tratamento dos dados e comunicação com o servidor

    return true;
}

bool listProfilesBasedOnSkill(){
    char skill[MAX_CARAC];

    printf("\n\n------------------------------------------");
    printf("\n    c. Listar baseado em habilidade\n");
    printf("------------------------------------------\n\n");

    printf("-> Insira a skill que procura: ");
    scanf("%s", skill);

    printf("\n\nEnviando informações ao servidor\n");
    printf("-----------------Aguarde-----------------\n\n");

    //Tratamento dos dados e comunicação com o servidor

    return true;
}

bool listProfilesBasedOnEducation(){
    char education[MAX_CARAC];

    printf("\n\n------------------------------------------");
    printf("\n    d. Listar baseado em curso\n");
    printf("------------------------------------------\n\n");

    printf("-> Insira o curso que procura(4 números): ");
    scanf("%s", education);

    printf("\n\nEnviando informações ao servidor\n");
    printf("-----------------Aguarde-----------------\n\n");

    //Tratamento dos dados e comunicação com o servidor

    return true;
}

bool listProfilesBasedOnGraduationYear(){
    char graduationYear[4];

    printf("\n\n------------------------------------------");
    printf("\n e. Listar baseado em ano de conclusão\n");
    printf("------------------------------------------\n\n");

    printf("-> Insira o ano de conclusão que procura: ");
    scanf("%s", graduationYear);

    printf("\n\nEnviando informações ao servidor\n");
    printf("-----------------Aguarde-----------------\n\n");

    //Tratamento dos dados e comunicação com o servidor

    return true;
}

bool list(){

    char letter;
    int flag = 1;
    bool retorno = true;
    while(flag){
        printf("\n\n------------------------------------------\n");
        printf("         Listagem de usuários!!!\n");
        printf("------------------------------------------\n\n");
        printf("Qual listagem de usuários você gostaria de realizar?\n"
                "   a. Ler perfil a partir de email\n"
                "   b. Listar todos os perfis existentes\n"
                "   c. Listar todos os perfis com uma certa habilidade\n"
                "   d. Listar todos os perfis de um determinado curso\n"
                "   e. Listar todos os perfis que se formam em determinado ano\n"
                "   f. Cancelar e retornar ao menu principal\n"
                "Digite o número da opção que deseja realizar: "
        );
        scanf("%c", &letter);
        cleanBuffer(); //we clean the buffer here
        switch (letter)
        {
        case 'a'://ler perfil a partir de email
            retorno = readProfile();
            flag = 0;
            break;

        case 'b'://ler todos os perfis
            retorno = listAllProfiles();
            flag = 0;
            break;
        
        case 'c'://ler usuários com determinada habilidade
            retorno = listProfilesBasedOnSkill();
            flag = 0;
            break;

        case 'd'://Ler usuários de determinado curso
            retorno = listProfilesBasedOnEducation();
            flag = 0;
            break;

        case 'e'://ler usuários que se formam em determinado ano
            retorno = listProfilesBasedOnGraduationYear();
            flag = 0;
            break;

        case 'f'://retornar a menu principal
            printf("----Retornando a menu principal...----\n\n");
            flag = 0;
            break;    

        default://colocar algum caracter invalido
            printf("\n\n------------------------------------------\n");
            printf("--------------Opção-Invalida--------------\n");
            printf("------------------------------------------\n\n");
            break;
        }
        
    }
    cleanBuffer();
    return retorno;
}

bool removeProfile(){
    char email[30];
    printf("\n\n------------------------------------------");
    printf("\n        5. Remover perfil\n");
    printf("------------------------------------------\n\n");

    printf("-> Insira o email do perfil que deseja remover: ");
    scanf("%s", email);



    printf("\n\nEnviando informações ao servidor\n");
    printf("-----------------Aguarde-----------------\n\n");
    //Tratamento dos dados e comunicação com o servidor


    return true;
}

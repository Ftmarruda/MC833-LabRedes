

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>


#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include "client_requests.h"

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

void cleanBuffer(){
    int n;
    while((n = getchar()) != EOF && n != '\n' );
}



int main(){
    int status;

    strcpy(request, "Connect\n");
    strcpy(response, "\0");

    printf("Conectando ao servidor.....\n");
    printf("Aguarde.....\n");
    //creating a TCP socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    //socket address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(50000);
    server_address.sin_addr.s_addr = inet_addr("192.168.7.226"); //o IP local do servidor vai aqui

    status = connect(serverSocket, (sockaddr *) &server_address, sizeof(server_address));
    if(status == -1){
        perror("Connection failed");
        close(serverSocket);
        return 1;
    }

    printf("Servidor Conectado!\n");

    char op = -1;
    char email[30], name[30],surname[30], address[100], education[100], graduationYear[4];
    int flag = 1;
    //keep server communication
    while(flag){
        printf("\n\n------------------------------------------\n");
        printf("         Requisições de cliente!!!\n");
        printf("------------------------------------------\n\n");
        printf("Você gostaria de realizar qual operação?\n"
                "   1. Adicionar novo usuário\n"
                "   2. Adicionar experiência profissional à usuário existente\n"
                "   3. Adicionar habilidade à usuário existente\n"
                "   4. Listar usuário\n"
                "   5. Remover usuário existente\n"
                "   6. Desconectar do servidor\n"
                "Digite o número da opção que deseja realizar: "
        );
        scanf("%c", &op);
        cleanBuffer(); //we clean the buffer here
        switch (op)
        {
        case '1'://criar novo usuário
            createProfile();
            break;
        
        case '3':
            break;

        case '4':
            break;

        case '5':
            break;

        case '6':
            printf("\n\nTchau! Volte sempre!\n\n");
            flag = 0;
            break;    

        default:
            printf("\n\n------------------------------------------\n");
            printf("--------------Opção-Invalida--------------\n");
            printf("------------------------------------------\n");
            break;
        }
    }

    close(serverSocket);

    return 0;

}
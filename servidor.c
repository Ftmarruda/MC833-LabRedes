/*
 *
 *
 * Comandos a serem executados pelo servidor
 *
 *
 */
#include <stdlib.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdbool.h>

//Structs

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

//Protótipos

bool createProfile (char email[30]);
bool addProfessionalExperience (char email[30], char professionalExperience[300]);
void listProfilesBasedOnCourse(char course[30]);
void listProfilesBasedOnSkill(char skill[300]);
void listProfilesBasedOnCourseCompletionYear(char courseCompletionYear[4]);
void listAllProfiles();
Profile readProfile(char *email); //FUNÇÃO PRIORITÁRIA - FAZER PRIMEIRO
Profile removeProfile(char *email);



int main(){

    printf("SQLite3 version: %s\n", sqlite3_libversion()); 
    return 0;

}


//Funções

//Cadastrar um novo perfil utilizando o email como identificador
//retornos:
//true: conta criada com sucesso
//false: para conta criada sem sucesso (já existe outra conta com esse email)
bool createProfile (char email[30]){
    bool signal = true;//mock
    return signal;
}


//acrescentar uma nova experiência profissional em um perfil; 
//casos a serem tratados:
//true: experiência adicionada com sucesso
//false: não existe conta vinculada ao e-mails
bool addProfessionalExperience (char email[30], char professionalExperience[300]){
    bool signal = true;//mock
    return signal;
}

//listar todas as pessoas (email e nome) formadas em um determinado curso;
//casos a serem tratados:
//true: perfis listados com sucesso
//false: o curso não existe
void listProfilesBasedOnCourse(char course[30]){
}

// - listar todas as pessoas (email e nome) que possuam uma determinada habilidade;
//casos a serem tratados:
//true: perfis listados com sucesso
//false: a habilidade não existe
void listProfilesBasedOnSkill(char skill[300]){
}

//listar todas as pessoas (email, nome e curso) formadas em um determinado ano;
//casos a serem tratados:
//true: perfis listados com sucesso
//false: ninguém se formou naquele ano
void listProfilesBasedOnCourseCompletionYear(char courseCompletionYear[4]){
}

//listar todas as informações de todos os perfis;
//casos a serem tratados:
//true: perfis listados com sucesso
//false: não há perfis
void listAllProfiles(){
    

}

//FUNÇÃO PRIORITÁRIA - FAZER PRIMEIRO
//dado o email de um perfil, retornar suas informações
//casos a serem tratados:
//true: perfil lido com sucesso
//false: não existe nenhum perfil vinculado ao e-mail
//retorno: o struct Profile vinculado ao perfil lido

Profile readProfile(char *email){
    Profile profile;
    return profile;
}

//remover um perfil a partir de seu identificador (email). 
//casos a serem tratados:
//true: perfil removido com sucesso
//false: não existe nenhum perfil vinculado ao e-mail
//retorno: o struct Profile vinculado ao perfil removido
Profile removeProfile(char *email){
    Profile profile;
    return profile;

}
    
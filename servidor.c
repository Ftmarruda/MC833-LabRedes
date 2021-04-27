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
#include <string.h>

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

bool createProfile (char email[30], char name[30], char surname[30], char address[100], char education[100], char graduationYear[4]);
bool addProfessionalExperience (char email[30], char professionalExperience[100]);
void listProfilesBasedOnCourse(char course[30]);
void listProfilesBasedOnSkill(char skill[100]);
void listProfilesBasedOnCourseCompletionYear(char courseCompletionYear[4]);
void listAllProfiles();
Profile readProfile(char *email); //FUNÇÃO PRIORITÁRIA - FAZER PRIMEIRO
Profile removeProfile(char *email);



int main(){

    bool signal = true;
    sqlite3 *db;
    char *err_msg = 0;
    
    //signal = createProfile("banana@example.com", "Gabriel", "Silveira", "Disneyland, Orlando", "Counter Strike University", "2022");
    signal = addProfessionalExperience("banana@example.com", "Trabalhei por dois anos na Conpec Corporation");


    //if error
    if (!signal) {
        return 1;
    }
    
    return 0;

}


//Funções

//Cadastrar um novo perfil utilizando o email como identificador
//retornos:
//true: conta criada com sucesso
//false: para conta criada sem sucesso (já existe outra conta com esse email)
bool createProfile (char email[30], char name[30], char surname[30], char address[100], char education[100], char graduationYear[4]){
    
    bool signal = true;
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("app.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }

    //Query

    char sql[200];
    strcpy(sql, "INSERT INTO Profiles VALUES('");
    strcat(sql, email);
    strcat(sql, "', '");
    strcat(sql, name);
    strcat(sql, "', '");
    strcat(sql, surname);
    strcat(sql, "', '");
    strcat(sql, address);
    strcat(sql, "', '");
    strcat(sql, education);
    strcat(sql, "', ");
    strcat(sql, graduationYear);
    strcat(sql, ");");

    sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        signal = false;
    }
    
    sqlite3_close(db);

    return signal;
}


//acrescentar uma nova experiência profissional em um perfil; 
//casos a serem tratados:
//true: experiência adicionada com sucesso
//false: não existe conta vinculada ao e-mails
bool addProfessionalExperience (char email[30], char professionalExperience[100]){
    
    bool signal = true;
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("app.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }

    //Query

    char sql[200];// = "INSERT INTO Experiences VALUES(NULL, 'banana@example.com', 'Trabalhei na Pecpec')";
    strcpy(sql, "INSERT INTO Experiences VALUES(NULL, '");
    strcat(sql, email);
    strcat(sql, "', '");
    strcat(sql, professionalExperience);
    strcat(sql, "');");

    sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        signal = false;
    }
    
    sqlite3_close(db);

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
    
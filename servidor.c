#include <stdlib.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//Protótipos
bool createProfile(char email[30], char name[30], char surname[30], char address[100], char education[100], char graduationYear[4]);
bool addProfessionalExperience(char email[30], char professionalExperience[100]);
bool addSkill(char email[30], char skill[100]);
bool listProfilesBasedOnSkill(char skill[100]);
bool listProfilesBasedOnCourse(char course[30]);
bool listProfilesBasedOnGraduationYear(char graduationYear[4]);
bool listAllProfiles();
bool readProfile(char *email);
bool removeProfile(char *email);

int callback(void *, int, char **, char **);



int main(){

    bool signal = true;
    sqlite3 *db;
    char *err_msg = 0;
    
    //signal = createProfile("felipe@example.com", "Felipe", "Tiago", "Disneyland, Orlando", "Counter Strike University", "2022");
    //signal = addProfessionalExperience("banana@example.com", "Trabalhei por dois anos na Conpec Corporation");
    //signal = addSkill("banana@example.com","Botar o pé atrás da cabeça");
    //signal = listAllProfiles();
    //signal = readProfile("felipe@example.com");
    signal = listProfilesBasedOnGraduationYear("2022");

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
   
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("app.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return false;
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
        return false;
    }
    
    sqlite3_close(db);

    return true;
}


//acrescentar uma nova experiência profissional em um perfil; 
//casos a serem tratados:
//true: experiência adicionada com sucesso
//false: não existe conta vinculada ao e-mails
bool addProfessionalExperience (char email[30], char professionalExperience[100]){
    
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("app.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return false;
    }

    //Query

    char sql[200];
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
        return false;
    }
    
    sqlite3_close(db);

    return true;
}

bool addSkill(char email[30], char skill[100]){

    sqlite3 *db;
    char *err_msg = 0;
    char *sql;
    
    int rc = sqlite3_open("app.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return false;
    }

    //Query 1

    sql = malloc(200*sizeof(char));
    strcpy(sql, "INSERT INTO Skills VALUES(NULL, '");
    strcat(sql, skill);
    strcat(sql, "');");

    sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        return false;
    }

    free(sql);
    //Query 2
    sql = malloc(200*sizeof(char));;
    strcpy(sql, "INSERT INTO Profiles_Skills VALUES('");
    strcat(sql, email);
    strcat(sql, "', '");
    strcat(sql, skill);
    strcat(sql, "');");

    sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        return false;
    }
    
    sqlite3_close(db);

    return true;
}

//listar todas as pessoas (email e nome) formadas em um determinado curso;
//casos a serem tratados:
//true: perfis listados com sucesso
//false: o curso não existe
bool listProfilesBasedOnCourse(char course[30]){
    return true;
}

// - listar todas as pessoas (email e nome) que possuam uma determinada habilidade;
//casos a serem tratados:
//true: perfis listados com sucesso
//false: a habilidade não existe
bool listProfilesBasedOnSkill(char skill[300]){
    return true;
}

//listar todas as pessoas (email, nome e curso) formadas em um determinado ano;
//casos a serem tratados:
//true: perfis listados com sucesso
//false: ninguém se formou naquele ano
bool listProfilesBasedOnGraduationYear(char graduationYear[4]){
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("app.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", 
                sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return false;
    }
    
    char sql[200];
    strcpy(sql, "SELECT * FROM Profiles WHERE Graduation_Year == ");
    strcat(sql, graduationYear);
    strcat(sql, ";");

        
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);
        
        return false;
    } 
    
    sqlite3_close(db);
    
    return true;
}

//listar todas as informações de todos os perfis;
//casos a serem tratados:
//true: perfis listados com sucesso
//false: não há perfis
bool listAllProfiles(){

    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("app.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", 
                sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return false;
    }
    
    char *sql = "SELECT * FROM Profiles";
        
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);
        
        return false;
    } 
    
    sqlite3_close(db);
    
    return true;

}

//FUNÇÃO PRIORITÁRIA - FAZER PRIMEIRO
//dado o email de um perfil, retornar suas informações
//casos a serem tratados:
//true: perfil lido com sucesso
//false: não existe nenhum perfil vinculado ao e-mail
//retorno: o struct Profile vinculado ao perfil lido

bool readProfile(char *email){

    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("app.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", 
                sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return false;
    }
    
    char sql[200];
    strcpy(sql, "SELECT * FROM Profiles WHERE Email == '");
    strcat(sql, email);
    strcat(sql, "';");

        
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);
        
        return false;
    } 
    
    sqlite3_close(db);
    
    return true;
}

//remover um perfil a partir de seu identificador (email). 
//casos a serem tratados:
//true: perfil removido com sucesso
//false: não existe nenhum perfil vinculado ao e-mail
//retorno: o struct Profile vinculado ao perfil removido
bool removeProfile(char *email){
    return true;

}


//prints query results
int callback(void *NotUsed, int argc, char **argv, 
                    char **azColName) {
    
    NotUsed = 0;
    
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    
    printf("\n");
    
    return 0;
}
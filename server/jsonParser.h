#include "../lib/cJSON.h"
#include "../lib/profileTypes.h"
#include "dao.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Transforma as strings JSON em structs profile à serem passados para o banco de dados.

bool parse(char* JSONstring);
bool parseCreate(const cJSON *JSONobject);
bool parseAddSkill(char* operation, int len);
bool parseaddExperience(char* operation, int len);
bool parseRemove(char* operation);
bool parseListAll(char* operation, char* string);
bool parseListUser(char* operation, char* string);
bool parseListEducation(char* operation, char* string);
bool parseListSkill(char* operation, char* string);
bool parseListYear(char* operation, char* string);

bool parse(char* JSONstring){

    const cJSON *operation = NULL;
    const cJSON *JSONobject = NULL;
    int status = false;

    //Criando um objeto JSON a partir da string recebida
    cJSON *JSON = cJSON_Parse(JSONstring);
    if (JSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL){
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        status = false;
        goto end;
    }

    //obtendo a operação à ser executada
    operation = cJSON_GetObjectItemCaseSensitive(JSON, "operation");
    if (cJSON_IsString(operation) && (operation->valuestring != NULL)){
        printf("Checking operation: \"%s\"\n", operation->valuestring);
    }

    //CREATE
    if(strcmp(operation->valuestring, "CREATE")==0){

        //obtendo o perfil a ser criado
        JSONobject = cJSON_GetObjectItemCaseSensitive(JSON, "object");

        if(!parseCreate(JSONobject)){
            printf("The server couldn't create the profile\n");
            status = false;
            goto end;
        }else{
            printf("Profile created\n");
            status = true;
            goto end;
        }
    }

    end:
        cJSON_Delete(JSON);
        return status;
}

/*
----------------------------
--------   CREATE   --------
----------------------------
*/

bool parseCreate(const cJSON *JSONobject){

    //CRIA O STRUCT PROFILE COM OS DADOS DO PERFIL
    Profile profile;
    bool status = false;

    printf("PARSING...\n");

    strcpy(profile.email, cJSON_GetObjectItemCaseSensitive(JSONobject, "email")->valuestring);
    printf("-> Email: %s\n", profile.email);

    strcpy(profile.name, cJSON_GetObjectItemCaseSensitive(JSONobject, "name")->valuestring);
    printf("-> Name: %s\n", profile.name);

    strcpy(profile.surname, cJSON_GetObjectItemCaseSensitive(JSONobject, "surname")->valuestring);
    printf("-> Surname: %s\n", profile.surname);

    strcpy(profile.address, cJSON_GetObjectItemCaseSensitive(JSONobject, "address")->valuestring);
    printf("-> Address: %s\n", profile.address);

    strcpy(profile.education, cJSON_GetObjectItemCaseSensitive(JSONobject, "education")->valuestring);
    printf("-> Education: %s\n", profile.education);

    strcpy(profile.graduationYear, cJSON_GetObjectItemCaseSensitive(JSONobject, "graduationYear")->valuestring);
    printf("-> Graduation Year: %s\n", profile.graduationYear);

    //CRIA O PERFIL NO BANCO DE DADOS
    if(createProfile(profile)){
        printf("Data inserted in the database\n");
        status = true;
    }else{
        printf("Couldn't insert the data in the database\n");
        status = false;
    }

    return status;
}

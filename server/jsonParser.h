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
bool parseAddSkill(const cJSON *JSONobject);
bool parseaddExperience(const cJSON *JSONobject);
bool parseRemove(const cJSON *JSONobject);
bool parseListAll();
bool parseListUser(const cJSON *JSONobject);
bool parseListEducation(const cJSON *JSONobject);
bool parseListSkill(const cJSON *JSONobject);
bool parseListYear(const cJSON *JSONobject);

bool parse(char* JSONstring){

    const cJSON *operation = NULL;
    const cJSON *JSONobject = NULL;
    int status = false;
    cJSON *JSON = cJSON_Parse(JSONstring);

    //Criando um objeto JSON a partir da string recebida
    if(strcmp(JSONstring, "Connect\n")==0){
        printf("Cliente Conectado\n");
        status = true;
        goto end;
    }else{
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

        }else if(strcmp(operation->valuestring, "ADD_SKILL")==0){

            //obtendo o perfil a ser criado
            JSONobject = cJSON_GetObjectItemCaseSensitive(JSON, "object");

            if(!parseAddSkill(JSONobject)){
                printf("The server couldn't add the skills\n");
                status = false;
                goto end;
            }else{
                printf("Skills added to user\n");
                status = true;
                goto end;
            }

        }else if(strcmp(operation->valuestring, "ADD_EXP")==0){

            //obtendo o perfil a ser criado
            JSONobject = cJSON_GetObjectItemCaseSensitive(JSON, "object");

            if(!parseaddExperience(JSONobject)){
                printf("The server couldn't add the experiences\n");
                status = false;
                goto end;
            }else{
                printf("Experiences added to user\n");
                status = true;
                goto end;
            }

        }else if(strcmp(operation->valuestring, "REMOVE")==0){

            //obtendo o perfil a ser criado
            JSONobject = cJSON_GetObjectItemCaseSensitive(JSON, "object");

            if(!parseRemove(JSONobject)){
                printf("The server couldn't remove the user\n");
                status = false;
                goto end;
            }else{
                printf("User removed\n");
                status = true;
                goto end;
            }

        }else if(strcmp(operation->valuestring, "ListAll")==0){

            if(!parseListAll()){
                printf("The server couldn't list the users\n");
                status = false;
                goto end;
            }else{
                printf("Users listed\n");
                status = true;
                goto end;
            }

        }else if(strcmp(operation->valuestring, "ListUser")==0){

            //obtendo o perfil a ser criado
            JSONobject = cJSON_GetObjectItemCaseSensitive(JSON, "object");

            if(!parseListUser(JSONobject)){
                printf("The server couldn't list the users\n");
                status = false;
                goto end;
            }else{
                printf("Users listed\n");
                status = true;
                goto end;
            }

        }else if(strcmp(operation->valuestring, "ListEducation")==0){

            //obtendo o perfil a ser criado
            JSONobject = cJSON_GetObjectItemCaseSensitive(JSON, "object");

            if(!parseListEducation(JSONobject)){
                printf("The server couldn't list the users\n");
                status = false;
                goto end;
            }else{
                printf("Users listed\n");
                status = true;
                goto end;
            }

        }else if(strcmp(operation->valuestring, "ListSkill")==0){

            //obtendo o perfil a ser criado
            JSONobject = cJSON_GetObjectItemCaseSensitive(JSON, "object");

            if(!parseListSkill(JSONobject)){
                printf("The server couldn't list the users\n");
                status = false;
                goto end;
            }else{
                printf("Users listed\n");
                status = true;
                goto end;
            }

        }else if(strcmp(operation->valuestring, "ListYear")==0){

            //obtendo o perfil a ser criado
            JSONobject = cJSON_GetObjectItemCaseSensitive(JSON, "object");

            if(!parseListYear(JSONobject)){
                printf("The server couldn't list the users\n");
                status = false;
                goto end;
            }else{
                printf("Users listed\n");
                status = true;
                goto end;
            }

        }else{

            printf("The server couldn't parse the operation\n");
            status = false;
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

/*
* !!!!!!!!!!!!!!AJUSTAR addSkill e addExperience!!!!!!!!!!!!!!!!!!!
*/
bool parseAddSkill(const cJSON *JSONobject){
    char email[31];
    char skills[600];

    strcpy(email, cJSON_GetObjectItemCaseSensitive(JSONobject, "email")->valuestring);
    printf("-> Email: %s\n", email);

    strcpy(skills, cJSON_GetObjectItemCaseSensitive(JSONobject, "skills")->valuestring);
    printf("-> Skills: %s\n", skills);

    return addSkill(email, skills);
}

bool parseaddExperience(const cJSON *JSONobject){
    char email[31];
    cJSON* experiences = cJSON_GetObjectItemCaseSensitive(JSONobject, "experiences");
    char* exp;
    int size = cJSON_GetArraySize(experiences), aux;
    bool status = true;
    printf("Array: %s", (char*) experiences);
    printf("Size of array: %d\n", size);

    strcpy(email, cJSON_GetObjectItemCaseSensitive(JSONobject, "email")->valuestring);
    printf("-> Email: %s\n", email);

    for(aux = 0; aux < size; aux++){
        exp = (char*) cJSON_GetArrayItem(experiences, aux);
        printf("-> Experience %d: %s\n", aux, exp);
        status = addExperience(email, exp);
    }

    return status;
}

bool parseRemove(const cJSON *JSONobject){
    char email[31];

    strcpy(email, cJSON_GetObjectItemCaseSensitive(JSONobject, "email")->valuestring);
    printf("-> Email: %s\n", email);

    return removeProfile(email);
}

bool parseListAll(){
    return listAllProfiles();
}

bool parseListUser(const cJSON *JSONobject){

    char email[31];

    strcpy(email, cJSON_GetObjectItemCaseSensitive(JSONobject, "email")->valuestring);
    printf("-> Email: %s\n", email);

    return readProfile(email);
}

bool parseListEducation(const cJSON *JSONobject){

    char education[101];

    strcpy(education, cJSON_GetObjectItemCaseSensitive(JSONobject, "education")->valuestring);
    printf("-> Education: %s\n", education);

    return listProfilesBasedOnEducation(education);
}

bool parseListSkill(const cJSON *JSONobject){

    char skill[101];

    strcpy(skill, cJSON_GetObjectItemCaseSensitive(JSONobject, "skill")->valuestring);
    printf("-> Skill: %s\n", skill);

    return listProfilesBasedOnSkill(skill);
}

bool parseListYear(const cJSON *JSONobject){

    char graduationYear[5];

    strcpy(graduationYear, cJSON_GetObjectItemCaseSensitive(JSONobject, "graduationYear")->valuestring);
    printf("-> Graduation Year: %s\n", graduationYear);

    return listProfilesBasedOnGraduationYear(graduationYear);
}

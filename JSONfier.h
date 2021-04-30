//CRIA STRINGS JSON PARA AS REQUESTS AO SERVIDOR

#include <stdio.h>
#include "cJSON.h"
#include "profileTypes.h"

typedef struct JSONskill{
    char description[100];
} JSONskill;

typedef struct JSONexperience{
    char description[100];
} JSONexperience;

typedef struct JSONprofile {
    cJSON *email;
    cJSON *name;
    cJSON *surname;
    cJSON *address;
    cJSON *education;
    cJSON *graduationYear;
    JSONexperience *experience[100]; //vetor de experiencias
    JSONskill *skills[100]; //vetor de skills
} JSONprofile;

typedef struct JSONquery {
    cJSON *wrapper;
    cJSON *operation;
    cJSON *object;
} JSONquery;

char* create(Profile profile);

char* create(Profile profile){
    //Create JSON object
    JSONprofile JSONprofileCreate;
    JSONquery query;

    char *string = NULL;

    //WRAPPER
    query.wrapper = cJSON_CreateObject();
    if (query.wrapper == NULL){
        goto end;
    }
    
    //OPERATION
    query.operation = cJSON_CreateString("CREATE");
    if (query.operation == NULL){
        goto end;
    }
    /* after creation was successful, immediately add it to the monitor,
     * thereby transferring ownership of the pointer to it */
    cJSON_AddItemToObject(query.wrapper, "operation", query.operation);

    //PROFILE OBJECT
    query.object = cJSON_CreateObject();
    if (query.object == NULL){
        goto end;
    }
    cJSON_AddItemToObject(query.wrapper, "object", query.object);
    
    //EMAIL
    JSONprofileCreate.email = cJSON_CreateString(profile.email);
    if (JSONprofileCreate.email == NULL){
        goto end;
    }
    cJSON_AddItemToObject(query.object, "email", JSONprofileCreate.email);

    //NAME
    JSONprofileCreate.name = cJSON_CreateString(profile.name);
    if (JSONprofileCreate.name == NULL){
        goto end;
    }
    cJSON_AddItemToObject(query.object, "name", JSONprofileCreate.name);

    //SURNAME
    JSONprofileCreate.surname = cJSON_CreateString(profile.surname);
    if (JSONprofileCreate.surname  == NULL){
        goto end;
    }
    cJSON_AddItemToObject(query.object, "surname", JSONprofileCreate.surname);

    //ADDRESS
    JSONprofileCreate.address = cJSON_CreateString(profile.address);
    if (JSONprofileCreate.address == NULL){
        goto end;
    }
    cJSON_AddItemToObject(query.object, "address", JSONprofileCreate.address);

    //EDUCATION
    JSONprofileCreate.education = cJSON_CreateString(profile.education);
    if (JSONprofileCreate.education == NULL){
        goto end;
    }
    cJSON_AddItemToObject(query.object, "education", JSONprofileCreate.education);

    //GRADUATION YEAR
    JSONprofileCreate.graduationYear = cJSON_CreateString(profile.graduationYear);
    if (JSONprofileCreate.graduationYear == NULL){
        goto end;
    }
    cJSON_AddItemToObject(query.object, "graduationYear", JSONprofileCreate.graduationYear);

    //JSONfy to string
    string = cJSON_Print(query.wrapper);
    if (string == NULL)
    {
        fprintf(stderr, "Objeto JSON não pôde ser exibido.\n");
    }

    if(0){
        end:
        printf("Falha ao criar o objeto JSON.\n");
    }
    
    cJSON_Delete(query.wrapper);

    return string;

}
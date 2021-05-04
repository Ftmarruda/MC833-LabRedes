//CRIA STRINGS JSON PARA AS REQUESTS AO SERVIDOR

#include <stdio.h>
#include <string.h>
#include "../lib/cJSON.h"
#include "../lib/profileTypes.h"

typedef struct JSONprofile {
    cJSON *email;
    cJSON *name;
    cJSON *surname;
    cJSON *address;
    cJSON *education;
    cJSON *graduationYear;
    cJSON *experience; //vetor de experiencias
    cJSON *skills; //vetor de skills
} JSONprofile;

typedef struct JSONquery {
    cJSON *wrapper;
    cJSON *operation;
    cJSON *object;
} JSONquery;

char* createJson(Profile profile);
char* addSkillJson(Profile profile, int len);
char* addExperienceJson(Profile profile, int len);
char* removeJson(Profile profile);
char* listJson(char operation, char* string);
bool parseServerMessage(char* response, int len);

/*
----------------------------
--------   CREATE   --------
----------------------------
*/

char* createJson(Profile profile){
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
    string = cJSON_PrintUnformatted(query.wrapper);
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

/*
-------------------------------
--------   ADD SKILL   --------
-------------------------------
*/

char* addSkillJson(Profile profile, int len){
    //Create JSON object
    JSONprofile JSONprofileCreate;
    JSONquery query;

    char *string = NULL;

    query.wrapper = cJSON_CreateObject();
    if (query.wrapper == NULL){
        goto end;
    }

    //OPERATION
    query.operation = cJSON_CreateString("ADD_SKILL");
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

    //Array of skills
    JSONprofileCreate.skills = cJSON_CreateStringArray(profile.skills, len);
    if (JSONprofileCreate.skills == NULL){
        goto end;
    }
    cJSON_AddItemToObject(query.object, "skills", JSONprofileCreate.skills);
    

    //JSONfy to string
    string = cJSON_PrintUnformatted(query.wrapper);
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

/*
------------------------------------
--------   ADD EXPERIENCE   --------
------------------------------------
*/

char* addExperienceJson(Profile profile, int len){
    //Create JSON object
    JSONprofile JSONprofileCreate;
    JSONquery query;

    char *string = NULL;

    query.wrapper = cJSON_CreateObject();
    if (query.wrapper == NULL){
        goto end;
    }

    //OPERATION
    query.operation = cJSON_CreateString("ADD_EXP");
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

    //Array of experiences
    JSONprofileCreate.experience = cJSON_CreateStringArray(profile.experience, len);
    if (JSONprofileCreate.experience == NULL){
        goto end;
    }
    cJSON_AddItemToObject(query.object, "experiences", JSONprofileCreate.experience);

    //JSONfy to string
    string = cJSON_PrintUnformatted(query.wrapper);
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

/*
----------------------------
--------   DELETE   --------
----------------------------
*/

char* removeJson(Profile profile){
    //Create JSON object
    JSONprofile JSONprofileCreate;
    JSONquery query;

    char *string = NULL;

    query.wrapper = cJSON_CreateObject();
    if (query.wrapper == NULL){
        goto end;
    }

    //OPERATION
    query.operation = cJSON_CreateString("REMOVE");
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

    //JSONfy to string
    string = cJSON_PrintUnformatted(query.wrapper);
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

/*
--------------------------
--------   LIST   --------
--------------------------
*/

/*
 * 
 * O parâmetro caracter pode ser:
 *      - a -> ListAll - listar todos os perfis
 *      - u -> ListUser - listar usuário expecífico
 *      - e -> ListEducation - listar usuários com certa experiência
 *      - s -> ListSkill - listar usuário com certa habilidade
 *      - y -> ListYear - listar usuáris com certo ano (Year) de conclusão
 * 
    */
char* listJson(char operation, char* string){
    //Create JSON object
    JSONprofile JSONprofileCreate;
    JSONquery query;

    char *retorno = NULL;
    char op[15], field[100];

    query.wrapper = cJSON_CreateObject();
    if (query.wrapper == NULL){
        goto end;
    }

    switch (operation)
    {
    case 'a':
        strcpy(op, "ListAll");
        strcpy(field, "none");
        break;

    case 'u':
        strcpy(op, "ListUser");
        strcpy(field, "email");
        break;

    case 'e':
        strcpy(op, "ListEducation");
        strcpy(field, "education");
        break;

    case 's':
        strcpy(op, "ListSkill");
        strcpy(field, "skill");
        break;

    case 'y':
        strcpy(op, "ListYear");
        strcpy(field, "graduationYear");
        break;

    
    default:
        printf("Erro\n");
        goto end;
        break;
    }

    //OPERATION
    query.operation = cJSON_CreateString(op);
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

    //Pode ser Qualquer coisa!! o que muda é o field
    JSONprofileCreate.email = cJSON_CreateString(string);
    if (JSONprofileCreate.email == NULL){
        goto end;
    }
    cJSON_AddItemToObject(query.object, field, JSONprofileCreate.email);

    //JSONfy to string
    retorno = cJSON_PrintUnformatted(query.wrapper);
    if (retorno == NULL)
    {
        fprintf(stderr, "Objeto JSON não pôde ser exibido.\n");
    }

    if(0){
        end:
        printf("Falha ao criar o objeto JSON.\n");
    }
    
    cJSON_Delete(query.wrapper);

    return retorno;
}

//{"response": "SUCCESS"/"FAILED", "object": {retorno}}
bool parseServerMessage(char* response, int len){

    const cJSON *operation = NULL;
    const cJSON *JSONobject = NULL;
    bool status = true;
    int i, n;
    cJSON *JSON = cJSON_Parse(response);

    if (JSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL){
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        status = false;
        goto end;
    }

    //obtendo a operação à ser executada
    operation = cJSON_GetObjectItemCaseSensitive(JSON, "response");
    /*if (cJSON_IsString(operation) && (operation->valuestring != NULL)){
        printf("Server response: \"%s\"\n", operation->valuestring);
    }*/

    JSONobject = cJSON_GetObjectItemCaseSensitive(JSON, "profiles");

    if(strcmp(operation->valuestring, "SUCCESS")==0){
        printf("\nRequisição processada pelo servidor com sucesso!\n");
        if ((JSONobject != NULL) && (cJSON_IsArray(JSONobject))){
            n = cJSON_GetArraySize(JSONobject);
            printf("Usuários!\n");
            for(i = 0; i < n; i++){
                printf("%s\n", cJSON_PrintUnformatted(cJSON_GetArrayItem(JSONobject, i)));
            }
        }
    }else if(strcmp(operation->valuestring, "FAILED")==0){
        printf("\nFalha no processamento do servidor! Por favor, tente novamente.\n");
        status = false;
    }else{
        printf("Parsing server message failed! Please try again\n");
        status = false;
    }

    end:
        return status;
}

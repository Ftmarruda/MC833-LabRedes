#include <stdlib.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool createProfile(char email[30], char name[30], char surname[30], char address[100], char education[100], char graduationYear[4]);
bool addExperience(char email[30], char professionalExperience[100]);
bool addSkill(char email[30], char skill[100]);
bool listProfilesBasedOnSkill(char skill[100]);
bool listProfilesBasedOnEducation(char education[100]);
bool listProfilesBasedOnGraduationYear(char graduationYear[4]);
bool listAllProfiles();
bool readProfile(char *email);
bool removeProfile(char *email);
int callback(void *, int, char **, char **);

int main(){

    createProfile("felipe@example.com", "Felipe", "Tiago", "Disneyland, Orlando", "Counter Strike University", "2022");
    createProfile("gabriel@example.com", "Gabriel", "Silveira", "Unicamp, Barão Geraldo", "Counter Strike University", "2022");

    addExperience("banana@example.com", "Trabalhei por dois anos na Conpec Corporation");
    addExperience("felipe@example.com", "Faço cerveja");
    addExperience("gabriel@example.com", "Sou coach");

    addSkill("felipe@example.com", "HTML");
    addSkill("felipe@example.com", "CSS");

    addSkill("gabriel@example.com", "HTML");
    addSkill("gabriel@example.com", "SQL");
    addSkill("gabriel@example.com", "JavaScript");

    addSkill("banana@example.com", "JavaScript");

    removeProfile("gabriel@example.com");

    //listAllProfiles();
    //readProfile("felipe@example.com");
    //listProfilesBasedOnGraduationYear("2022");
    //listProfilesBasedOnSkill("Botar o pé atrás da cabeça");
    //listProfilesBasedOnEducation("Counter Strike University");
    
    return 0;
}

//------------------------------
//------||   FUNÇÕES    ||------
//------------------------------

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
    strcpy(sql, "INSERT OR IGNORE INTO Profiles VALUES('");
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

bool addExperience(char email[30], char experience[100]){
    
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
    strcpy(sql, "INSERT OR IGNORE INTO Experiences VALUES(NULL, '");
    strcat(sql, email);
    strcat(sql, "', '");
    strcat(sql, experience);
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
    strcpy(sql, "INSERT OR IGNORE INTO Skills VALUES('");
    strcat(sql, skill);
    strcat(sql, "');");

    sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        free(sql);
        return false;
    }
    free(sql);

    //Query 2
    sql = malloc(200*sizeof(char));;
    strcpy(sql, "INSERT OR IGNORE INTO Profiles_Skills VALUES('");
    strcat(sql, email);
    strcat(sql, "', '");
    strcat(sql, skill);
    strcat(sql, "');");


    strcat(sql, "");

    sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        return false;
        free(sql);
    }
    free(sql);

    sqlite3_close(db);

    return true;
}

bool listProfilesBasedOnEducation(char education[100]){
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
    strcpy(sql, "SELECT * FROM Profiles WHERE Education == '");
    strcat(sql, education);
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

bool listProfilesBasedOnSkill(char skill[300]){
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
    strcpy(sql, "SELECT * FROM Profiles_Skills, Profiles WHERE Profiles_Skills.Profile_Email = Profiles.Email AND Skill_Description == '");
    strcat(sql, skill);
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

bool removeProfile(char *email){
    
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("app.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", 
                sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return false;
    }

    sqlite3_exec(db, "PRAGMA foreign_keys = ON", callback, 0, &err_msg);
    
    char sql[200];
    strcpy(sql, "DELETE FROM Profiles WHERE Email == '");
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
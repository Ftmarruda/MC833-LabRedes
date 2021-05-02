#include<sqlite3.h>
#include<stdio.h>

#define QUERY_MAX_SIZE 512

bool createProfile (Profile profile);
bool addExperience(char email[30], char professionalExperience[100]);
bool addSkill(char email[30], char skill[100]);
bool listProfilesBasedOnSkill(char skill[100]);
bool listProfilesBasedOnEducation(char education[100]);
bool listProfilesBasedOnGraduationYear(char graduationYear[4]);
bool listAllProfiles();
bool readProfile(char *email);
bool removeProfile(char *email);
int callback(void *, int, char **, char **);

/*
----------------------------
--------   CREATE   --------
----------------------------
*/

bool createProfile (Profile profile){
   
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("../server/app.db", &db); //caminho relativo à onde você executa o programa no terminal
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return false;
    }
    
    //Query
    char sql[QUERY_MAX_SIZE];
    strcpy(sql, "INSERT INTO Profiles VALUES('");
    strcat(sql, profile.email);
    strcat(sql, "', '");
    strcat(sql, profile.name);
    strcat(sql, "', '");
    strcat(sql, profile.surname);
    strcat(sql, "', '");
    strcat(sql, profile.address);
    strcat(sql, "', '");
    strcat(sql, profile.education);
    strcat(sql, "', '");
    strcat(sql, profile.graduationYear);
    strcat(sql, "');");

    printf("Query:\n%s\n", sql);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        return false;
    }
    
    sqlite3_close(db);

    return true;
}

/*
------------------------------------
--------   ADD EXPERIENCE   --------
------------------------------------
*/

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
    char sql[QUERY_MAX_SIZE];
    strcpy(sql, "INSERT INTO Experiences VALUES(NULL, '");
    strcat(sql, email);
    strcat(sql, "', '");
    strcat(sql, experience);
    strcat(sql, "');");

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        return false;
    }
    
    sqlite3_close(db);

    return true;
}

/*
-------------------------------
--------   ADD SKILL   --------
-------------------------------
*/

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

    sql = (char *) malloc(QUERY_MAX_SIZE*sizeof(char));
    strcpy(sql, "INSERT INTO Skills VALUES('");
    strcat(sql, skill);
    strcat(sql, "');");

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        free(sql);
        return false;
    }
    free(sql);

    //Query 2
    sql = (char *) malloc(QUERY_MAX_SIZE*sizeof(char));;
    strcpy(sql, "INSERT INTO Profiles_Skills VALUES('");
    strcat(sql, email);
    strcat(sql, "', '");
    strcat(sql, skill);
    strcat(sql, "');");


    strcat(sql, "");

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

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

/*
---------------------------------------------
--------   LIST BASED ON EDUCATION   --------
---------------------------------------------
*/

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
    
    char sql[QUERY_MAX_SIZE];
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

/*
-----------------------------------------
--------   LIST BASED ON SKILL   --------
-----------------------------------------
*/

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
    
    char sql[QUERY_MAX_SIZE];
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

/*
---------------------------------------------------
--------   LIST BASED ON GRADUATION YEAR   --------
---------------------------------------------------
*/

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
    
    char sql[QUERY_MAX_SIZE];
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

/*
---------------------------------------
--------   LIST ALL PROFILES   --------
---------------------------------------
*/

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

/*
----------------------------------
--------   LIST PROFILE   --------
----------------------------------
*/

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
    
    char sql[QUERY_MAX_SIZE];
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

/*
-------------------------------------
--------   REMOVE EDUCATION  --------
-------------------------------------
*/

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
    
    char sql[QUERY_MAX_SIZE];
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

/*
----------------------------------------
--------   AUXILIARY FUNCTIONS  --------
----------------------------------------
*/

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

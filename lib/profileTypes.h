typedef struct Profile {
    char email[31];
    char name[31];
    char surname[31];
    char address[101];
    char education[101];
    char graduationYear[5];
    const char *const *experience; //vetor de experiencias
    const char *const *skills; //vetor de skills
} Profile; 

typedef struct Query {
    char *operation;
    Profile profile;
} Query;

#define MAX_CARAC 100

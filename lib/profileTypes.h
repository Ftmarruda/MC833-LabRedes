

typedef struct Profile {
    char email[30];
    char name[30];
    char surname[30];
    char address[100];
    char education[100];
    char graduationYear[4];
    const char *const *experience; //vetor de experiencias
    const char *const *skills; //vetor de skills
} Profile; 

#define MAX_CARAC 100

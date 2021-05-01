

typedef struct Profile {
    char email[30];
    char name[30];
    char surname[30];
    char address[100];
    char education[100];
    char graduationYear[4];
    char **experience; //vetor de experiencias
    char **skills; //vetor de skills
} Profile; 
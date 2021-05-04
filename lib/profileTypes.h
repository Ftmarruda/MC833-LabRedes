

//Definição de constantes
#define MAX_Name 31
#define MAX_CARAC 140
#define MAX_LINE 5000
#define MAX_Year 5


typedef struct Profile {
    char email[31];
    char name[31];
    char surname[31];
    char address[MAX_CARAC];
    char education[MAX_CARAC];
    char graduationYear[MAX_Year];
    const char *const *experience; //vetor de experiencias
    const char *const *skills; //vetor de skills
} Profile; 

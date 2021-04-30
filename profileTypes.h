typedef struct Skill{
    char description[100];
} Skill;

typedef struct Experience{
    char description[100];
} Experience;

typedef struct Profile {
    char email[30];
    char name[30];
    char surname[30];
    char address[100];
    char education[100];
    char graduationYear[4];
    Experience *experience[100]; //vetor de experiencias
    Skill *skills[100]; //vetor de skills
} Profile;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#define MAX_LINES 140
#define MAX_LINE_LENGTH 100

typedef struct participant
{
    int position;
    char gender;
    int age;
    int positionInCategory;
    int dorsal;
    char *name;
    char sex;
    char *time;
    struct participant *next;
} Participant;

void printescalao(Participant *head, const char *escalao);
Participant *loadFileToList(const char *filename);
void printnome(Participant *head, const char *nome);
void freeList(Participant *head);
// declarações pretty fucking gay if u ask me

Participant *loadFileToList(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file %s\n", filename);
        return NULL;
    }

    char line[256];
    fgets(line, sizeof(line), file); // Ignore the first line

    Participant *head = NULL;
    Participant *tail = NULL;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        Participant *newParticipant = (Participant *)malloc(sizeof(Participant));
        if (newParticipant == NULL)
        {
            printf("Memory allocation failed\n");
            break;
        }

        char *token = strtok(line, "\t");
        newParticipant->position = atoi(token);

        token = strtok(NULL, "\t");
        newParticipant->gender = token[0];
        newParticipant->age = atoi(token + 1);

        token = strtok(NULL, "\t");
        newParticipant->positionInCategory = atoi(token);

        token = strtok(NULL, "\t");
        newParticipant->dorsal = atoi(token);

        token = strtok(NULL, "\t");
        newParticipant->name = strdup(token);

        token = strtok(NULL, "\t");
        newParticipant->sex = token[0];

        token = strtok(NULL, "\t");
        newParticipant->time = strdup(token);

        newParticipant->next = NULL;

        if (head == NULL)
        {
            head = newParticipant;
            tail = newParticipant;
        }
        else
        {
            tail->next = newParticipant;
            tail = newParticipant;
        }
    }

    fclose(file);
    return head;
}
void printescalao(Participant *head, const char *escalao)
{
    Participant *current = head;

    while (current != NULL)
    {
        // Convert age to string
        char ageStr[10];
        snprintf(ageStr, sizeof(ageStr), "%d", current->age);

        // Concatenate age with gender
        char genderAndAge[20];
        snprintf(genderAndAge, sizeof(genderAndAge), "%c%s", current->gender, ageStr);

        // Compare with escalao
        if (strcmp(genderAndAge, escalao) == 0)
        {
            // Create a new variable with the concatenated string
            char combined[20];
            snprintf(combined, sizeof(combined), "%d%s", current->gender, ageStr);

            printf("Position: %d\n", current->position);
            printf("Gender: %c%d\n", current->gender, current->age);
            printf("Position in Category: %d\n", current->positionInCategory);
            printf("Dorsal: %d\n", current->dorsal);
            printf("Name: %s\n", current->name);
            printf("Sex: %c\n", current->sex);
            printf("Time: %s\n", current->time);
            printf("--------------------\n");
        }

        current = current->next;
    }
    
}
void printnome(Participant *head, const char *nome)
{
    Participant *current = head;
    int nomeLength = strlen(nome);

    while (current != NULL)
    {
        // Compare with nome
        if (strncmp(current->name, nome, nomeLength) == 0)
        {
            // Print participant information
            printf("Position: %d\n", current->position);
            printf("Gender: %c%d\n", current->gender, current->age);
            printf("Position in Category: %d\n", current->positionInCategory);
            printf("Dorsal: %d\n", current->dorsal);
            printf("Name: %s\n", current->name);
            printf("Sex: %c\n", current->sex);
            printf("Time: %s\n", current->time);
            printf("--------------------\n");
        }

        current = current->next;
    }
}


void freeList(Participant *head)
{
    while (head != NULL)
    {
        Participant *current = head;
        head = head->next;
        free(current->name);
        free(current->time);
        free(current);
    }
}


int main(int argc, char *argv[])
{
    char *filename = "RunResults.txt";
    char *escalao = NULL;
    char *nome = NULL;
    int i = 0, e = 0, n = 0;
    int opt;
    while ((opt = getopt(argc, argv, "h:i:e:n:?")) != -1)
    {
        switch (opt)
        {
        case 'h':
            printf("-h mostra os parâmetros possíveis e as correspondentes funcionalidades\n");
            printf("-i ficheiro usar ficheiro de entrada “ficheiro” em vez de “RunResults.txt”, por omissão\n");
            printf("-e escalão pesquisar o “escalão”, mostrando a informação dos participantes desse escalão\n");
            printf("-n nome pesquisar o “nome” do participante.");
            exit(0);
            break; // não sei se oque esta por cima e a maneira mais correta parece kinda weird
        case 'i':
            i++;
            filename = strdup(optarg);
            printf("filename: %s\n", optarg);
            break;
        case 'e':
            e++;
            escalao = strdup(optarg);
            printf("Escalão selecionado: %s\n", optarg);
            break;
        case 'n':
            n++;
            nome = strdup(optarg);
            printf("Nome selecionado: %s\n", optarg);
            break;
        case '?':
            // Handle unknown option
            printf("Opção desconheciada pesquise -h para ver opções viaveis");
            exit(1);
            break;
        }
    }

    Participant *participants = loadFileToList(filename);

    if (e == 1)
    {
        printescalao(participants, escalao);
    }
    else if (n == 1)
    {
        printnome(participants, nome);
    
    }
    freeList(participants);

    return 0;
}
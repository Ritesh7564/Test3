/* stage2.c - ANSI C Mentor-Mentee Matching Program for Milliways */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRAINEES 20
#define MAX_MENTORS 8
#define NAME_LEN 30

/* Struct to store mentor information */
struct Mentor
{
    int id;
    char name[NAME_LEN];
    int matchedTraineeIndex;
};

/* Global trainee and mentor data */
char trainees[MAX_TRAINEES][NAME_LEN] = {
    "Jin", "Hana", "Minho", "Soo", "Luna", "Kai", "Yuna", "Dae", "Hyo", "Nari",
    "Leo", "Mina", "Taeyang", "Eunji", "Sun", "Bo", "Jae", "Ara", "Hyun", "Yeon"};

int traineeAsciiValues[MAX_TRAINEES];
int traineeAbilities[MAX_TRAINEES];

struct Mentor mentors[MAX_MENTORS];
int mentorCount = 0;

/* Parse nickname into integer using ASCII values */
int parseIntMember(char *nickname)
{
    int sum = 0;
    int i;

    for (i = 0; nickname[i] != '\0'; i++)
    {
        sum += (int)nickname[i];
    }

    return sum;
}

/* Generate random ability score between 100 and 1000 */
int getRandomAbility()
{
    return 100 + rand() % 901;
}

/* Initialize trainee data */
void initTrainees()
{
    int i;

    for (i = 0; i < MAX_TRAINEES; i++)
    {
        traineeAsciiValues[i] = parseIntMember(trainees[i]);
        traineeAbilities[i] = getRandomAbility();
    }
}

/* Input mentor names */
void inputMentors()
{
    int i;

    printf("\nEnter names for up to 8 mentors:\n");

    for (i = 0; i < MAX_MENTORS; i++)
    {
        printf("Mentor %d Name: ", i + 1);
        fgets(mentors[i].name, NAME_LEN, stdin);
        mentors[i].name[strcspn(mentors[i].name, "\n")] = '\0'; // remove newline
        mentors[i].id = i + 1;
        mentors[i].matchedTraineeIndex = -1; // not matched yet
        mentorCount++;
    }
}

/* Match trainees to mentors (bonus: ensure 1:1) */
void matchMentoring()
{
    int i;
    int usedMentors[MAX_MENTORS] = {0};

    printf("\nMatching mentors with trainees...\n");

    for (i = 0; i < MAX_TRAINEES && i < MAX_MENTORS; i++)
    {
        int traineeHash = traineeAsciiValues[i];
        int preferredMentor = traineeHash % MAX_MENTORS;

        // If preferred mentor already taken, find next available
        while (usedMentors[preferredMentor])
        {
            preferredMentor = (preferredMentor + 1) % MAX_MENTORS;
        }

        mentors[preferredMentor].matchedTraineeIndex = i;
        usedMentors[preferredMentor] = 1;
    }

    // Output results
    printf("\n=== Mentor-Mentee Pairs ===\n");

    for (i = 0; i < MAX_MENTORS; i++)
    {
        if (mentors[i].matchedTraineeIndex != -1)
        {
            int idx = mentors[i].matchedTraineeIndex;
            printf("Trainee No: %d (%s) → Mentor ID: %d (%s)\n",
                   idx + 1,
                   trainees[idx],
                   mentors[i].id,
                   mentors[i].name);
        }
        else
        {
            printf("Mentor ID: %d (%s) has no assigned trainee.\n",
                   mentors[i].id,
                   mentors[i].name);
        }
    }
}

/* Main menu entry for testing */
void menu()
{
    int choice;

    srand((unsigned int)time(NULL)); // seed for random

    initTrainees();

    while (1)
    {
        printf("\n== Milliways Training Menu ==\n");
        printf("1. Enter Mentors\n");
        printf("2. Match Mentoring\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice)
        {
        case 1:
            inputMentors();
            break;
        case 2:
            if (mentorCount == 0)
            {
                printf("Please enter mentors first.\n");
            }
            else
            {
                matchMentoring();
            }
            break;
        case 0:
            printf("Exiting...\n");
            return;
        default:
            printf("Invalid choice.\n");
        }
    }
}

int main()
{
    menu();
    return 0;
}

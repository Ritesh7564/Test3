/* stage2.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAX_MEMBERS 10
#define MAX_COUNSELING 50
#define MAX_RESPONSE_LEN 101
#define MAX_QUESTIONS 5

// === Struct Definitions ===
typedef struct {
    char nickname[50];
    int age;
    char trauma[200];
} TraumaInfo;

typedef struct {
    int id;
    char content[200];
} CounselingQuestion;

typedef struct {
    char nickname[50];
    char question[200];
    char response[MAX_RESPONSE_LEN];
} CounselingResponse;

// === Global Data ===
TraumaInfo traumaList[MAX_MEMBERS];
int traumaCount = 0;

CounselingResponse counselingLog[MAX_COUNSELING];
int counselingCount = 0;

const CounselingQuestion questionBank[MAX_QUESTIONS] = {
    {1, "In what situations have you experienced this trauma?"},
    {2, "How has this situation affected your daily life and emotions?"},
    {3, "How have you tried to overcome this trauma?"},
    {4, "What emotions do you associate with this trauma?"},
    {5, "What kind of support do you think is necessary to overcome this trauma?"}
};

// Dummy member data from Assignment 1
const char *members[MAX_MEMBERS] = {"Luna", "Kai", "Mira", "Juno", "Zion", "Rhea", "Leo", "Nova", "Orion", "Skye"};
const int ages[MAX_MEMBERS] = {19, 20, 21, 22, 23, 24, 25, 26, 27, 28};

// === Helper Functions ===
int findMemberIndex(const char *nickname) {
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(members[i], nickname) == 0) return i;
    }
    return -1;
}

int traumaExists(const char *nickname) {
    for (int i = 0; i < traumaCount; i++) {
        if (strcmp(traumaList[i].nickname, nickname) == 0) return i;
    }
    return -1;
}

void enterTrauma() {
    char nickname[50];
    char trauma[200];

    while (1) {
        printf("\nEnter nickname (or type 'exit' to return): ");
        scanf("%s", nickname);
        if (strcmp(nickname, "exit") == 0) break;

        int idx = findMemberIndex(nickname);
        idx >= 0
            ? ({
                printf("Enter trauma description: ");
                getchar();
                fgets(trauma, sizeof(trauma), stdin);
                trauma[strcspn(trauma, "\n")] = 0;

                int tIdx = traumaExists(nickname);
                if (tIdx >= 0) {
                    strcpy(traumaList[tIdx].trauma, trauma);
                } else {
                    strcpy(traumaList[traumaCount].nickname, nickname);
                    traumaList[traumaCount].age = ages[idx];
                    strcpy(traumaList[traumaCount].trauma, trauma);
                    traumaCount++;
                }
                printf("Trauma recorded successfully for %s.\n", nickname);
            })
            : printf("Nickname not found. Try again.\n");
    }
}

void startCounseling() {
    if (traumaCount == 0) {
        printf("No members have trauma data.\n");
        return;
    }

    printf("\nMembers with trauma entries:\n");
    for (int i = 0; i < traumaCount; i++) {
        printf("- %s\n", traumaList[i].nickname);
    }

    char nickname[50];
    printf("Enter nickname to begin counseling: ");
    scanf("%s", nickname);

    int idx = traumaExists(nickname);
    if (idx < 0) {
        printf("Nickname not found in trauma list.\n");
        return;
    }

    int asked[3] = {-1, -1, -1};
    srand(time(NULL));
    for (int i = 0; i < 3; i++) {
        int q;
        do {
            q = rand() % MAX_QUESTIONS;
        } while (q == asked[0] || q == asked[1]);
        asked[i] = q;

        printf("\nQ%d: %s\n", i + 1, questionBank[q].content);
        printf("Your answer (max 100 chars): ");
        getchar();
        char response[MAX_RESPONSE_LEN];
        fgets(response, MAX_RESPONSE_LEN, stdin);
        response[strcspn(response, "\n")] = 0;

        while (strlen(response) == 0 || strlen(response) > 100) {
            printf("Invalid input. Please re-enter: ");
            fgets(response, MAX_RESPONSE_LEN, stdin);
            response[strcspn(response, "\n")] = 0;
        }

        strcpy(counselingLog[counselingCount].nickname, nickname);
        strcpy(counselingLog[counselingCount].question, questionBank[q].content);
        strcpy(counselingLog[counselingCount].response, response);
        counselingCount++;
    }
    printf("\nCounseling session for %s completed.\n", nickname);
}

void viewCounselingSummary() {
    printf("\nCounseling Summaries:\n");
    for (int i = 0; i < traumaCount; i++) {
        char *name = traumaList[i].nickname;
        printf("\n--- %s ---\nAge: %d\nTrauma: %s\nResponses:\n",
               name, traumaList[i].age, traumaList[i].trauma);
        for (int j = 0; j < counselingCount; j++) {
            if (strcmp(counselingLog[j].nickname, name) == 0) {
                printf("Q: %s\nA: %s\n", counselingLog[j].question, counselingLog[j].response);
            }
        }
    }
}

void overcomeTrauma() {
    char choice;
    while (1) {
        printf("\n--- Trauma Management ---\n");
        printf("A. Enter Trauma Info\n");
        printf("B. Start Counseling Session\n");
        printf("C. View Counseling Summary\n");
        printf("Q. Return to Main Menu\n");
        printf("Select an option: ");
        scanf(" %c", &choice);
        choice = tolower(choice);

        switch (choice) {
            case 'a': enterTrauma(); break;
            case 'b': startCounseling(); break;
            case 'c': viewCounselingSummary(); break;
            case 'q': return;
            default: printf("Invalid option.\n");
        }
    }
}

// Main menu for demonstration
int main() {
    while (1) {
        char choice;
        printf("\n=== MAIN MENU ===\n");
        printf("1. Overcome Trauma\n");
        printf("Q. Quit\n");
        printf("Select: ");
        scanf(" %c", &choice);
        if (tolower(choice) == 'q') break;
        else if (choice == '1') overcomeTrauma();
        else printf("Invalid option.\n");
    }
    return 0;
}

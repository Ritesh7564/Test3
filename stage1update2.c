/* stage1.c - Updated for Fitness and Workout Routine Management in Milliways Training Program */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMBERS 6
#define MAX_NAME_LEN 50
#define MAX_NICKNAME_LEN 20
#define TESTS 7
#define DAYS 6

// Member data
char milliways_members[MAX_MEMBERS][MAX_NAME_LEN] = {
    "Jiyeon Park",
    "Ethan Smith",
    "Suphanan Wong",
    "Helena Silva",
    "Karolina Nowak",
    "Liam Wilson"
};

char milliways_nicknames[MAX_MEMBERS][MAX_NICKNAME_LEN] = {
    "Jiyeon",
    "Ethan",
    "Suphanan",
    "Helena",
    "Karolina",
    "Liam"
};

// Fitness categories
char *fitness_tests[TESTS] = {
    "1-Mile Run (min)",
    "100m Sprint (sec)",
    "30 Push-ups (min)",
    "50 Squats (min)",
    "50 Push-ups (min)",
    "400m Swim (min)",
    "Bench Press (x Bodyweight)"
};

// 2D array for fitness scores
float health_scores[MAX_MEMBERS][TESTS];

// Workout routine types
char *exercise_types[5][3] = {
    {"Running", "Cycling", "Fast Walking"},          // Cardio
    {"Push-ups", "Squats", ""},                     // Full-body Strength
    {"Leg Press", "Leg Curl", ""},                  // Lower-body Strength
    {"Pull-ups", "Chin-ups", ""},                   // Upper-body Strength
    {"Plank", "Crunches", ""}                        // Core Strength
};

char member_routine[MAX_MEMBERS][DAYS][2][30]; // [member][day][0:cardio,1:strength/core]

void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Display member list
void displayMemberList() {
    printf("\nAvailable Members:\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("- %s (%s)\n", milliways_members[i], milliways_nicknames[i]);
    }
}

// Parse comma-separated input values into float array
void parse_fitness_data(char *input, float *scores) {
    char *token = strtok(input, ",");
    int i = 0;
    while (token != NULL && i < TESTS) {
        scores[i] = atof(token);
        token = strtok(NULL, ",");
        i++;
    }
    if (i != TESTS) {
        printf("Invalid number of inputs. Please enter %d values.\n", TESTS);
    }
}

void setHealth() {
    printf("\n[II. Training > 1. Physical Strength & Knowledge > A. Enter Fitness Data]\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("Enter fitness data for %s (%s):\n", milliways_members[i], milliways_nicknames[i]);
        printf("Format: 1-Mile,100m Sprint,Pushups,Squats,Arm Strength,Swimming,Weightlifting\n");

        char input[200];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        parse_fitness_data(input, health_scores[i]);
    }
    printf("\nAll fitness data has been recorded.\n");
}

void getHealth() {
    char choice;
    printf("\n[II. Training > 1. Physical Strength & Knowledge > B. View Fitness Data]\n");
    printf("Choose option:\n");
    printf("1. View all members' data\n");
    printf("2. View one member's full data\n");
    printf("3. View one test result for a member\n");
    printf("Select: ");
    choice = getchar();
    clear_input();

    if (choice == '1') {
        for (int i = 0; i < MAX_MEMBERS; i++) {
            printf("\nMember: %s (%s)\n", milliways_members[i], milliways_nicknames[i]);
            for (int j = 0; j < TESTS; j++) {
                printf("%s: %.2f\n", fitness_tests[j], health_scores[i][j]);
            }
        }
    } else if (choice == '2') {
        char nickname[MAX_NICKNAME_LEN];
        printf("Enter nickname: ");
        fgets(nickname, sizeof(nickname), stdin);
        nickname[strcspn(nickname, "\n")] = 0;

        int found = -1;
        for (int i = 0; i < MAX_MEMBERS; i++) {
            if (strcmp(nickname, milliways_nicknames[i]) == 0) {
                found = i;
                break;
            }
        }
        if (found != -1) {
            printf("\nMember: %s (%s)\n", milliways_members[found], milliways_nicknames[found]);
            for (int j = 0; j < TESTS; j++) {
                printf("%s: %.2f\n", fitness_tests[j], health_scores[found][j]);
            }
        } else {
            printf("Nickname not found.\n");
        }
    } else if (choice == '3') {
        char nickname[MAX_NICKNAME_LEN];
        int testIndex;
        printf("Enter nickname: ");
        fgets(nickname, sizeof(nickname), stdin);
        nickname[strcspn(nickname, "\n")] = 0;

        printf("Select fitness test (1-7):\n");
        for (int i = 0; i < TESTS; i++) {
            printf("%d. %s\n", i + 1, fitness_tests[i]);
        }
        printf("Enter number: ");
        scanf("%d", &testIndex);
        clear_input();

        if (testIndex < 1 || testIndex > TESTS) {
            printf("Invalid test number.\n");
            return;
        }

        int found = -1;
        for (int i = 0; i < MAX_MEMBERS; i++) {
            if (strcmp(nickname, milliways_nicknames[i]) == 0) {
                found = i;
                break;
            }
        }
        if (found != -1) {
            printf("%s (%s) - %s: %.2f\n",
                   milliways_members[found], nickname,
                   fitness_tests[testIndex - 1],
                   health_scores[found][testIndex - 1]);
        } else {
            printf("Nickname not found.\n");
        }
    } else {
        printf("Invalid selection.\n");
    }
}

void setExerciseRoutine() {
    printf("\n[II. Training > 1. Physical Strength & Knowledge > C. Set Basic Workout Routine]\n");
    displayMemberList();

    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("\nSetting routine for %s (%s):\n", milliways_members[i], milliways_nicknames[i]);
        int core_count = 0;
        for (int day = 0; day < DAYS; day++) {
            printf("Day %d (Mon=1 ~ Sat=6):\n", day + 1);
            printf("Select Cardio (0: Running, 1: Cycling, 2: Fast Walking): ");
            int cidx; scanf("%d", &cidx); clear_input();
            strcpy(member_routine[i][day][0], exercise_types[0][cidx]);

            printf("Select Strength/Core (1: Full-body, 2: Lower-body, 3: Upper-body, 4: Core): ");
            int type; scanf("%d", &type); clear_input();
            if (type == 4 && core_count >= 1) {
                printf("Core exercise already used once. Pick another type.\n");
                day--; continue;
            }
            core_count += (type == 4);

            printf("Select Exercise (0 or 1): ");
            int sidx; scanf("%d", &sidx); clear_input();
            strcpy(member_routine[i][day][1], exercise_types[type][sidx]);
        }
    }
    printf("\nAll routines set.\n");
}

void getExerciseRoutine() {
    printf("\n[II. Training > 1. Physical Strength & Knowledge > D. View Basic Workout Routine]\n");
    displayMemberList();

    char name[MAX_NAME_LEN];
    printf("Enter full member name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    int found = -1;
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(name, milliways_members[i]) == 0) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        printf("\nWorkout Routine for %s (%s):\n", milliways_members[found], milliways_nicknames[found]);
        for (int d = 0; d < DAYS; d++) {
            printf("Day %d - Cardio: %s, Strength/Core: %s\n",
                   d + 1,
                   member_routine[found][d][0],
                   member_routine[found][d][1]);
        }
    } else {
        printf("Member not found.\n");
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n[Main Menu]\n");
        printf("1. Enter Fitness Data\n");
        printf("2. View Fitness Data\n");
        printf("3. Set Workout Routine\n");
        printf("4. View Workout Routine\n");
        printf("0. Exit\n");
        printf("Select option: ");
        scanf("%d", &choice);
        clear_input();

        if (choice == 0) break;
        else if (choice == 1) setHealth();
        else if (choice == 2) getHealth();
        else if (choice == 3) setExerciseRoutine();
        else if (choice == 4) getExerciseRoutine();
        else printf("Invalid choice.\n");
    }
    return 0;
}

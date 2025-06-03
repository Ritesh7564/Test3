#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CANDIDATES 6
#define NUM_JUDGES 1  // Can be extended for multiple judges

// Candidate structure
char *candidate_names[NUM_CANDIDATES] = {
    "Jiyeon Park",
    "Ethan Smith",
    "Helena Silva",
    "Liam Wilson",
    "Mina Choi",
    "Daniel Lee"
};

int candidate_ids[NUM_CANDIDATES] = {101234, 102345, 103456, 104567, 105678, 106789};

// scoring_sheet[NUM_CANDIDATES][7] structure:
// [0] = Candidate ID, [1~5] = Scores, [6] = Total Score
int scoring_sheet[NUM_CANDIDATES][7];

// Function prototypes
int input_valid_score(const char *prompt);
void review_input();
void modify_scores();
void compute_top_4();

int main() {
    char judge_name[100], expertise[100];
    char choice;
    int i;

start:
    printf("####################################\n");
    printf("#     Audition Evaluation Entry    #\n");
    printf("####################################\n");

    printf("> Judge Name: ");
    fgets(judge_name, sizeof(judge_name), stdin);
    judge_name[strcspn(judge_name, "\n")] = 0;

    printf("> Expertise: ");
    fgets(expertise, sizeof(expertise), stdin);
    expertise[strcspn(expertise, "\n")] = 0;

    printf("++++++++++++++++++++++++++++++++++++\n");

    // Score entry
    for (i = 0; i < NUM_CANDIDATES; i++) {
        printf("Candidate: %s\n", candidate_names[i]);
        scoring_sheet[i][0] = candidate_ids[i];

        scoring_sheet[i][1] = input_valid_score("Music Proficiency");
        scoring_sheet[i][2] = input_valid_score("Dance");
        scoring_sheet[i][3] = input_valid_score("Vocal");
        scoring_sheet[i][4] = input_valid_score("Visual");
        scoring_sheet[i][5] = input_valid_score("Expression");

        // Calculate total
        scoring_sheet[i][6] = scoring_sheet[i][1] + scoring_sheet[i][2] +
                              scoring_sheet[i][3] + scoring_sheet[i][4] +
                              scoring_sheet[i][5];

        printf("------------------------------------\n");
    }

    review_input();

    printf("Would you like to submit? (Y/N): ");
    scanf(" %c", &choice);
    getchar(); // consume newline

    if (choice == 'N' || choice == 'n') {
        modify_scores();
        goto start;
    }

    printf("***Final submission completed.***\n");
    compute_top_4();

    return 0;
}

int input_valid_score(const char *prompt) {
    int score;
    while (1) {
        printf("%s (10-100): ", prompt);
        if (scanf("%d", &score) != 1 || score < 10 || score > 100) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n'); // flush input
        } else {
            return score;
        }
    }
}

void review_input() {
    int i;
    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Submission completed.\nPlease review your input!\n");
    printf("------------------------------------\n");
    for (i = 0; i < NUM_CANDIDATES; i++) {
        printf("%s: %d\n", candidate_names[i], scoring_sheet[i][6]);
    }
}

void modify_scores() {
    char name[100];
    int id, found, i;

    while (1) {
        printf("Enter candidate's name to modify (or 'exit' to stop): ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;

        if (strcmp(name, "exit") == 0) break;

        printf("Enter 6-digit candidate ID: ");
        scanf("%d", &id);
        getchar(); // consume newline

        found = 0;
        for (i = 0; i < NUM_CANDIDATES; i++) {
            if (strcmp(name, candidate_names[i]) == 0 && id == candidate_ids[i]) {
                printf("Modifying %s\n", name);
                scoring_sheet[i][1] = input_valid_score("Music Proficiency");
                scoring_sheet[i][2] = input_valid_score("Dance");
                scoring_sheet[i][3] = input_valid_score("Vocal");
                scoring_sheet[i][4] = input_valid_score("Visual");
                scoring_sheet[i][5] = input_valid_score("Expression");
                scoring_sheet[i][6] = scoring_sheet[i][1] + scoring_sheet[i][2] +
                                      scoring_sheet[i][3] + scoring_sheet[i][4] +
                                      scoring_sheet[i][5];
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Candidate not found. Please check the name and ID.\n");
        }
    }
}

void compute_top_4() {
    int i, j;
    int sorted_idx[NUM_CANDIDATES];
    for (i = 0; i < NUM_CANDIDATES; i++) {
        sorted_idx[i] = i;
    }

    // Simple bubble sort by total score descending
    for (i = 0; i < NUM_CANDIDATES - 1; i++) {
        for (j = 0; j < NUM_CANDIDATES - i - 1; j++) {
            if (scoring_sheet[sorted_idx[j]][6] < scoring_sheet[sorted_idx[j + 1]][6]) {
                int temp = sorted_idx[j];
                sorted_idx[j] = sorted_idx[j + 1];
                sorted_idx[j + 1] = temp;
            }
        }
    }

    printf("=======================================\n");
    printf("Compiling final selection results...\n");
    printf("=======================================\n");
    printf("###########################################\n");
    printf("# Congratulations! Welcome to Milliways!  #\n");
    printf("###########################################\n");
    for (i = 0; i < 4; i++) {
        printf("%d. %s\n", i + 1, candidate_names[sorted_idx[i]]);
    }
}

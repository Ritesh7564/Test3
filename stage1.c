#include <stdio.h>
#include <string.h>

#define TOTAL_STAGES 8

const char *main_menu[] = {
    "I. Audition Management",
    "II. Training",
    "III. Debut"
};

const char *training_menu[] = {
    "1. Physical Strength & Knowledge",
    "2. Self-Management & Teamwork",
    "3. Language & Pronunciation",
    "4. Vocal",
    "5. Dance",
    "6. Visual & Image",
    "7. Acting & Stage Performance",
    "8. Fan Communication"
};

char training_result[TOTAL_STAGES] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };

void print_main_menu(void)
{
    int i;
    printf("\n=== Main Menu ===\n");
    for (i = 0; i < 3; i++)
        printf("%d. %s\n", i + 1, main_menu[i]);
    printf("Enter your choice (or Q to quit): ");
}

void print_training_menu(void)
{
    int i;
    printf("\n--- Training Menu ---\n");
    for (i = 0; i < TOTAL_STAGES; i++)
    {
        printf("%d. %s", i + 1, training_menu[i]);
        if (training_result[i] == 'P')
            printf(" [Passed]");
        else if (training_result[i] == 'F')
            printf(" [Failed]");
        printf("\n");
    }
    printf("Enter your training stage (or Q to go back): ");
}

void handle_training(void)
{
    char input[10];
    int stage;
    while (1)
    {
        print_training_menu();
        fgets(input, sizeof(input), stdin);
        if (input[0] == '\n' || input[0] == 'q' || input[0] == 'Q' || input[0] == '0')
            break;

        stage = input[0] - '0';
        if (stage < 1 || stage > 8)
        {
            printf("Invalid stage. Try again.\n");
            continue;
        }

        if (training_result[stage - 1] == 'P')
        {
            printf("Stage already passed. Cannot retake.\n");
            continue;
        }

        if ((stage == 2 && training_result[0] != 'P') ||
            (stage >= 3 && (training_result[0] != 'P' || training_result[1] != 'P')))
        {
            printf("You must pass the previous required stages before accessing this one.\n");
            continue;
        }

        printf("Would you like to enter the evaluation result? (Y/N): ");
        fgets(input, sizeof(input), stdin);
        if (input[0] == 'Y' || input[0] == 'y')
        {
            printf("Did you complete the training and pass the certification? (P/F): ");
            fgets(input, sizeof(input), stdin);
            if (input[0] == 'P' || input[0] == 'p')
                training_result[stage - 1] = 'P';
            else
                training_result[stage - 1] = 'F';
        }
        else
        {
            continue;
        }
    }
}

void handle_audition(void)
{
    printf("\n[Audition Management Module Placeholder]\n");
}

void handle_debut(void)
{
    printf("\n[Debut Module Placeholder]\n");
}

int main(void)
{
    char input[10];
    int choice;

    while (1)
    {
        print_main_menu();
        fgets(input, sizeof(input), stdin);
        if (input[0] == '\n' || input[0] == 'q' || input[0] == 'Q' || input[0] == '0')
        {
            printf("Exiting program.\n");
            break;
        }

        choice = input[0] - '0';

        switch (choice)
        {
            case 1:
                handle_audition();
                break;
            case 2:
                handle_training();
                break;
            case 3:
                handle_debut();
                break;
            default:
                printf("Invalid option. Try again.\n");
        }
    }

    return 0;
}

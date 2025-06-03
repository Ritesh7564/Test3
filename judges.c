#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JUDGES 100
#define MAX_LENGTH 500

char judges_array[MAX_JUDGES][MAX_LENGTH];

int count_commas(const char *str) {
    int count = 0; 
    while (*str) {
        if (*str == ',') count++;
        str++;
    }
    return count;
}

void parse_and_display(const char *data, int index) {
    char temp[MAX_LENGTH];
    strcpy(temp, data);

    char *token = strtok(temp, ",");
    const char *labels[] = {
        "Name", "Gender", "Affiliation", "Title", "Expertise", "Email", "Phone"
    };

    printf("[Judge %d]\n", index + 1);

    int i = 0;
    while (token != NULL && i < 7) {
        while (*token == ' ') token++;
        printf("%s: %s\n", labels[i], token);
        token = strtok(NULL, ",");
        i++;
    }

    printf("-----------------------------------\n");
}

int main() {
    char project[100];
    int total_judges, selected_members;

    printf("####################################\n");
    printf("#      Judge List Data Entry      #\n");
    printf("####################################\n");

    printf("Participating Project: ");
    fgets(project, sizeof(project), stdin);
    project[strcspn(project, "\n")] = 0; 

    printf("Total Number of Judges: ");
    scanf("%d", &total_judges);

    printf("Number of Selected Members: ");
    scanf("%d", &selected_members);
    getchar();

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Starting to input information for %d judges.\n", total_judges);
    printf("++++++++++++++++++++++++++++++++++++\n");

    int i = 0;
    while (i < total_judges) {
        printf("Judge %d: ", i + 1);
        fgets(judges_array[i], MAX_LENGTH, stdin);
        judges_array[i][strcspn(judges_array[i], "\n")] = 0; 

        if (count_commas(judges_array[i]) != 6) {
            printf("The input items are incorrect. Please enter them again.\n");
            continue;
        }

        i++;
    }

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Judge information entry is complete.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");

    printf("\"Should we check the judge information?\" ");
    char confirm;
    scanf(" %c", &confirm); 
    if (confirm == 'Y') {
        printf("####################################\n");
        printf("#        Display Judge Data        #\n");
        printf("####################################\n");

        for (i = 0; i < total_judges; i++) {
            parse_and_display(judges_array[i], i);
        }
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define CANDIDATE_COUNT 6

char *candidate01[11];
char *candidate02[11];
char *candidate03[11];
char *candidate04[11];
char *candidate05[11];
char *candidate06[11];

char **candidates[] = {
    candidate01, candidate02, candidate03, candidate04, candidate05, candidate06
};

char *member_info[] = {
    "Name", "DOB", "Gender", "Email", "Nationality", "BMI",
    "Primary Skill", "Secondary Skill", "TOPIK", "MBTI", "Introduction"
};

int calculate_age(const char *dob) {
    int birth_year, birth_month, birth_day;
    sscanf(dob, "%4d%2d%2d", &birth_year, &birth_month, &birth_day);
    int current_year = 2025, current_month = 5, current_day = 6;

    int age = current_year - birth_year;
    if (birth_month > current_month || (birth_month == current_month && birth_day > current_day))
        age--;

    return age;
}

int main() {
    char group_name[50];
    int i;

    printf("Enter audition group name: ");
    i = 0;
    char ch;
    while ((ch = getchar()) != '\n' && i < 49) {
        group_name[i++] = ch;
    }
    group_name[i] = '\0';

    printf("\n####################################\n");
    printf("    [%s] Audition Candidate Data Entry\n", group_name);
    printf("####################################\n");

    int count = 0;
    while (count < CANDIDATE_COUNT) {
        printf("Entering information for candidate %d.\n", count + 1);
        printf("---------------------------------\n");

        for (i = 0; i < 11; i++) {
            static char buffer[6][11][200]; 
            printf("%d. %s: ", i + 1, member_info[i]);
            fgets(buffer[count][i], sizeof(buffer[count][i]), stdin);

            int len = 0;
            while (buffer[count][i][len] != '\0') {
                if (buffer[count][i][len] == '\n') {
                    buffer[count][i][len] = '\0';
                    break;
                }
                len++;
            }

            candidates[count][i] = buffer[count][i];
        }

        printf("=================================\n");
        count++;
    }

    printf("\n####################################\n");
    printf("    [%s] Audition Candidate Data Review\n", group_name);
    printf("####################################\n");
    printf("=============================================================================================\n");
    printf("Name (Age)        | DOB       | Gender | Email               | Nationality | BMI  | Primary | Secondary | TOPIK   | MBTI  |\n");
    printf("=============================================================================================\n");

    for (i = 0; i < CANDIDATE_COUNT; i++) {
        char *dob = candidates[i][1];
        char dob_noslash[9];
        sscanf(dob, "%4c%*c%2c%*c%2c", &dob_noslash[0], &dob_noslash[4], &dob_noslash[6]);
        dob_noslash[4] = dob[5];
        dob_noslash[6] = dob[8];
        dob_noslash[8] = '\0';

        int age = calculate_age(dob_noslash);
        char *topik = candidates[i][8];

        printf("%-15s (%d) | %-8s | %-6s | %-20s | %-12s | %-4s | %-7s | %-9s | %-7s | %-5s |\n",
            candidates[i][0], age, dob_noslash, candidates[i][2], candidates[i][3], candidates[i][4],
            candidates[i][5], candidates[i][6], candidates[i][7],
            (topik[0] == '0') ? "Native" : topik, candidates[i][9]);

        printf("---------------------------------------------------------------------------------------------\n");
        printf("%s\n", candidates[i][10]);
        printf("---------------------------------------------------------------------------------------------\n");
    }

    return 0;
}

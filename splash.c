#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for sleep()

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printTriangleLeft(int height) {
    for (int i = 1; i <= height; ++i) {
        for (int j = 1; j <= i; ++j)
            printf("*");
        printf("\n");
    }
}

void printTriangleRight(int height) {
    for (int i = 1; i <= height; ++i) {
        for (int j = 1; j <= height - i; ++j)
            printf(" ");
        for (int k = 1; k <= i; ++k)
            printf("*");
        printf("\n");
    }
}

int main() {
    char date[11]; // yyyy-mm-dd + null
    char name[100];

    printf("[Please enter the current date in the \"yyyy-mm-dd\" format]: ");
    fgets(date, sizeof(date), stdin);
    date[strcspn(date, "\n")] = '\0'; // remove newline

    printf("[Please enter your name]: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // remove newline

    printf("**The input has been processed successfully.**\n");

    sleep(3);
    clearScreen();

    // Print left triangle
    printTriangleLeft(5);

    // Splash Screen
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("                            [Magrathea ver 0.1]                              \n");
    printf("Magrathea, where a shining planet is created in a wasteland with no grass,\n");
    printf("where unseen potential is discovered and gems are polished by the hands of experts,\n");
    printf("                             Welcome to Magrathea.\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("                            [Execution Time]: %s\n", date);
    printf("==============================================================================\n");

    // Print right triangle
    printTriangleRight(5);

    return 0;
}

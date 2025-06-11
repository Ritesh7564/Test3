/*
 * arthur_easter_egg.c - Implements Arthur's hidden trauma Easter Egg.
 * GNU Coding Standards & ANSI C compliant.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_INPUT 100

/* Arthur's Easter Egg Trauma Struct */
typedef struct {
  char keyword[8];
  char message[300];
} ArthurEasterEgg;

/* Function Prototypes */
void find_easter_egg();
int isRightChar(const char *input_chars, const char *reversed_binary);
int isEasterEgg(const char *word);
void to_binary(unsigned char ch, char *output);
void shuffle_and_convert(const char *keyword);

/* Easter Egg Data */
ArthurEasterEgg arthur = {
  "specter",
  "I confess. After graduating from university, I was blinded by the arrogance of starting a startup and recklessly blocked my friends' paths. I painfully learned that when I am the only one convinced by my idea, it leads to disastrous results. The past Arthur was a ghost of dogmatism and stubbornness."
};

void to_binary(unsigned char ch, char *output) {
  for (int i = 7; i >= 0; i--)
    output[7 - i] = (ch & (1 << i)) ? '1' : '0';
  output[8] = '\0';
}

void find_easter_egg() {
  printf("<<Arthur's Easter Egg>>\n");

  char reversed_binary[8][9];
  for (int i = 6; i >= 0; i--) {
    to_binary(arthur.keyword[i], reversed_binary[6 - i]);
  }

  printf("Enter the characters for these reversed binary values:\n");
  for (int i = 0; i < 7; i++) {
    printf("%s\n", reversed_binary[i]);
  }

  char input_chars[8];
  printf("Enter 7 characters in order: ");
  scanf("%7s", input_chars);

  if (isRightChar(input_chars, (const char *)reversed_binary)) {
    char word[8];
    printf("Now combine and enter the full word: ");
    scanf("%7s", word);
    if (isEasterEgg(word)) {
      printf("\n##Easter Egg Discovered!$$\n");
      printf("%s\n", arthur.message);
    } else {
      printf("Incorrect keyword. Returning to menu.\n");
    }
  } else {
    printf("Incorrect characters. Returning to menu.\n");
  }
}

int isRightChar(const char *input_chars, const char *reversed_binary) {
  for (int i = 0; i < 7; i++) {
    char temp_bin[9];
    to_binary(input_chars[i], temp_bin);
    if (strcmp(temp_bin, ((char (*)[9])reversed_binary)[i]) != 0)
      return 0;
  }
  return 1;
}

int isEasterEgg(const char *word) {
  return strcmp(word, arthur.keyword) == 0;
}

void shuffle_and_convert(const char *keyword) {
  char reversed[8];
  int len = strlen(keyword);

  for (int i = 0; i < len; i++) {
    reversed[i] = keyword[len - 1 - i];
  }
  reversed[len] = '\0';

  char odd[8] = "", even[8] = "";
  int o = 0, e = 0;
  for (int i = 0; i < len; i++) {
    if (i % 2 == 1)
      odd[o++] = reversed[i];
    else
      even[e++] = reversed[i];
  }
  odd[o] = '\0';
  even[e] = '\0';

  strcat(odd, even);
  printf("Shuffled and converted binary values:\n");
  for (int i = 0; i < len; i++) {
    char bin[9];
    to_binary(odd[i], bin);
    printf("%s\n", bin);
  }
}

/* Example Hook Function */
void self_management_teamwork_menu() {
  char input[50];
  printf("Enter your name (or Arthur to unlock Easter Egg): ");
  scanf("%s", input);
  if (strcmp(input, "Arthur") == 0)
    find_easter_egg();
  else
    printf("Welcome, %s.\n", input);
}

/* Entry Point */
int main() {
  self_management_teamwork_menu();
  // Uncomment to test bonus:
  // shuffle_and_convert(arthur.keyword);
  return 0;
}

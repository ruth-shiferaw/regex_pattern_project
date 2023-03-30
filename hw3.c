//Ruth Shiferaw
//JHED ID: RSHIFER1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

#define MAX_WORD_NUM 1024
#define MAX_INPUT_SIZE 128
#define DEFAULT_RESTRICTION 10

int main(int argc, const char *argv[]) {
  char words[ MAX_WORD_NUM ][ MAX_WORD_SIZE + 1 ]; 
  char user_regex[128];
  int file_words = 0;
  int restrict_value = 10;
  int match_avail = 0; //for printing error message for no matches

  if (argc == 3) {
    if (argv[2] != NULL) {
      restrict_value = atoi(argv[2]);
    }
  }

  if (restrict_value < 1) {
    fprintf(stderr, "Error: invalid restriction value entered.\n");
    return 3;
  }

  FILE *input = fopen(argv[1], "r"); //if fails, will equal NULL
  if (input == NULL) {
    fprintf(stderr, "Error: Could not open input file.\n");
    return 1;
  } 

  //finding the amount of words defined in the file
  fscanf(input, "%d", &file_words);
  if (file_words < 1) {
    fprintf(stderr, "Error: input file contains an invalid number of words.\n");
    return 1;
  }
  
  //calling read_file, will exit if invalid # of words
  if (read_file(input, words, file_words) == 2) {
    fprintf(stderr, "Error: input file has invalid number of words.\n");
    return 1;
  }
 
  while (scanf(" %s", user_regex) == 1) { 
    for (int i = 0; i < file_words; i++) {
      if ((match(user_regex, words[i], restrict_value)) == 1) {
        printf("%s\n", words[i]);
        match_avail = 1;
      }
    }
    if (match_avail == 0) {
        printf("No match found for regex '%s'\n", user_regex);
    }
  }
  fclose(input);
  return 0;
}

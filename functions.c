//Ruth Shiferaw
//JHED ID: RSHIFER1
#include "functions.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int read_file(FILE *fp, char words[][MAX_WORD_SIZE + 1], int size) {
  int word_count = 0;
  //storing words into 2D array (each row = 1 word)
  for(int i = 0; i < size; i++ ) {
    fscanf(fp, "%s", words[i]);
    if (*words[i] != '\0') { //checking if size param amount matches 
      word_count = word_count + 1; //counts the amount of words in the file
    }
  }
  
  //checking if actual amount of words is equal to or greater than stated size
  if ((word_count < size)) { //checks if num of words == defined num
    return 2; //error return num
  }
  return 0; //no issues, then return 0
}

int match(const char *regex, const char *word, int restriction) {
   int reg_length = (int)strlen(regex);
   bool all_tildes = false;
   int num_tildes = 0;

   //base case here
   if (*regex == '\0' && *word == '\0') {
    return 1;
    }

  // checking  kleene star
  //overarching if-statement starts here 
  if(regex[1] == '*') {
    // check if the rest of the regex matches with 0 or more of the current char being evaluated
    if(match(regex + 2, word, restriction)) { //if it's a match, will return 1 and exit
      return 1;
    }
    while (*word != '\0' && (*word == *regex)) {
      if (match(regex + 2, word + 1, restriction)) { //if matches, return 1 and exit
        return 1;
      }
      word++; //increment index to go through agaain
    }
  }

  // checking for question mark
  else if (regex[1] == '?') {
    // check if the rest of the regex matches 0 or 1 of the current character
    if (match(regex + 2, word, restriction)) {
      return 1; //if it matches, it will return 1 and exit 
    }
    if (*word == *regex) {
      return match(regex + 2, word + 1, restriction); //if not this will execute
    }
  }

  // checking for tilde symbol (with only ~ as regex input)
  else if (regex[0] == '~') {
    // match any single character
    for (int i = 0; i < reg_length; i++) {
      if (regex[0] == '~' && regex[0] == regex[i]) {
        all_tildes = true;
        num_tildes++;
      }
    }

    if (all_tildes == true) {
      if (((int)strlen(word)) <= (num_tildes*restriction)) {
        return 1;
      }
    }
  }

  //checking for tilde symbol (with a mix of letters)
  else if (regex[1] == '~') { 
    // checking if the leftover regex matches up to index of restriction int && still ends in current char
    for (int i = 0; i <= restriction && word[i] != '\0' && (word[i] == *regex); i++) {
      if (match(regex + 2, word + i + 1, restriction)) {
        return 1;
      }
    } 
  }

  //handling normal letters
  else if (*word != '\0' && (*word == *regex)) {
    return match(regex + 1, word + 1, restriction);
  }

  return 0; //if none of the other conditions are met, return 0 for a failed match
 }



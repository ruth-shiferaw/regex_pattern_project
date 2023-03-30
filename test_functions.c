//Ruth Shiferaw
//JHED ID: RSHIFER1
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "functions.h"

#define TEST_RESTRICTION_1 10
#define TEST_RESTRICTION_2 2
#define TEST_RESTRICTION_3 5
#define TEST_RESTRICTION_4 30
#define MAX_WORD_NUM 1024

void test_read_files() {
  char test_words [MAX_WORD_NUM][MAX_WORD_SIZE + 1];
  int num_file_words = 0;
  FILE* file_one = fopen("test_file_1.txt", "w");
  fprintf(file_one, "5\nintermediate\ninttterrmeediateeee\nprogram\nppproograaamm\naaa");
  fclose(file_one);

  file_one = fopen("test_file_1.txt", "r");
  fscanf(file_one, "%d", &num_file_words);
  assert(num_file_words == 5);
  assert(read_file(file_one, test_words, (num_file_words - 1)) == 0);
  assert(strcmp(test_words[0], "intermediate") == 0);
  fclose(file_one);
}

void test_match_regex() {
  assert(match("abc", "abc", TEST_RESTRICTION_1) == 1);
  assert(match("abcd", "abc", TEST_RESTRICTION_1) == 0);
  assert(match("", "", TEST_RESTRICTION_1) == 1);
  assert(match("aaa", "aa", TEST_RESTRICTION_2) == 0);
  assert(match("aaa","aaa", TEST_RESTRICTION_1) == 1);
}

void test_match_regex_star() {
  assert(match("abcd*", "abc", TEST_RESTRICTION_1) == 1);
  assert(match("abc*d", "abcccccccd", TEST_RESTRICTION_1) == 1);
  assert(match("abc*de", "abcccccccd", TEST_RESTRICTION_1) == 0);
  assert(match("a*a", "a", TEST_RESTRICTION_3) == 1);
  assert(match("a*", "aaa", TEST_RESTRICTION_1) == 1);
  assert(match("a*b", "aaa", TEST_RESTRICTION_3) == 0);
}

void test_match_regex_question() {
  assert(match("a?", "", TEST_RESTRICTION_1) == 1);
  assert(match("a?", "b", TEST_RESTRICTION_1) == 0);
  assert(match("a?", "a", TEST_RESTRICTION_1) == 1);
  assert(match("a?a?a?a?a?a?a?aaa", "aaa", TEST_RESTRICTION_4) == 1);
  assert(match("a?", "aaa", TEST_RESTRICTION_2) == 0);
  assert(match("p?", "ppproograaamm", TEST_RESTRICTION_2) == 0);
}

void test_match_regex_tilde() {
  assert(match("~", "aaaa", TEST_RESTRICTION_1) == 1);
  assert(match("~", "", TEST_RESTRICTION_1) == 1);
  assert(match("~", "a", TEST_RESTRICTION_1) == 1);
  assert(match("~", "inttterrmeediateeee", TEST_RESTRICTION_2) == 0);
  assert(match("~", "inttterrmeediateeee", TEST_RESTRICTION_4) == 1);
}

void test_match_regex_multiple() {
  assert(match("!2*keK?ee?rCC?C*aP?E*eR*T*", "!2222keKerCCCaeRRRT",
               TEST_RESTRICTION_1) == 1);
  assert(match("!~2*keK?ee?rCC?C*aP?E*eR*T*", "!2222keKerCCCaeRRRT",
               TEST_RESTRICTION_1) == 1);
  assert(match("~abc", "sda12!$2", TEST_RESTRICTION_1) == 1);
  assert(match("ina?ttt?t*e*r*ms?e*diate*", "intermediate",
               TEST_RESTRICTION_4) == 0);
  assert(match("ina?ttt?t*e*r*ms?e*diate*", "inttterrmeediateeee",
               TEST_RESTRICTION_4) == 1);
}

void test_match_regex_tilde_restriction() {
  assert(match("~", "aaaa", TEST_RESTRICTION_2) == 0);
  assert(match("~~", "aaaa", TEST_RESTRICTION_2) == 1);
  assert(match("~a", "aaa", TEST_RESTRICTION_1) == 1);
}

int main() {
  printf("Starting Tests...\n");
  test_read_files();
  test_match_regex();
  test_match_regex_star();
  test_match_regex_question();
  test_match_regex_tilde();
  test_match_regex_multiple();
  test_match_regex_tilde_restriction();
  printf("All tests passed!!!\n");
}

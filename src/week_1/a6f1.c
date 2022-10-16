#include <stdio.h>
#include <stdlib.h>

#define megisto_plithos 256
#define N 81

typedef enum { FALSE, TRUE } boolean;

typedef boolean typos_synolou[megisto_plithos];
typedef int stoixeio_synolou;

void Dimiourgia(typos_synolou synolo);
void Eisagogi(stoixeio_synolou stoixeio, typos_synolou synolo);
boolean Melos(stoixeio_synolou stoixeio, typos_synolou synolo);

void createAlphabetSet(typos_synolou set_alphabet);
boolean isVowel(char c, typos_synolou set_vowel);
void createVowelSet(typos_synolou set_vowel);
int vowelCount(char word[], typos_synolou set_alphabet,
               typos_synolou set_vowel);
void displayset(typos_synolou set);

int main() {
  typos_synolou vowels;
  typos_synolou alphabet;
  char word[N];

  createAlphabetSet(alphabet);
  createVowelSet(vowels);

  displayset(alphabet);
  displayset(vowels);

  int i;
  for (i = 0; i < 3; i++) {
    printf("Give a string with uppercase characters: ");
    gets(word);
    printf("Number of vowels: %d\n", vowelCount(word, alphabet, vowels));
  }
  return 0;
}

void createAlphabetSet(typos_synolou set_alphabet) {
  int i;
  Dimiourgia(set_alphabet);
  for (i = 65; i <= 90; i++) {
    Eisagogi(i, set_alphabet);
  }
}

boolean isVowel(char c, typos_synolou set_vowel) { return Melos(c, set_vowel); }

void createVowelSet(typos_synolou set_vowel) {
  Dimiourgia(set_vowel);
  Eisagogi(65, set_vowel);  // A
  Eisagogi(69, set_vowel);  // E
  Eisagogi(73, set_vowel);  // I
  Eisagogi(79, set_vowel);  // O
  Eisagogi(85, set_vowel);  // U
  Eisagogi(89, set_vowel);  // Y
}

int vowelCount(char word[], typos_synolou set_alphabet,
               typos_synolou set_vowel) {
  int i, vowelNo = 0;
  for (i = 0; word[i] != '\0'; i++) {
    if (isVowel(word[i], set_vowel)) {
      vowelNo++;
    } else if (!Melos(word[i], set_alphabet)) {
      printf("Invalid character detected: %c-%d \n", word[i], word[i]);
    }
  }
  return vowelNo;
}

void displayset(typos_synolou set) {
  stoixeio_synolou i;

  for (i = 0; i < megisto_plithos; i++) {
    if (Melos(i, set)) {
      printf("%c ", i);
    }
  }
  printf("\n");
}

void Dimiourgia(typos_synolou synolo) {
  stoixeio_synolou i;

  for (i = 0; i < megisto_plithos; i++) synolo[i] = FALSE;
}

void Eisagogi(stoixeio_synolou stoixeio, typos_synolou synolo) {
  synolo[stoixeio] = TRUE;
}

boolean Melos(stoixeio_synolou stoixeio, typos_synolou synolo) {
  return synolo[stoixeio];
}

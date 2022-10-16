#include <stdio.h>
#include <stdlib.h>

#define megisto_plithos 256

typedef enum { FALSE, TRUE } boolean;

typedef boolean typos_synolou[megisto_plithos];
typedef int stoixeio_synolou;

void Dimiourgia(typos_synolou synolo);
void Eisagogi(stoixeio_synolou stoixeio, typos_synolou synolo);
boolean Melos(stoixeio_synolou stoixeio, typos_synolou synolo);

boolean isValidInteger(char s[], typos_synolou set_char,
                       typos_synolou set_digit);
boolean isValidIdentifier(char s[], typos_synolou set_letter,
                          typos_synolou set_digit);

int main() {
  typos_synolou CharacterSet;
  typos_synolou DigitSet;
  typos_synolou LetterSet;

  char s[megisto_plithos], choice;
  int i;

  Dimiourgia(CharacterSet);
  Dimiourgia(DigitSet);
  Dimiourgia(LetterSet);

  Eisagogi(43, CharacterSet);
  Eisagogi(45, CharacterSet);

  for (i = 48; i <= 57; i++) {
    Eisagogi(i, DigitSet);
  }

  for (i = 65; i <= 90; i++) {
    Eisagogi(i, LetterSet);
  }

  for (i = 97; i <= 122; i++) {
    Eisagogi(i, LetterSet);
  }

  do {
    printf("Give an integer: ");
    scanf("%s", s);
    getchar();
    if (isValidInteger(s, CharacterSet, DigitSet)) {
      printf("Correct integer\n");
    } else {
      printf("Wrong integer\n");
    }
    do {
      printf("Continue with more integers (Y or N): ");
      scanf("%c", &choice);
    } while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');
  } while (choice == 'Y' || choice == 'y');

  do {
    printf("Give an identifier: ");
    scanf("%s", s);
    getchar();
    if (isValidIdentifier(s, LetterSet, DigitSet)) {
      printf("Correct identifier\n");
    } else {
      printf("Wrong identifier\n");
    }
    do {
      printf("Continue with more identifiers (Y or N): ");
      scanf("%c", &choice);
    } while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');
  } while (choice == 'Y' || choice == 'y');

  return 0;
}

boolean isValidInteger(char s[], typos_synolou set_char,
                       typos_synolou set_digit) {
  int i;
  boolean flag = TRUE;
  if (!Melos(s[0], set_char) && !Melos(s[0], set_digit)) {
    flag = FALSE;
  } else if (Melos(s[0], set_char) && !Melos(s[1], set_digit)) {
    flag = FALSE;
  } else {
    for (i = 1; s[i] != '\0' && flag; i++) {
      if (!Melos(s[i], set_digit)) {
        flag = FALSE;
      }
    }
  }
  return flag;
}

boolean isValidIdentifier(char s[], typos_synolou set_letter,
                          typos_synolou set_digit) {
  int i;
  boolean flag = TRUE;
  if (!Melos(s[0], set_letter)) {
    flag = FALSE;
  } else {
    for (i = 1; s[i] != '\0' && flag; i++) {
      if (!Melos(s[i], set_letter) && !Melos(s[i], set_digit) && s[i] != '_') {
        flag = FALSE;
      }
    }
  }
  return flag;
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

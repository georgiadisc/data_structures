#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char userid[9];
} QueueElementType;

typedef struct QueueNode *QueuePointer;

typedef struct QueueNode {
  QueueElementType Data;
  QueuePointer Next;
} QueueNode;

typedef struct {
  QueuePointer Front;
  QueuePointer Rear;
} QueueType;

typedef enum { FALSE, TRUE } boolean;

void CreateQ(QueueType *Queue);
boolean EmptyQ(QueueType Queue);
void AddQ(QueueType *Queue, QueueElementType Item);
void RemoveQ(QueueType *Queue, QueueElementType *Item);
void TraverseQ(QueueType Queue);

boolean search_for_userid(QueueElementType item);

int main() {
  QueueElementType AnItem;
  QueueType AQueue, BQueue;
  QueuePointer CurrPtr;
  boolean Flag;

  CreateQ(&AQueue);
  CreateQ(&BQueue);

  char Input;
  int User;

  do {
    printf("USERNAME: ");
    scanf("%s", AnItem.userid);
    getchar();
    if (search_for_userid(AnItem) == FALSE) {
      printf("Wrong user ID\n");
    } else {
      if (strncmp(AnItem.userid, "USR", 3) == 0) {
        CurrPtr = BQueue.Front;
        User = 1;
      } else {
        CurrPtr = AQueue.Front;
        User = 2;
      }
      Flag = FALSE;
      while (CurrPtr != NULL && Flag == FALSE) {
        if (strcmp(AnItem.userid, CurrPtr->Data.userid) == 0) {
          printf(
              "You have logged in to the system from another terminal. New "
              "access is forbidden.\n");
          Flag = TRUE;
        } else {
          CurrPtr = CurrPtr->Next;
        }
      }
      if (Flag == FALSE) {
        if (User == 1) {
          AddQ(&BQueue, AnItem);
        } else {
          AddQ(&AQueue, AnItem);
        }
      }
    }
    do {
      printf("New insertion?(Y/N): ");
      scanf("%c", &Input);
      getchar();
    } while (Input != 'Y' && Input != 'N');
  } while (Input != 'N');

  printf("Oura Diaxeiristwn\n");
  TraverseQ(AQueue);

  printf("Oura Aplwn Xrhstwn\n");
  TraverseQ(BQueue);

  return 0;
}

boolean search_for_userid(QueueElementType item) {
  FILE *fp;
  QueueElementType str;
  if ((fp = fopen("I11F4.dat", "r")) == NULL)
    printf("problem opening file\n");
  else {
    while (!feof(fp)) {
      fscanf(fp, "%s", str.userid);
      if (strcmp(str.userid, item.userid) == 0) {
        fclose(fp);
        return TRUE;
      }
    }
  }
  fclose(fp);
  return FALSE;
}

void CreateQ(QueueType *Queue) {
  (*Queue).Front = NULL;
  Queue->Rear = NULL;
}

boolean EmptyQ(QueueType Queue) { return (Queue.Front == NULL); }

void AddQ(QueueType *Queue, QueueElementType Item) {
  QueuePointer TempPtr;

  TempPtr = (QueuePointer)malloc(sizeof(struct QueueNode));
  TempPtr->Data = Item;
  TempPtr->Next = NULL;
  if (Queue->Front == NULL)
    Queue->Front = TempPtr;
  else
    Queue->Rear->Next = TempPtr;
  Queue->Rear = TempPtr;
}

void RemoveQ(QueueType *Queue, QueueElementType *Item) {
  QueuePointer TempPtr;

  if (EmptyQ(*Queue)) {
    printf("EMPTY Queue\n");
  } else {
    TempPtr = Queue->Front;
    *Item = TempPtr->Data;
    Queue->Front = Queue->Front->Next;
    free(TempPtr);
    if (Queue->Front == NULL) Queue->Rear = NULL;
  }
}

void TraverseQ(QueueType Queue) {
  QueuePointer CurrPtr;

  if (EmptyQ(Queue)) {
    printf("EMPTY Queue\n");
  } else {
    CurrPtr = Queue.Front;
    while (CurrPtr != NULL) {
      printf("%s\n", CurrPtr->Data.userid);
      CurrPtr = CurrPtr->Next;
    }
  }
}

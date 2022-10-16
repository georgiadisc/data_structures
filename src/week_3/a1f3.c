#include <stdio.h>

#define QueueLimit 21

typedef int QueueElementType;

typedef struct {
  int Front, Rear;
  QueueElementType Element[QueueLimit];
} QueueType;

typedef enum { FALSE, TRUE } boolean;

void CreateQ(QueueType *Queue);
boolean EmptyQ(QueueType Queue);
boolean FullQ(QueueType Queue);
void RemoveQ(QueueType *Queue, QueueElementType *Item);
void AddQ(QueueType *Queue, QueueElementType Item);
void TraverseQ(QueueType Queue);

int QSizeA(QueueType Queue);
int QSizeB(QueueType *Queue);

int main() {
  int i, item;
  QueueType Queue;
  CreateQ(&Queue);
  for (i = 0; i < 20; i++) {
    AddQ(&Queue, i);
  }
  // A
  printf("Question a\n");

  printf("Printing Queue\n");
  TraverseQ(Queue);

  printf("(QSizeA) size=%d\n", QSizeA(Queue));
  printf("Printing Queue\n");
  TraverseQ(Queue);

  printf("(QSizeB) size=%d\n", QSizeB(&Queue));
  printf("Printing Queue\n");
  TraverseQ(Queue);
  printf("\n");
  // B
  printf("Question b\n");

  CreateQ(&Queue);
  for (i = 0; i < 20; i++) {
    AddQ(&Queue, i);
  }
  for (i = 0; i < 10; i++) {
    RemoveQ(&Queue, &item);
  }

  printf("Printing Queue\n");
  TraverseQ(Queue);

  printf("(QSizeA) size=%d\n", QSizeA(Queue));
  printf("Printing Queue\n");
  TraverseQ(Queue);

  printf("(QSizeB) size=%d\n", QSizeB(&Queue));
  printf("Printing Queue\n");
  TraverseQ(Queue);

  printf("\n");
  // C
  printf("Question c\n");

  printf("(QSizeA) size=%d\n", QSizeA(Queue));
  printf("Printing Queue\n");
  TraverseQ(Queue);

  printf("(QSizeB) size=%d\n", QSizeB(&Queue));
  printf("Printing Queue\n");
  TraverseQ(Queue);

  return 0;
}

int QSizeA(QueueType Queue) { return Queue.Rear - Queue.Front; }

int QSizeB(QueueType *Queue) {
  int j = 0, item;
  while (!EmptyQ(*Queue)) {
    RemoveQ(Queue, &item);
    j++;
  }
  return j;
}

void CreateQ(QueueType *Queue) {
  Queue->Front = 0;
  Queue->Rear = 0;
}

boolean EmptyQ(QueueType Queue) { return (Queue.Front == Queue.Rear); }

boolean FullQ(QueueType Queue) {
  return ((Queue.Front) == ((Queue.Rear + 1) % QueueLimit));
}

void RemoveQ(QueueType *Queue, QueueElementType *Item) {
  if (!EmptyQ(*Queue)) {
    *Item = Queue->Element[Queue->Front];
    Queue->Front = (Queue->Front + 1) % QueueLimit;
  } else
    printf("Empty Queue\n");
}

void AddQ(QueueType *Queue, QueueElementType Item) {
  if (!FullQ(*Queue)) {
    Queue->Element[Queue->Rear] = Item;
    Queue->Rear = (Queue->Rear + 1) % QueueLimit;
  } else
    printf("Full Queue\n");
}

void TraverseQ(QueueType Queue) {
  int current;
  if (!EmptyQ(Queue)) {
    current = Queue.Front;
    while (current != Queue.Rear) {
      printf("%d ", Queue.Element[current]);
      current = (current + 1) % QueueLimit;
    }
    printf("\n");
  } else
    printf("Empty Queue\n");
}

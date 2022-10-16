#include <stdio.h>

#define QueueLimit 22
#define StackLimit 22

typedef double StackElementType;

typedef struct {
  int Top;
  StackElementType Element[StackLimit];
} StackType;

typedef double QueueElementType;

typedef struct {
  int Front, Rear;
  QueueElementType Element[QueueLimit];
} QueueType;

typedef enum { FALSE, TRUE } boolean;

void CreateStack(StackType *Stack);
boolean EmptyStack(StackType Stack);
boolean FullStack(StackType Stack);
void Push(StackType *Stack, StackElementType Item);
void Pop(StackType *Stack, StackElementType *Item);

void CreateQ(QueueType *Queue);
boolean EmptyQ(QueueType Queue);
boolean FullQ(QueueType Queue);
void RemoveQ(QueueType *Queue, QueueElementType *Item);
void AddQ(QueueType *Queue, QueueElementType Item);
void TraverseQ(QueueType Queue);

void ReverseQ(QueueType *Queue);

int main() {
  QueueType Queue;
  CreateQ(&Queue);
  double i;
  for (i = 0; i <= 10; i += 0.5) {
    AddQ(&Queue, i);
  }
  TraverseQ(Queue);
  printf("\n");
  printf("Reverse Queue\n");
  ReverseQ(&Queue);
  TraverseQ(Queue);
  return 0;
}

void ReverseQ(QueueType *Queue) {
  double item;
  StackType temp;
  CreateStack(&temp);
  while (!EmptyQ(*Queue)) {
    RemoveQ(Queue, &item);
    Push(&temp, item);
  }
  while (!EmptyStack(temp)) {
    Pop(&temp, &item);
    AddQ(Queue, item);
  }
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
      printf("%.2f ", Queue.Element[current]);
      current = (current + 1) % QueueLimit;
    }
    printf("\n");
  } else
    printf("Empty Queue\n");
}

void CreateStack(StackType *Stack) { Stack->Top = -1; }

boolean EmptyStack(StackType Stack) { return (Stack.Top == -1); }

boolean FullStack(StackType Stack) { return (Stack.Top == (StackLimit - 1)); }

void Push(StackType *Stack, StackElementType Item) {
  if (!FullStack(*Stack)) {
    Stack->Top++;
    Stack->Element[Stack->Top] = Item;
  } else
    printf("Full Stack...");
}

void Pop(StackType *Stack, StackElementType *Item) {
  if (!EmptyStack(*Stack)) {
    *Item = Stack->Element[Stack->Top];
    Stack->Top--;
  } else
    printf("Empty Stack...");
}

#include <stdio.h>

#define StackLimit 50

typedef int StackElementType;

typedef struct {
  int Top;
  StackElementType Element[StackLimit];
} StackType;

typedef enum { FALSE, TRUE } boolean;

void CreateStack(StackType *Stack);
boolean EmptyStack(StackType Stack);
boolean FullStack(StackType Stack);
void Push(StackType *Stack, StackElementType Item);
void Pop(StackType *Stack, StackElementType *Item);

void TraverseStack(StackType Stack);

int main() {
  int i;
  StackElementType item, min;
  StackType Stack, mStack;

  CreateStack(&Stack);
  CreateStack(&mStack);

  printf("Dwse to epomeno stoixeio: ");
  scanf("%d", &item);
  Push(&Stack, item);
  min = item;
  Push(&mStack, min);
  TraverseStack(Stack);
  printf("Min=%d\n", min);

  for (i = 1; i < 6; i++) {
    printf("Dwse to epomeno stoixeio: ");
    scanf("%d", &item);
    if (item <= min) {
      min = item;
      Push(&mStack, item);
    }
    Push(&Stack, item);
    TraverseStack(Stack);
    printf("Min=%d\n", min);
  }

  printf("\n");

  printf("Emptying stack\n");

  while (!EmptyStack(Stack)) {
    Pop(&Stack, &item);
    if (item == min) {
      Pop(&mStack, &min);
      if (!EmptyStack(mStack)) {
        Pop(&mStack, &min);
        Push(&mStack, min);
        printf("Min=%d\n", min);
      }
    }
    TraverseStack(Stack);
  }
  return 0;
}

void TraverseStack(StackType Stack) {
  int i;
  printf("plithos sto stack %d\n", Stack.Top + 1);
  for (i = 0; i <= Stack.Top; i++) {
    printf("%d ", Stack.Element[i]);
  }
  printf("\n");
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

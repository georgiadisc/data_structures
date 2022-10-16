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

void GetNthElementA(StackType *Stack, int n, StackElementType *nelement);
void GetNthElementB(StackType Stack, int n, StackElementType *nelement);
void TraverseStack(StackType Stack);

int main() {
  int i, n;
  StackElementType nelement;

  StackType Stack;
  CreateStack(&Stack);

  for (i = 2; i <= StackLimit; i += 2) {
    Push(&Stack, i);
  }

  TraverseStack(Stack);

  do {
    printf("Dwse n: ");
    scanf("%d", &n);
  } while (!(n >= 1 && n <= StackLimit / 2));

  GetNthElementA(&Stack, n, &nelement);
  printf("Top with GetNthElementA = %d\n", nelement);
  TraverseStack(Stack);

  GetNthElementB(Stack, n, &nelement);
  printf("Top with GetNthElementB = %d\n", nelement);
  TraverseStack(Stack);

  return 0;
}

void GetNthElementA(StackType *Stack, int n, StackElementType *nelement) {
  int i;
  StackType temp;
  CreateStack(&temp);
  StackElementType item;
  for (i = 0; i < n; i++) {
    Pop(Stack, &item);
    Push(&temp, item);
  }
  *nelement = item;
  for (i = 0; i < n; i++) {
    Pop(&temp, &item);
    Push(Stack, item);
  }
}

void GetNthElementB(StackType Stack, int n, StackElementType *nelement) {
  *nelement = Stack.Element[Stack.Top - n + 1];
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

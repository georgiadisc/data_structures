#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int containers;
  float weight;
  char date[11];
} StackElementType;

typedef struct StackNode *StackPointer;

typedef struct StackNode {
  StackElementType Data;
  StackPointer Next;
} StackNode;

typedef enum { FALSE, TRUE } boolean;

void CreateStack(StackPointer *Stack);
boolean EmptyStack(StackPointer Stack);
void Push(StackPointer *Stack, StackElementType Item);
void Pop(StackPointer *Stack, StackElementType *Item);
void TraverseStack(StackPointer Stack);

int IndexOfMin(StackPointer Warehouse1, StackPointer Warehouse2,
               StackPointer Warehouse3);
int StackSize(StackPointer Warehouse);

int main() {
  StackPointer Warehouse1, Warehouse2, Warehouse3;
  StackElementType AnItem;
  int shipments, i, min;

  CreateStack(&Warehouse1);
  CreateStack(&Warehouse2);
  CreateStack(&Warehouse3);

  printf("Plithos fortiwn: ");
  scanf("%d", &shipments);

  for (i = 1; i <= shipments; i++) {
    printf("Arithmos kivwtiwn gia to %do fortio: ", i);
    scanf("%d", &AnItem.containers);

    printf("Synoliko baros gia to %do fortio: ", i);
    scanf("%f", &AnItem.weight);

    printf("Imeromhnia liksis gia to %do fortio: ", i);
    scanf("%s", AnItem.date);
    getchar();

    min = IndexOfMin(Warehouse1, Warehouse2, Warehouse3);

    if (min == 1) {
      Push(&Warehouse1, AnItem);
    } else if (min == 2) {
      Push(&Warehouse2, AnItem);
    } else {
      Push(&Warehouse3, AnItem);
    }
  }

  printf("WAREHOUSE 1\n");
  TraverseStack(Warehouse3);

  printf("WAREHOUSE 2\n");
  TraverseStack(Warehouse2);

  printf("WAREHOUSE 3\n");
  TraverseStack(Warehouse1);

  return 0;
}

void CreateStack(StackPointer *Stack) { *Stack = NULL; }

boolean EmptyStack(StackPointer Stack) { return (Stack == NULL); }

void Push(StackPointer *Stack, StackElementType Item) {
  StackPointer TempPtr;

  TempPtr = (StackPointer)malloc(sizeof(struct StackNode));
  TempPtr->Data = Item;
  TempPtr->Next = *Stack;
  *Stack = TempPtr;
}

void Pop(StackPointer *Stack, StackElementType *Item) {
  StackPointer TempPtr;

  if (EmptyStack(*Stack)) {
    printf("EMPTY Stack\n");
  } else {
    TempPtr = *Stack;
    *Item = TempPtr->Data;
    *Stack = TempPtr->Next;
    free(TempPtr);
  }
}

void TraverseStack(StackPointer Stack) {
  StackPointer CurrPtr;

  if (EmptyStack(Stack)) {
    printf("EMPTY Stack\n");
  } else {
    CurrPtr = Stack;
    while (CurrPtr != NULL) {
      printf("%d %.2f %s\n", CurrPtr->Data.containers, CurrPtr->Data.weight,
             CurrPtr->Data.date);
      CurrPtr = CurrPtr->Next;
    }
  }
  printf("\n");
}

int IndexOfMin(StackPointer Warehouse1, StackPointer Warehouse2,
               StackPointer Warehouse3) {
  if (StackSize(Warehouse1) <= StackSize(Warehouse2) &&
      StackSize(Warehouse1) <= StackSize(Warehouse3)) {
    return 1;
  } else if (StackSize(Warehouse2) <= StackSize(Warehouse1) &&
             StackSize(Warehouse2) <= StackSize(Warehouse3)) {
    return 2;
  } else {
    return 3;
  }
}

int StackSize(StackPointer Warehouse) {
  StackPointer CurrPtr;
  int Count;

  Count = 0;
  CurrPtr = Warehouse;

  while (CurrPtr != NULL) {
    Count += CurrPtr->Data.containers;
    CurrPtr = CurrPtr->Next;
  }

  return Count;
}

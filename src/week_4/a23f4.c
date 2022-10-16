#include <stdio.h>
#include <stdlib.h>

#define StackLimit 10
#define NumberOfNodes 10
#define NilValue -1

typedef int StackElementType;

typedef struct {
  int Top;
  StackElementType Element[StackLimit];
} StackType;

typedef struct {
  int ssn;
  float grade;
} ListElementType;

typedef int ListPointer;

typedef struct {
  ListElementType Data;
  ListPointer Next;
} NodeType;

typedef enum { FALSE, TRUE } boolean;

void CreateStack(StackType *Stack);
boolean EmptyStack(StackType Stack);
boolean FullStack(StackType Stack);
void Push(StackType *Stack, StackElementType Item);
void Pop(StackType *Stack, StackElementType *Item);
void TraverseStack(StackType Stack);

void InitializeStoragePool(NodeType Node[], ListPointer *FreePtr);
void CreateList(ListPointer *List);
boolean EmptyList(ListPointer List);
boolean FullList(ListPointer FreePtr);
void GetNode(ListPointer *P, ListPointer *FreePtr, NodeType Node[]);
void ReleaseNode(NodeType Node[NumberOfNodes], ListPointer P,
                 ListPointer *FreePtr);
void Insert(ListPointer *List, NodeType Node[], ListPointer *FreePtr,
            ListPointer PredPtr, ListElementType Item);
void Delete(ListPointer *List, NodeType Node[], ListPointer *FreePtr,
            ListPointer PredPtr);
void TraverseLinked(ListPointer List, NodeType Node[]);
void printAll(ListPointer List, ListPointer FreePtr, NodeType Node[]);

float FindMaxs(ListPointer List, NodeType Node[NumberOfNodes],
               StackType *Stack);

int main() {
  int i, item, ssn;
  float max, grade;
  NodeType Node[NumberOfNodes];
  ListPointer FreePtr;
  ListPointer PredPtr = NilValue;
  ListPointer List;
  StackType Stack, temp;
  CreateStack(&Stack);
  CreateStack(&temp);
  // 1
  InitializeStoragePool(Node, &FreePtr);
  // 2
  CreateList(&List);
  // 3
  printAll(List, FreePtr, Node);
  // 4
  printf("Question 4\n");
  printf("Linked list\n");
  TraverseLinked(List, Node);
  // 5
  printf("Question 5\n");
  for (i = 0; i < 5; i++) {
    printf("DWSE AM GIA EISAGWGH STH LISTA: ");
    scanf("%d", &ssn);
    printf("DWSE VATHMO GIA EISAGWGH STH LISTA: ");
    scanf("%f", &grade);
    ListElementType Item = {ssn, grade};
    Insert(&List, Node, &FreePtr, PredPtr, Item);
  }
  // 6
  printf("Question 6\n");
  printf("Storage pool\n");
  printAll(List, FreePtr, Node);
  // 7
  printf("Question 7\n");
  printf("Linked list\n");
  TraverseLinked(List, Node);
  // 8
  printf("Question 8\n");
  if (EmptyList(List)) {
    printf("Empty List\n");
  } else {
    printf("Not an Empty List\n");
  }
  // 9
  printf("Question 9\n");
  if (EmptyList(List)) {
    printf("Full List\n");
  } else {
    printf("Not a Full List\n");
  }
  // 10
  max = FindMaxs(List, Node, &Stack);
  printf("Question 10\n");
  printf("Max vathmos=%.1f\n", max);
  printf("AM me megisto vathmo: ");
  while (!EmptyStack(Stack)) {
    Pop(&Stack, &item);
    Push(&temp, item);
  }
  while (!EmptyStack(temp)) {
    Pop(&temp, &item);
    printf("%d ", item);
  }
  printf("\n");
  // 11
  printf("Question 11\n");
  TraverseStack(Stack);
  // 12
  printf("Question 12\n");
  printf("Storage pool\n");
  printAll(List, FreePtr, Node);
  // 13
  printf("Question 13\n");
  printf("Linked list\n");
  TraverseLinked(List, Node);

  return 0;
}

float FindMaxs(ListPointer List, NodeType Node[NumberOfNodes],
               StackType *Stack) {
  int i, temp;
  float max;
  if (EmptyList(List)) {
    printf("Empty list\n");
    return -1;
  } else {
    max = Node[0].Data.grade;
    for (i = 1; i < NumberOfNodes; i++) {
      if (Node[i].Data.grade > max) {
        max = Node[i].Data.grade;
        while (!EmptyStack(*Stack)) {
          Pop(Stack, &temp);
        }
        Push(Stack, Node[i].Data.ssn);
      } else if (Node[i].Data.grade == max) {
        Push(Stack, Node[i].Data.ssn);
      }
    }
  }
  return max;
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

void TraverseStack(StackType Stack) {
  int i;
  printf("\nplithos sto stack %d\n", Stack.Top + 1);
  for (i = Stack.Top; i >= 0; i--) {
    printf("%d ", Stack.Element[i]);
  }
  printf("\n");
}

void InitializeStoragePool(NodeType Node[], ListPointer *FreePtr) {
  int i;

  for (i = 0; i < NumberOfNodes - 1; i++) {
    Node[i].Next = i + 1;
    Node[i].Data.ssn = -1;
    Node[i].Data.grade = -1.0;
  }
  Node[NumberOfNodes - 1].Next = NilValue;
  Node[NumberOfNodes - 1].Data.ssn = -1;
  Node[NumberOfNodes - 1].Data.grade = -1.0;
  *FreePtr = 0;
}

void CreateList(ListPointer *List) { *List = NilValue; }

boolean EmptyList(ListPointer List) { return (List == NilValue); }

boolean FullList(ListPointer FreePtr) { return (FreePtr == NilValue); }

void GetNode(ListPointer *P, ListPointer *FreePtr, NodeType Node[]) {
  *P = *FreePtr;
  if (!FullList(*FreePtr)) *FreePtr = Node[*FreePtr].Next;
}

void ReleaseNode(NodeType Node[], ListPointer P, ListPointer *FreePtr) {
  Node[P].Next = *FreePtr;
  Node[P].Data.ssn = -1;
  Node[P].Data.grade = -1.0;
  *FreePtr = P;
}

void Insert(ListPointer *List, NodeType Node[], ListPointer *FreePtr,
            ListPointer PredPtr, ListElementType Item) {
  ListPointer TempPtr;
  GetNode(&TempPtr, FreePtr, Node);
  if (!FullList(TempPtr)) {
    if (PredPtr == NilValue) {
      Node[TempPtr].Data = Item;
      Node[TempPtr].Next = *List;
      *List = TempPtr;
    } else {
      Node[TempPtr].Data = Item;
      Node[TempPtr].Next = Node[PredPtr].Next;
      Node[PredPtr].Next = TempPtr;
    }
  } else {
    printf("Full List ...\n");
  }
}

void Delete(ListPointer *List, NodeType Node[], ListPointer *FreePtr,
            ListPointer PredPtr) {
  ListPointer TempPtr;

  if (!EmptyList(*List))
    if (PredPtr == NilValue) {
      TempPtr = *List;
      *List = Node[TempPtr].Next;
      ReleaseNode(Node, TempPtr, FreePtr);
    } else {
      TempPtr = Node[PredPtr].Next;
      Node[PredPtr].Next = Node[TempPtr].Next;
      ReleaseNode(Node, TempPtr, FreePtr);
    }
  else
    printf("Empty List ...\n");
}

void TraverseLinked(ListPointer List, NodeType Node[]) {
  ListPointer CurrPtr;

  if (!EmptyList(List)) {
    CurrPtr = List;
    while (CurrPtr != NilValue) {
      printf("(%d:<%d,%.1f> ->%d) ", CurrPtr, Node[CurrPtr].Data.ssn,
             Node[CurrPtr].Data.grade, Node[CurrPtr].Next);
      CurrPtr = Node[CurrPtr].Next;
    }
    printf("\n");
  } else
    printf("Empty List ...\n");
}

void printAll(ListPointer List, ListPointer FreePtr, NodeType Node[]) {
  int i;
  printf("1o STOIXEIO LISTAS=%d, 1H FREE POSITION=%d\n", List, FreePtr);
  printf("H STORAGE POOL EXEI TA EJHS STOIXEIA\n");
  for (i = 0; i < NumberOfNodes; i++)
    printf("(%d:<%d,%.1f> ->%d) ", i, Node[i].Data.ssn, Node[i].Data.grade,
           Node[i].Next);
  printf("\n");
}

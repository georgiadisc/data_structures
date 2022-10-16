#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NumberOfNodes 10
#define NilValue -1
#define NameSize 21

typedef struct {
  char name[NameSize];
  int school;
} ListElementType;

typedef int ListPointer;

typedef struct {
  ListElementType Data;
  ListPointer Next;
} NodeType;

typedef enum { FALSE, TRUE } boolean;

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
            ListPointer PredPtr, ListElementType *Item);
void TraverseLinked(ListPointer List, NodeType Node[]);
void printAll(ListPointer List, ListPointer FreePtr, NodeType Node[]);

boolean LinearSearch(ListPointer List, NodeType Node[]);

int main() {
  NodeType Node_A[NumberOfNodes];
  NodeType Node_B[NumberOfNodes];

  FILE *input;
  int i, pos, scan;
  char termch;

  ListElementType Item;
  ListPointer List_A, FreePtr_A, CurrPtr_A, PrevPtr_A = NilValue;
  ListPointer List_B, FreePtr_B, PrevPtr_B, CurrPtr_B = NilValue;

  InitializeStoragePool(Node_A, &FreePtr_A);
  CreateList(&List_A);

  InitializeStoragePool(Node_B, &FreePtr_B);
  CreateList(&List_B);

  // A
  printf("Question a:\n");
  input = fopen("students.dat", "r");

  while (TRUE) {
    scan = fscanf(input, "%s%c", Item.name, &termch);
    scan = fscanf(input, "%d%c", &Item.school, &termch);
    if (scan == EOF) break;
    Insert(&List_A, Node_A, &FreePtr_A, PrevPtr_A, Item);
  }

  printAll(List_A, FreePtr_A, Node_A);
  printf("Lista A\n");
  TraverseLinked(List_A, Node_A);

  // B
  PrevPtr_B = NilValue;

  for (i = 0; i < 4; i++) {
    do {
      printf("Dwse thn thesh toy ma8hth poy klhrw8hke: ");
      scanf("%d", &pos);
      getchar();
    } while (!(pos >= 0 && pos <= 9));
    PrevPtr_A = NilValue;
    CurrPtr_A = List_A;
    while (CurrPtr_A != pos) {
      PrevPtr_A = CurrPtr_A;
      CurrPtr_A = Node_A[CurrPtr_A].Next;
    }
    Delete(&List_A, Node_A, &FreePtr_A, PrevPtr_A, &Item);
    Insert(&List_B, Node_B, &FreePtr_B, PrevPtr_B, Item);

    PrevPtr_B = List_B;
    while (Node_B[PrevPtr_B].Next != NilValue) {
      PrevPtr_B = Node_B[PrevPtr_B].Next;
    }
  }

  printf("Question b: \n");

  printAll(List_A, FreePtr_A, Node_A);
  printf("Lista A\n");
  TraverseLinked(List_A, Node_A);

  printAll(List_B, FreePtr_B, Node_B);
  printf("Lista B\n");
  TraverseLinked(List_B, Node_B);

  // C
  printf("Question c: \n");
  PrevPtr_B = NilValue;
  CurrPtr_B = List_B;

  while (CurrPtr_B != 1) {
    PrevPtr_B = CurrPtr_B;
    CurrPtr_B = Node_B[CurrPtr_B].Next;
  }

  Delete(&List_B, Node_B, &FreePtr_B, PrevPtr_B, &Item);
  PrevPtr_A = NilValue;
  Insert(&List_A, Node_A, &FreePtr_A, PrevPtr_A, Item);

  printAll(List_A, FreePtr_A, Node_A);
  printf("Lista A\n");
  TraverseLinked(List_A, Node_A);

  printAll(List_B, FreePtr_B, Node_B);
  printf("Lista B\n");
  TraverseLinked(List_B, Node_B);

  fclose(input);
  return 0;
}

void InitializeStoragePool(NodeType Node[], ListPointer *FreePtr) {
  int i;

  for (i = 0; i < NumberOfNodes - 1; i++) {
    Node[i].Next = i + 1;
    Node[i].Data.name[0] = '\0';
    Node[i].Data.school = -1;
  }
  Node[NumberOfNodes - 1].Next = NilValue;
  Node[NumberOfNodes - 1].Data.name[0] = '\0';
  Node[NumberOfNodes - 1].Data.school = -1;
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
  Node[P].Data.name[0] = '\0';
  Node[P].Data.school = -1;

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
  } else
    printf("Full List ...\n");
}

void Delete(ListPointer *List, NodeType Node[], ListPointer *FreePtr,
            ListPointer PredPtr, ListElementType *Item) {
  ListPointer TempPtr;

  if (!EmptyList(*List)) {
    if (PredPtr == NilValue) {
      TempPtr = *List;
      *List = Node[TempPtr].Next;
    } else {
      TempPtr = Node[PredPtr].Next;
      Node[PredPtr].Next = Node[TempPtr].Next;
    }
    strcpy(Item->name, Node[TempPtr].Data.name);
    Item->school = Node[TempPtr].Data.school;
    ReleaseNode(Node, TempPtr, FreePtr);
  } else
    printf("Empty List ...\n");
}

void TraverseLinked(ListPointer List, NodeType Node[]) {
  ListPointer CurrPtr;

  if (!EmptyList(List)) {
    CurrPtr = List;
    while (CurrPtr != NilValue) {
      printf("(%d:<%s,%d> ->%d) ", CurrPtr, Node[CurrPtr].Data.name,
             Node[CurrPtr].Data.school, Node[CurrPtr].Next);
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
    printf("(%d:<%s,%d> ->%d) ", i, Node[i].Data.name, Node[i].Data.school,
           Node[i].Next);
  printf("\n");
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NumberOfNodes 10
#define NilValue -1
#define NameSize 21

typedef struct {
  char name[NameSize];
  int weight;
  int cost;
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
            ListPointer PredPtr);
void TraverseLinked(ListPointer List, NodeType Node[]);
void printAll(ListPointer List, ListPointer FreePtr, NodeType Node[]);

void sort_list(ListPointer *List, NodeType Node[], boolean Ascending,
               int ByFeature);
void switch_positions(ListPointer PrevPtr, ListPointer CurrentPtr,
                      ListPointer NextPtr, NodeType Node[], ListPointer *List);

int main() {
  int i, objects;
  ListElementType Item;
  ListPointer List, FreePtr, PredPtr = NilValue;
  NodeType Node[NumberOfNodes];
  // 1
  InitializeStoragePool(Node, &FreePtr);
  // 2
  CreateList(&List);
  // 3
  printAll(List, FreePtr, Node);
  // 4
  TraverseLinked(List, Node);
  // 5
  do {
    printf("Give objects number: ");
    scanf("%d", &objects);
  } while (!(objects >= 0 && objects <= NumberOfNodes));
  // 6
  for (i = 0; i < objects; i++) {
    printf("Give name: ");
    scanf("%s", Item.name);
    getchar();

    printf("Give weight: ");
    scanf("%d", &Item.weight);

    printf("Give cost: ");
    scanf("%d", &Item.cost);

    Insert(&List, Node, &FreePtr, PredPtr, Item);
  }
  // 7
  printAll(List, FreePtr, Node);
  // 8
  TraverseLinked(List, Node);
  // 9
  printf("Name Ascending\n");
  sort_list(&List, Node, TRUE, 1);
  TraverseLinked(List, Node);
  // 10
  printf("Weight Ascending\n");
  sort_list(&List, Node, TRUE, 2);
  TraverseLinked(List, Node);
  // 11
  printf("Cost Ascending\n");
  sort_list(&List, Node, TRUE, 3);
  TraverseLinked(List, Node);
  // 12
  printf("Name Descending\n");
  sort_list(&List, Node, FALSE, 1);
  TraverseLinked(List, Node);
  // 13
  printf("Weight Descending\n");
  sort_list(&List, Node, FALSE, 2);
  TraverseLinked(List, Node);
  // 14
  printf("Cost Descending\n");
  sort_list(&List, Node, FALSE, 3);
  TraverseLinked(List, Node);
  return 0;
}

void sort_list(ListPointer *List, NodeType Node[], boolean Ascending,
               int ByFeature) {
  ListPointer NextPointer, CurrPtr, PrevPtr, OutPtr;
  boolean swap;

  if (!EmptyList(*List)) {
    OutPtr = *List;
    while (OutPtr != NilValue) {
      CurrPtr = *List;
      PrevPtr = NilValue;
      NextPointer = Node[CurrPtr].Next;
      while (NextPointer != NilValue) {
        swap = FALSE;
        if (Ascending == TRUE) {
          switch (ByFeature) {
            case 1:
              if (strcmp(Node[CurrPtr].Data.name, Node[NextPointer].Data.name) >
                  0) {
                swap = TRUE;
              }
              break;
            case 2:
              if (Node[CurrPtr].Data.weight > Node[NextPointer].Data.weight) {
                swap = TRUE;
              }
              break;
            case 3:
              if (Node[CurrPtr].Data.cost > Node[NextPointer].Data.cost) {
                swap = TRUE;
              }
              break;
          }
        } else {
          switch (ByFeature) {
            case 1:
              if (strcmp(Node[CurrPtr].Data.name, Node[NextPointer].Data.name) <
                  0) {
                swap = TRUE;
              }
              break;
            case 2:
              if (Node[CurrPtr].Data.weight < Node[NextPointer].Data.weight) {
                swap = TRUE;
              }
              break;
            case 3:
              if (Node[CurrPtr].Data.cost < Node[NextPointer].Data.cost) {
                swap = TRUE;
              }
              break;
          }
        }
        if (swap == TRUE) {
          switch_positions(PrevPtr, CurrPtr, NextPointer, Node, List);
          if (OutPtr == CurrPtr) {
            OutPtr = NextPointer;
          }
        }
        PrevPtr = CurrPtr;
        CurrPtr = NextPointer;
        NextPointer = Node[NextPointer].Next;
      }
      OutPtr = Node[OutPtr].Next;
    }
  } else {
    printf("Empty List ...\n");
  }
}

void switch_positions(ListPointer PrevPtr, ListPointer CurrentPtr,
                      ListPointer NextPtr, NodeType Node[], ListPointer *List) {
  if (CurrentPtr == *List) {
    *List = NextPtr;
  }
  Node[CurrentPtr].Next = Node[NextPtr].Next;
  Node[NextPtr].Next = CurrentPtr;
  if (PrevPtr != NilValue) {
    Node[PrevPtr].Next = NextPtr;
  }
}

void InitializeStoragePool(NodeType Node[], ListPointer *FreePtr) {
  int i;

  for (i = 0; i < NumberOfNodes - 1; i++) {
    Node[i].Next = i + 1;
    Node[i].Data.name[0] = '\0';
    Node[i].Data.weight = 0;
    Node[i].Data.cost = 0;
  }
  Node[NumberOfNodes - 1].Next = NilValue;
  Node[NumberOfNodes - 1].Data.name[0] = '\0';
  Node[NumberOfNodes - 1].Data.weight = 0;
  Node[NumberOfNodes - 1].Data.cost = 0;
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
  Node[P].Data.weight = 0;
  Node[P].Data.cost = 0;
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
      printf("(%s,%d,%d)\n", Node[CurrPtr].Data.name, Node[CurrPtr].Data.weight,
             Node[CurrPtr].Data.cost);
      CurrPtr = Node[CurrPtr].Next;
    }
    printf("\n");
  } else
    printf("Empty List ...\n");
}

void printAll(ListPointer List, ListPointer FreePtr, NodeType Node[]) {
  int i;
  printf("H STORAGE POOL EXEI TA EJHS STOIXEIA\n");
  for (i = 0; i < NumberOfNodes; i++)
    printf("(%d:<%s,%d,%d> ->%d)", i, Node[i].Data.name, Node[i].Data.weight,
           Node[i].Data.cost, Node[i].Next);
  printf("\n");
}

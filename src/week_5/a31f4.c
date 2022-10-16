#include <stdio.h>
#include <stdlib.h>

#define observations_limit 25
#define NumberOfNodes 12
#define NilValue -1

typedef int ListElementType_A;

typedef struct {
  int number;
  int frequency;
} ListElementType_B;

typedef int ListPointer;

typedef struct {
  ListElementType_A Data;
  ListPointer Next;
} NodeType_A;

typedef struct {
  ListElementType_B Data;
  ListPointer Next;
} NodeType_B;

typedef enum { FALSE, TRUE } boolean;

// A
void InitializeStoragePool_A(NodeType_A Node[], ListPointer *FreePtr);
void CreateList_A(ListPointer *List);
boolean EmptyList_A(ListPointer List);
boolean FullList_A(ListPointer FreePtr);
void GetNode_A(ListPointer *P, ListPointer *FreePtr, NodeType_A Node[]);
void ReleaseNode_A(NodeType_A Node[NumberOfNodes], ListPointer P,
                   ListPointer *FreePtr);
void Insert_A(ListPointer *List, NodeType_A Node[], ListPointer *FreePtr,
              ListPointer PredPtr, ListElementType_A Item);
void Delete_A(ListPointer *List, NodeType_A Node[], ListPointer *FreePtr,
              ListPointer PredPtr);
void TraverseLinked_A(ListPointer List, NodeType_A Node[]);
// B
void InitializeStoragePool_B(NodeType_B Node[], ListPointer *FreePtr);
void CreateList_B(ListPointer *List);
boolean EmptyList_B(ListPointer List);
boolean FullList_B(ListPointer FreePtr);
void GetNode_B(ListPointer *P, ListPointer *FreePtr, NodeType_B Node[]);
void ReleaseNode_B(NodeType_B Node[NumberOfNodes], ListPointer P,
                   ListPointer *FreePtr);
void Insert_B(ListPointer *List, NodeType_B Node[], ListPointer *FreePtr,
              ListPointer PredPtr, ListElementType_B Item);
void Delete_B(ListPointer *List, NodeType_B Node[], ListPointer *FreePtr,
              ListPointer PredPtr);
void TraverseLinked_B(ListPointer List, NodeType_B Node[]);

void GetFrequencies(ListPointer *List, NodeType_A Node_A[], NodeType_B Node_B[],
                    ListPointer *FreePtr, ListPointer PredPtr,
                    int observations);

int main() {
  // 0
  ListElementType_A Item_A;
  ListPointer List_A, FreePtr_A, PredPtr_A = NilValue;
  ListPointer List_B, FreePtr_B, PredPtr_B = NilValue;
  NodeType_A Node_A[NumberOfNodes];
  NodeType_B Node_B[NumberOfNodes];
  // 1
  InitializeStoragePool_A(Node_A, &FreePtr_A);
  InitializeStoragePool_B(Node_B, &FreePtr_B);
  // 2
  CreateList_A(&List_A);
  CreateList_B(&List_B);
  //
  int i, observations, number;
  do {
    printf("Enter observations number: ");
    scanf("%d", &observations);
  } while (!(observations >= 0 &&
             observations <= observations_limit));  // >= ﬁ > ·Ô ÙÔ 0?
  for (i = 0; i < observations; i++) {
    do {
      printf("Enter an observation in [0,9]: ");
      scanf("%d", &number);
    } while (!(number >= 0 && number <= 9));
    Item_A = number;
    Insert_A(&List_A, Node_A, &FreePtr_A, PredPtr_A, Item_A);
  }
  //
  printf("\n");
  printf("1h Lista Parathrhsewn\n");
  TraverseLinked_A(List_A, Node_A);
  //
  GetFrequencies(&List_B, Node_A, Node_B, &FreePtr_B, PredPtr_B, observations);
  //
  printf("\n");
  printf("2h Lista Syxnothtwn\n");
  TraverseLinked_B(List_B, Node_B);
  return 0;
}

void GetFrequencies(ListPointer *List, NodeType_A Node_A[], NodeType_B Node_B[],
                    ListPointer *FreePtr, ListPointer PredPtr,
                    int observations) {
  int i;
  ListElementType_B Item;
  for (i = 0; i < 10; i++) {
    Item.number = i;
    Item.frequency = 0;
    Insert_B(List, Node_B, FreePtr, PredPtr, Item);
  }
  for (i = 0; i < observations; i++) {
    Node_B[Node_A[i].Data].Data.frequency++;
  }
}
// A
void InitializeStoragePool_A(NodeType_A Node[], ListPointer *FreePtr) {
  int i;

  for (i = 0; i < NumberOfNodes - 1; i++) {
    Node[i].Next = i + 1;
    Node[i].Data = -1;
  }
  Node[NumberOfNodes - 1].Next = NilValue;
  Node[NumberOfNodes - 1].Data = -1;
  *FreePtr = 0;
}

void CreateList_A(ListPointer *List) { *List = NilValue; }

boolean EmptyList_A(ListPointer List) { return (List == NilValue); }

boolean FullList_A(ListPointer FreePtr) { return (FreePtr == NilValue); }

void GetNode_A(ListPointer *P, ListPointer *FreePtr, NodeType_A Node[]) {
  *P = *FreePtr;
  if (!FullList_A(*FreePtr)) *FreePtr = Node[*FreePtr].Next;
}

void ReleaseNode_A(NodeType_A Node[], ListPointer P, ListPointer *FreePtr) {
  Node[P].Next = *FreePtr;
  Node[P].Data = -1;
  *FreePtr = P;
}

void Insert_A(ListPointer *List, NodeType_A Node[], ListPointer *FreePtr,
              ListPointer PredPtr, ListElementType_A Item) {
  ListPointer TempPtr;
  GetNode_A(&TempPtr, FreePtr, Node);
  if (!FullList_A(TempPtr)) {
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

void Delete_A(ListPointer *List, NodeType_A Node[], ListPointer *FreePtr,
              ListPointer PredPtr) {
  ListPointer TempPtr;

  if (!EmptyList_A(*List)) {
    if (PredPtr == NilValue) {
      TempPtr = *List;
      *List = Node[TempPtr].Next;
    } else {
      TempPtr = Node[PredPtr].Next;
      Node[PredPtr].Next = Node[TempPtr].Next;
    }
    ReleaseNode_A(Node, TempPtr, FreePtr);
  } else
    printf("Empty List ...\n");
}

void TraverseLinked_A(ListPointer List, NodeType_A Node[]) {
  ListPointer CurrPtr;

  if (!EmptyList_A(List)) {
    CurrPtr = List;
    while (CurrPtr != NilValue) {
      printf("(%d) ", Node[CurrPtr].Data);
      CurrPtr = Node[CurrPtr].Next;
    }
    printf("\n");
  } else
    printf("Empty List ...\n");
}
// B
void InitializeStoragePool_B(NodeType_B Node[], ListPointer *FreePtr) {
  int i;

  for (i = 0; i < NumberOfNodes - 1; i++) {
    Node[i].Next = i + 1;
    Node[i].Data.number = -1;
    Node[i].Data.frequency = -1;
  }
  Node[NumberOfNodes - 1].Next = NilValue;
  Node[NumberOfNodes - 1].Data.number = -1;
  Node[NumberOfNodes - 1].Data.frequency = -1;
  *FreePtr = 0;
}

void CreateList_B(ListPointer *List) { *List = NilValue; }

boolean EmptyList_B(ListPointer List) { return (List == NilValue); }

boolean FullList_B(ListPointer FreePtr) { return (FreePtr == NilValue); }

void GetNode_B(ListPointer *P, ListPointer *FreePtr, NodeType_B Node[]) {
  *P = *FreePtr;
  if (!FullList_B(*FreePtr)) *FreePtr = Node[*FreePtr].Next;
}

void ReleaseNode_B(NodeType_B Node[], ListPointer P, ListPointer *FreePtr)

{
  Node[P].Next = *FreePtr;
  Node[P].Data.number = -1;
  Node[P].Data.frequency = -1;
  *FreePtr = P;
}

void Insert_B(ListPointer *List, NodeType_B Node[], ListPointer *FreePtr,
              ListPointer PredPtr, ListElementType_B Item) {
  ListPointer TempPtr;
  GetNode_B(&TempPtr, FreePtr, Node);
  if (!FullList_B(TempPtr)) {
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

void Delete_B(ListPointer *List, NodeType_B Node[], ListPointer *FreePtr,
              ListPointer PredPtr) {
  ListPointer TempPtr;

  if (!EmptyList_B(*List)) {
    if (PredPtr == NilValue) {
      TempPtr = *List;
      *List = Node[TempPtr].Next;
    } else {
      TempPtr = Node[PredPtr].Next;
      Node[PredPtr].Next = Node[TempPtr].Next;
    }
    ReleaseNode_B(Node, TempPtr, FreePtr);
  } else
    printf("Empty List ...\n");
}

void TraverseLinked_B(ListPointer List, NodeType_B Node[]) {
  ListPointer CurrPtr;

  if (!EmptyList_B(List)) {
    CurrPtr = List;
    while (CurrPtr != NilValue) {
      printf("(%d:%d) ", Node[CurrPtr].Data.number,
             Node[CurrPtr].Data.frequency);
      CurrPtr = Node[CurrPtr].Next;
    }
    printf("\n");
  } else
    printf("Empty List ...\n");
}

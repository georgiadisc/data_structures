#include <stdio.h>
#include <stdlib.h>

typedef int ListElementType;

typedef struct ListNode *ListPointer;

typedef struct ListNode {
  ListElementType Data;
  ListPointer Next;
} ListNode;

typedef enum { FALSE, TRUE } boolean;

void CreateList(ListPointer *List);
boolean EmptyList(ListPointer List);
void LinkedInsert(ListPointer *List, ListElementType Item, ListPointer PredPtr);
void LinkedDelete(ListPointer *List, ListPointer PredPtr);
void LinkedTraverse(ListPointer List);
void LinearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr,
                  boolean *Found);
void OrderedLinearSearch(ListPointer List, ListElementType Item,
                         ListPointer *PredPtr, boolean *Found);

void UniqueList(ListPointer InList, ListPointer *OutList);

int main() {
  ListPointer List, PredPtr, FinalList;
  int number, i;
  ListElementType Item;

  CreateList(&List);
  printf("DWSE TON PLH8OS TWN STOIXEIWN THS LISTAS: ");
  scanf("%d", &number);

  PredPtr = NULL;

  for (i = 0; i < number; i++) {
    printf("DWSE TON ARI8MO GIA EISAGWGH STH ARXH THS LISTAS: ");
    scanf("%d", &Item);
    LinkedInsert(&List, Item, PredPtr);
  }

  printf("Arxiki lista\n");
  LinkedTraverse(List);

  UniqueList(List, &FinalList);

  printf("Teliki lista\n");
  LinkedTraverse(FinalList);

  return 0;
}

void CreateList(ListPointer *List) { *List = NULL; }

boolean EmptyList(ListPointer List) { return (List == NULL); }

void LinkedInsert(ListPointer *List, ListElementType Item,
                  ListPointer PredPtr) {
  ListPointer TempPtr;

  TempPtr = (ListPointer)malloc(sizeof(struct ListNode));
  TempPtr->Data = Item;
  if (PredPtr == NULL) {
    TempPtr->Next = *List;
    *List = TempPtr;
  } else {
    TempPtr->Next = PredPtr->Next;
    PredPtr->Next = TempPtr;
  }
}

void LinkedDelete(ListPointer *List, ListPointer PredPtr) {
  ListPointer TempPtr;

  if (EmptyList(*List))
    printf("EMPTY LIST\n");
  else {
    if (PredPtr == NULL) {
      TempPtr = *List;
      *List = TempPtr->Next;
    } else {
      TempPtr = PredPtr->Next;
      PredPtr->Next = TempPtr->Next;
    }
    free(TempPtr);
  }
}

void LinkedTraverse(ListPointer List) {
  ListPointer CurrPtr;

  if (EmptyList(List))
    printf("EMPTY LIST\n");
  else {
    CurrPtr = List;
    while (CurrPtr != NULL) {
      printf("%d ", (*CurrPtr).Data);
      CurrPtr = CurrPtr->Next;
    }
  }
  printf("\n");
}

void LinearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr,
                  boolean *Found) {
  ListPointer CurrPtr;
  boolean stop;

  CurrPtr = List;
  *PredPtr = NULL;
  stop = FALSE;
  while (!stop && CurrPtr != NULL) {
    if (CurrPtr->Data == Item)
      stop = TRUE;
    else {
      *PredPtr = CurrPtr;
      CurrPtr = CurrPtr->Next;
    }
  }
  *Found = stop;
}

void OrderedLinearSearch(ListPointer List, ListElementType Item,
                         ListPointer *PredPtr, boolean *Found) {
  ListPointer CurrPtr;
  boolean DoneSearching;

  CurrPtr = List;
  *PredPtr = NULL;
  DoneSearching = FALSE;
  *Found = FALSE;
  while (!DoneSearching && CurrPtr != NULL) {
    if (CurrPtr->Data >= Item) {
      DoneSearching = TRUE;
      *Found = (CurrPtr->Data == Item);
    } else {
      *PredPtr = CurrPtr;
      CurrPtr = CurrPtr->Next;
    }
  }
}

void UniqueList(ListPointer InList, ListPointer *OutList) {
  ListPointer CurrPtr, LastPtr;

  if (!EmptyList(InList)) {
    CreateList(OutList);
    CurrPtr = InList;
    LastPtr = *OutList;

    LinkedInsert(OutList, CurrPtr->Data, LastPtr);

    CurrPtr = CurrPtr->Next;
    LastPtr = *OutList;

    while (!EmptyList(CurrPtr)) {
      if (CurrPtr->Data != LastPtr->Data) {
        LinkedInsert(OutList, CurrPtr->Data, LastPtr);
        LastPtr = LastPtr->Next;
      }
      CurrPtr = CurrPtr->Next;
    }
  } else {
    printf("Empty List\n");
  }
}

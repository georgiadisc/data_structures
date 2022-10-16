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

void delete_n_element(ListPointer *List, int n);

int main() {
  ListPointer List, PredPtr;
  ListElementType Item;

  int i, n, pos;

  CreateList(&List);
  printf("DWSE TON PLH8OS TWN STOIXEIWN THS LISTAS: ");
  scanf("%d", &n);

  for (i = 0; i < n; i++) {
    printf("DWSE TON ARI8MO GIA EISAGWGH STH ARXH THS LISTAS: ");
    scanf("%d", &Item);
    PredPtr = NULL;
    LinkedInsert(&List, Item, PredPtr);
  }

  printf("DWSE TI THESI GIA DIAGRAFI TOY STOIXEIOU: ");
  scanf("%d", &pos);

  printf("Arxiki lista\n");
  LinkedTraverse(List);

  delete_n_element(&List, pos);

  printf("Teliki lista\n");
  LinkedTraverse(List);
  return 0;
}

void delete_n_element(ListPointer *List, int n) {
  ListPointer TempPtr, PrevPtr;

  int i;

  if (!EmptyList(*List)) {
    if (n == 1) {
      TempPtr = *List;
      *List = TempPtr->Next;
    } else {
      i = 2;
      PrevPtr = *List;
      TempPtr = PrevPtr->Next;
      while (i < n) {
        PrevPtr = TempPtr;
        TempPtr = TempPtr->Next;
        i++;
      }
      PrevPtr->Next = TempPtr->Next;
    }
    free(TempPtr);
  } else {
    printf("Empty List \n");
  }
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

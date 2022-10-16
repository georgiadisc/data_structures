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

void intersection_list(ListPointer AList, ListPointer BList,
                       ListPointer *FinalList);

int main() {
  ListPointer AList, BList, FinalList, PredPtr;
  ListElementType Item;

  int num, i;

  CreateList(&AList);
  PredPtr = NULL;

  printf("DWSE TON PLH8OS TWN STOIXEIWN THS LISTAS 1: ");
  scanf("%d", &num);
  for (i = 0; i < num; i++) {
    printf("DWSE TON ARI8MO GIA EISAGWGH STH ARXH THS LISTAS 1: ");
    scanf("%d", &Item);
    LinkedInsert(&AList, Item, PredPtr);
  }

  CreateList(&BList);
  PredPtr = NULL;

  printf("DWSE TON PLH8OS TWN STOIXEIWN THS LISTAS : ");
  scanf("%d", &num);
  for (i = 0; i < num; i++) {
    printf("DWSE TON ARI8MO GIA EISAGWGH STH ARXH THS LISTAS 2: ");
    scanf("%d", &Item);
    LinkedInsert(&BList, Item, PredPtr);
  }

  printf("1h lista\n");
  LinkedTraverse(AList);

  printf("2h lista\n");
  LinkedTraverse(BList);

  intersection_list(AList, BList, &FinalList);

  printf("Teliki lista\n");
  LinkedTraverse(FinalList);

  return 0;
}

void intersection_list(ListPointer AList, ListPointer BList,
                       ListPointer *FinalList) {
  ListPointer ACurrPtr, PredPtr, BCurrPtr, Temp;
  boolean Found;
  ListElementType Item;

  CreateList(FinalList);
  ACurrPtr = AList;

  while (!(EmptyList(ACurrPtr))) {
    BCurrPtr = BList;
    Found = FALSE;
    while ((!(EmptyList(BCurrPtr))) && (Found == FALSE)) {
      if (ACurrPtr->Data == BCurrPtr->Data) {
        Item = ACurrPtr->Data;
        PredPtr = NULL;
        LinearSearch(*FinalList, Item, &PredPtr, &Found);
        if (Found == FALSE) {
          Temp = NULL;
          LinkedInsert(&(*FinalList), Item, Temp);
          Found = TRUE;
        }
      }
      BCurrPtr = BCurrPtr->Next;
    }
    ACurrPtr = ACurrPtr->Next;
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
    printf("\n");
  }
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

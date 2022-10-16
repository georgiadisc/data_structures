#include <stdio.h>
#include <stdlib.h>

typedef char BinTreeElementType;

typedef struct BinTreeNode *BinTreePointer;
typedef struct BinTreeNode {
  BinTreeElementType Data;
  BinTreePointer LChild, RChild;
} BinTreeNode;

typedef enum { FALSE, TRUE } boolean;

void CreateBST(BinTreePointer *Root);
boolean BSTEmpty(BinTreePointer Root);
void RecBSTInsert(BinTreePointer *Root, BinTreeElementType Item);
void RecBSTSearch(BinTreePointer Root, BinTreeElementType KeyValue,
                  boolean *Found, BinTreePointer *LocPtr);
void RecBSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue);
void RecBSTInorder(BinTreePointer Root);
void RecBSTPreorder(BinTreePointer Root);
void RecBSTPostorder(BinTreePointer Root);

boolean IdenticalBSTs(BinTreePointer Root1, BinTreePointer Root2);

int main() {
  BinTreePointer ARoot, BRoot, CRoot;
  char word1[] = "IDENTICAL";
  char word2[] = "DIFFERENT";
  int i;

  CreateBST(&ARoot);
  CreateBST(&BRoot);
  CreateBST(&CRoot);

  for (i = 0; word1[i] != '\0'; i++) {
    RecBSTInsert(&ARoot, word1[i]);
    RecBSTInsert(&BRoot, word1[i]);
  }

  for (i = 0; word2[i] != '\0'; i++) {
    RecBSTInsert(&CRoot, word2[i]);
  }

  if (IdenticalBSTs(ARoot, BRoot))
    printf("Ta dyadika dentra A kai B einai idia\n");
  else
    printf("Ta dyadika dentra A kai B diafferoun\n");

  if (IdenticalBSTs(BRoot, CRoot))
    printf("Ta dyadika dentra B kai C einai idia\n");
  else
    printf("Ta dyadika dentra B kai C diafferoun\n");

  return 0;
}

void CreateBST(BinTreePointer *Root) { *Root = NULL; }

boolean BSTEmpty(BinTreePointer Root) { return (Root == NULL); }

void RecBSTInsert(BinTreePointer *Root, BinTreeElementType Item) {
  if (BSTEmpty(*Root)) {
    (*Root) = (BinTreePointer)malloc(sizeof(struct BinTreeNode));
    (*Root)->Data = Item;
    (*Root)->LChild = NULL;
    (*Root)->RChild = NULL;
  } else if (Item < (*Root)->Data)
    RecBSTInsert(&(*Root)->LChild, Item);
  else if (Item > (*Root)->Data)
    RecBSTInsert(&(*Root)->RChild, Item);
  else
    printf("TO STOIXEIO EINAI HDH STO DDA\n");
}

void RecBSTSearch(BinTreePointer Root, BinTreeElementType KeyValue,
                  boolean *Found, BinTreePointer *LocPtr) {
  if (BSTEmpty(Root))
    *Found = FALSE;
  else if (KeyValue < Root->Data)
    RecBSTSearch(Root->LChild, KeyValue, &(*Found), &(*LocPtr));
  else if (KeyValue > Root->Data)
    RecBSTSearch(Root->RChild, KeyValue, &(*Found), &(*LocPtr));
  else {
    *Found = TRUE;
    *LocPtr = Root;
  }
}

void RecBSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue) {
  BinTreePointer TempPtr;

  if (BSTEmpty(*Root))
    printf("TO STOIXEIO DEN BRE8HKE STO DDA\n");
  else if (KeyValue < (*Root)->Data)
    RecBSTDelete(&((*Root)->LChild), KeyValue);
  else if (KeyValue > (*Root)->Data)
    RecBSTDelete(&((*Root)->RChild), KeyValue);
  else if ((*Root)->LChild == NULL) {
    TempPtr = *Root;
    *Root = (*Root)->RChild;
    free(TempPtr);
  } else if ((*Root)->RChild == NULL) {
    TempPtr = *Root;
    *Root = (*Root)->LChild;
    free(TempPtr);
  } else {
    TempPtr = (*Root)->RChild;
    while (TempPtr->LChild != NULL) TempPtr = TempPtr->LChild;
    (*Root)->Data = TempPtr->Data;
    RecBSTDelete(&((*Root)->RChild), (*Root)->Data);
  }
}

void RecBSTInorder(BinTreePointer Root) {
  if (Root != NULL) {
    //    printf("L");
    RecBSTInorder(Root->LChild);
    printf("%c", Root->Data);
    //    printf("R");
    RecBSTInorder(Root->RChild);
  }
  // printf("U");
}

void RecBSTPreorder(BinTreePointer Root) {
  if (Root != NULL) {
    printf("%c", Root->Data);
    // printf("L");
    RecBSTPreorder(Root->LChild);
    //  printf("R");
    RecBSTPreorder(Root->RChild);
  }
  // printf("U");
}

void RecBSTPostorder(BinTreePointer Root) {
  if (Root != NULL) {
    //  printf("L");
    RecBSTPostorder(Root->LChild);
    //   printf("R");
    RecBSTPostorder(Root->RChild);
    printf("%c", Root->Data);
  }
  // printf("U");
}

boolean IdenticalBSTs(BinTreePointer Root1, BinTreePointer Root2) {
  if (BSTEmpty(Root1) && BSTEmpty(Root2))
    return TRUE;
  else {
    if (!BSTEmpty(Root1) && !BSTEmpty(Root2)) {
      return (Root1->Data == Root2->Data &&
              IdenticalBSTs(Root1->LChild, Root2->LChild) &&
              IdenticalBSTs(Root1->RChild, Root2->RChild));
    } else {
      return FALSE;
    }
  }
}

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
int LeftNodeCount(BinTreePointer Root);

int main() {
  BinTreePointer Root1, Root2;
  char word[] = "ALGORITHM";
  int i;

  CreateBST(&Root1);
  printf("First tree with inorder traverse\n");
  for (i = 0; word[i] != '\0'; i++) {
    RecBSTInsert(&Root1, word[i]);
  }
  RecBSTInorder(Root1);
  printf("\n");

  CreateBST(&Root2);
  printf("Second tree with inorder traverse\n");
  for (i = i - 1; i >= 0; i--) {
    RecBSTInsert(&Root2, word[i]);
  }
  RecBSTInorder(Root2);
  printf("\n");

  printf("First tree LeftNodeCount = %d\n", LeftNodeCount(Root1));
  printf("Second tree LeftNodeCount = %d\n", LeftNodeCount(Root2));

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

int LeftNodeCount(BinTreePointer Root) {
  int lcounter = 0;
  int rcounter = 0;

  if (BSTEmpty(Root)) {
    return 0;
  } else {
    if (Root->LChild != NULL) {
      lcounter = 1 + LeftNodeCount(Root->LChild);
    }
    if (Root->RChild != NULL) {
      rcounter = LeftNodeCount(Root->RChild);
    }
    return lcounter + rcounter;
  }
}

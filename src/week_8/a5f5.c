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
boolean EmptyBST(BinTreePointer Root);
void BSTInsert(BinTreePointer *Root, BinTreeElementType Item);
void BSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found,
               BinTreePointer *LocPtr);
void BSTSearch2(BinTreePointer Root, BinTreeElementType KeyValue,
                boolean *Found, BinTreePointer *LocPtr, BinTreePointer *Parent);
void BSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue);
void InorderTraversal(BinTreePointer Root);

int BSTLevel(BinTreePointer root, BinTreeElementType item);

int main() {
  BinTreePointer ARoot;
  char word[] = "PROGRAMS";
  int i;

  CreateBST(&ARoot);

  for (i = 0; word[i] != '\0'; i++) {
    BSTInsert(&ARoot, word[i]);
  }

  for (i = 0; word[i] != '\0'; i++) {
    if (i != 4) {
      printf("Level of %c: %d\n", word[i], BSTLevel(ARoot, word[i]));
    }
  }

  return 0;
}

int BSTLevel(BinTreePointer root, BinTreeElementType item) {
  BinTreePointer LocPtr;
  int level;

  LocPtr = root;
  level = 1;

  while (LocPtr != NULL) {
    if (item < LocPtr->Data) {
      level++;
      LocPtr = LocPtr->LChild;
    } else if (item > LocPtr->Data) {
      level++;
      LocPtr = LocPtr->RChild;
    } else {
      return level;
    }
  }

  return -1;
}

void CreateBST(BinTreePointer *Root) { *Root = NULL; }

boolean EmptyBST(BinTreePointer Root) { return (Root == NULL); }

void BSTInsert(BinTreePointer *Root, BinTreeElementType Item) {
  BinTreePointer LocPtr, Parent;
  boolean Found;

  LocPtr = *Root;
  Parent = NULL;
  Found = FALSE;
  while (!Found && LocPtr != NULL) {
    Parent = LocPtr;
    if (Item < LocPtr->Data)
      LocPtr = LocPtr->LChild;
    else if (Item > LocPtr->Data)
      LocPtr = LocPtr->RChild;
    else
      Found = TRUE;
  }
  if (Found) {
    printf("TO STOIXEIO EINAI HDH STO DDA\n");
    printf("\n");
  } else {
    LocPtr = (BinTreePointer)malloc(sizeof(struct BinTreeNode));
    LocPtr->Data = Item;
    LocPtr->LChild = NULL;
    LocPtr->RChild = NULL;
    if (Parent == NULL)
      *Root = LocPtr;
    else if (Item < Parent->Data)
      Parent->LChild = LocPtr;
    else
      Parent->RChild = LocPtr;
  }
}

void BSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found,
               BinTreePointer *LocPtr) {
  (*LocPtr) = Root;
  (*Found) = FALSE;
  while (!(*Found) && (*LocPtr) != NULL) {
    if (KeyValue < (*LocPtr)->Data)
      (*LocPtr) = (*LocPtr)->LChild;
    else if (KeyValue > (*LocPtr)->Data)
      (*LocPtr) = (*LocPtr)->RChild;
    else
      (*Found) = TRUE;
  }
}

void BSTSearch2(BinTreePointer Root, BinTreeElementType KeyValue,
                boolean *Found, BinTreePointer *LocPtr,
                BinTreePointer *Parent) {
  *LocPtr = Root;
  *Parent = NULL;
  *Found = FALSE;
  while (!(*Found) && *LocPtr != NULL) {
    if (KeyValue < (*LocPtr)->Data) {
      *Parent = *LocPtr;
      *LocPtr = (*LocPtr)->LChild;
    } else if (KeyValue > (*LocPtr)->Data) {
      *Parent = *LocPtr;
      *LocPtr = (*LocPtr)->RChild;
    } else
      *Found = TRUE;
  }
}

void BSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue) {
  BinTreePointer n, Parent, nNext, SubTree;
  boolean Found;

  BSTSearch2(*Root, KeyValue, &Found, &n, &Parent);
  if (!Found)
    printf("TO STOIXEIO DEN EINAI STO DDA\n");
  else {
    if (n->LChild != NULL && n->RChild != NULL) {
      nNext = n->RChild;
      Parent = n;
      while (nNext->LChild != NULL) {
        Parent = nNext;
        nNext = nNext->LChild;
      }
      n->Data = nNext->Data;
      n = nNext;
    }
    SubTree = n->LChild;
    if (SubTree == NULL) SubTree = n->RChild;
    if (Parent == NULL)
      *Root = SubTree;
    else if (Parent->LChild == n)
      Parent->LChild = SubTree;
    else
      Parent->RChild = SubTree;
    free(n);
  }
}

void InorderTraversal(BinTreePointer Root) {
  if (Root != NULL) {
    InorderTraversal(Root->LChild);
    printf("%d ", Root->Data);
    InorderTraversal(Root->RChild);
  }
}

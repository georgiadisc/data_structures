#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char am[9], name[11], lastname[11];
} BinTreeElementType;

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
               BinTreePointer *LocPtr, int *nodes);
void BSTSearch2(BinTreePointer Root, BinTreeElementType KeyValue,
                boolean *Found, BinTreePointer *LocPtr, BinTreePointer *Parent);
void BSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue);
void InorderTraversal(BinTreePointer Root);

void BuildBST(BinTreePointer *Root);

int main() {
  BinTreePointer ARoot, LocPtr;
  int nodes, i;
  BinTreeElementType student;
  boolean found;

  BuildBST(&ARoot);

  for (i = 0; i < 3; i++) {
    printf("Give am:");
    scanf("%s", student.am);

    BSTSearch(ARoot, student, &found, &LocPtr, &nodes);
    if (found) {
      printf("komboi=%d AM=%s Onoma=%s Epwnymo=%s\n", nodes, LocPtr->Data.am,
             LocPtr->Data.name, LocPtr->Data.lastname);
    } else {
      printf("komboi=%d o foithths den brethike sto DDA\n", nodes);
    }
  }
  return 0;
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
    if (strcmp(Item.am, LocPtr->Data.am) < 0)
      LocPtr = LocPtr->LChild;
    else if (strcmp(Item.am, LocPtr->Data.am) > 0)
      LocPtr = LocPtr->RChild;
    else
      Found = TRUE;
  }
  if (Found)
    printf("TO STOIXEIO EINAI HDH STO DDA\n");
  else {
    LocPtr = (BinTreePointer)malloc(sizeof(struct BinTreeNode));
    LocPtr->Data = Item;
    LocPtr->LChild = NULL;
    LocPtr->RChild = NULL;
    if (Parent == NULL)
      *Root = LocPtr;
    else if (strcmp(Item.am, Parent->Data.am) < 0)
      Parent->LChild = LocPtr;
    else
      Parent->RChild = LocPtr;
  }
}

void BSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found,
               BinTreePointer *LocPtr, int *nodes) {
  *nodes = 0;
  (*LocPtr) = Root;
  (*Found) = FALSE;
  while (!(*Found) && (*LocPtr) != NULL) {
    (*nodes)++;
    if (strcmp(KeyValue.am, (*LocPtr)->Data.am) < 0)
      (*LocPtr) = (*LocPtr)->LChild;
    else if (strcmp(KeyValue.am, (*LocPtr)->Data.am) > 0)
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
    if (KeyValue.am < (*LocPtr)->Data.am) {
      *Parent = *LocPtr;
      *LocPtr = (*LocPtr)->LChild;
    } else if (KeyValue.am > (*LocPtr)->Data.am) {
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
    printf("%s ", Root->Data.am);
    InorderTraversal(Root->RChild);
  }
}

void BuildBST(BinTreePointer *Root) {
  int scan;
  char ch;
  BinTreeElementType student;
  CreateBST(Root);
  FILE *fp;
  fp = fopen("i31f5.txt", "r");
  if (fp == NULL)
    printf("problem opening file\n");
  else {
    while (!feof(fp)) {
      scan = fscanf(fp, "%s %s %s%c", student.am, student.name,
                    student.lastname, &ch);
      if (scan != 4) break;
      BSTInsert(Root, student);
    }
  }
  fclose(fp);
}

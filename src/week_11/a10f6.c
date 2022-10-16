#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define HMax 31
#define VMax 30
#define EndOfList -1

typedef struct {
  char name[6];
  int value;
} ListElementType;

typedef int KeyType;

typedef struct {
  KeyType key;
  ListElementType Data;
  int Link;
} ListElm;

typedef struct {
  int HashTable[HMax];
  int Size;
  int SubListPtr;
  int StackPtr;
  ListElm List[VMax];
} HashListType;

typedef enum { FALSE, TRUE } boolean;

void CreateHashList(HashListType *HList);
int HashKey(KeyType key);
boolean FullHashList(HashListType HList);
void SearchSynonymList(HashListType HList, KeyType KeyArg, int *Loc, int *Pred);
void SearchHashList(HashListType HList, KeyType KeyArg, int *Loc, int *Pred);
void AddRec(HashListType *HList, ListElm InRec);
void DeleteRec(HashListType *HList, KeyType DelKey);
int FoldKey(char s[]);
void Print_HashList(HashListType HList);

int main() {
  HashListType HList;
  ListElm Item, ItemA, ItemB;
  int LocA, LocB, PrevA, PrevB;
  int i, result;

  CreateHashList(&HList);

  printf("Declare variables\n");
  for (i = 0; i < 4; i++) {
    printf("Enter the variable name: ");
    scanf("%s", Item.Data.name);
    printf("Enter the variable value: ");
    scanf("%d", &Item.Data.value);
    Item.key = FoldKey(Item.Data.name);
    AddRec(&HList, Item);
  }

  Print_HashList(HList);

  printf("Multiply Variables\n");

  printf("Enter the first variable: ");
  scanf("%s", ItemA.Data.name);
  ItemA.key = FoldKey(ItemA.Data.name);
  SearchHashList(HList, ItemA.key, &LocA, &PrevA);

  printf("Enter the second variable: ");
  scanf("%s", ItemB.Data.name);
  ItemB.key = FoldKey(ItemB.Data.name);
  SearchHashList(HList, ItemB.key, &LocB, &PrevB);

  if (LocA != -1 && LocB != -1) {
    if (strcmp(HList.List[LocA].Data.name, ItemA.Data.name) == 0 &&
        strcmp(HList.List[LocB].Data.name, ItemB.Data.name) == 0) {
      result = HList.List[LocA].Data.value * HList.List[LocB].Data.value;
      printf("%s*%s=%d\n", HList.List[LocA].Data.name,
             HList.List[LocB].Data.name, result);
    } else {
      if (strcmp(HList.List[LocA].Data.name, ItemA.Data.name) != 0) {
        printf("Undeclared variable %s\n", ItemA.Data.name);
      }
      if (strcmp(HList.List[LocB].Data.name, ItemB.Data.name) != 0) {
        printf("Undeclared variable %s\n", ItemB.Data.name);
      }
    }
  } else {
    if (LocA == -1) {
      printf("Undeclared variable %s\n", ItemA.Data.name);
    }
    if (LocB == -1) {
      printf("Undeclared variable %s\n", ItemB.Data.name);
    }
  }

  printf("Add Variables\n");

  printf("Enter the first variable: ");
  scanf("%s", ItemA.Data.name);
  ItemA.key = FoldKey(ItemA.Data.name);
  SearchHashList(HList, ItemA.key, &LocA, &PrevA);

  printf("Enter the second variable: ");
  scanf("%s", ItemB.Data.name);
  ItemB.key = FoldKey(ItemB.Data.name);
  SearchHashList(HList, ItemB.key, &LocB, &PrevB);

  if (LocA != -1 && LocB != -1) {
    if (strcmp(HList.List[LocA].Data.name, ItemA.Data.name) == 0 &&
        strcmp(HList.List[LocB].Data.name, ItemB.Data.name) == 0) {
      result = HList.List[LocA].Data.value + HList.List[LocB].Data.value;
      printf("%s+%s=%d\n", HList.List[LocA].Data.name,
             HList.List[LocB].Data.name, result);
    } else {
      if (strcmp(HList.List[LocA].Data.name, ItemA.Data.name) != 0) {
        printf("Undeclared variable %s\n", ItemA.Data.name);
      }
      if (strcmp(HList.List[LocB].Data.name, ItemB.Data.name) != 0) {
        printf("Undeclared variable %s\n", ItemB.Data.name);
      }
    }
  } else {
    if (LocA == -1) {
      printf("Undeclared variable %s\n", ItemA.Data.name);
    }
    if (LocB == -1) {
      printf("Undeclared variable %s\n", ItemB.Data.name);
    }
  }

  return 0;
}

int HashKey(KeyType key) { return key % HMax; }

void CreateHashList(HashListType *HList) {
  int index;

  HList->Size = 0;
  HList->StackPtr = 0;

  index = 0;
  while (index < HMax) {
    HList->HashTable[index] = EndOfList;
    index = index + 1;
  }

  index = 0;
  while (index < VMax - 1) {
    HList->List[index].Link = index + 1;
    index = index + 1;
  }
  HList->List[index].Link = EndOfList;
}

boolean FullHashList(HashListType HList) { return (HList.Size == VMax); }

void SearchSynonymList(HashListType HList, KeyType KeyArg, int *Loc,
                       int *Pred) {
  int Next;
  Next = HList.SubListPtr;
  *Loc = -1;
  *Pred = -1;
  while (Next != EndOfList) {
    if (HList.List[Next].key == KeyArg) {
      *Loc = Next;
      Next = EndOfList;
    } else {
      *Pred = Next;
      Next = HList.List[Next].Link;
    }
  }
}
void SearchHashList(HashListType HList, KeyType KeyArg, int *Loc, int *Pred) {
  int HVal;
  HVal = HashKey(KeyArg);
  if (HList.HashTable[HVal] == EndOfList) {
    *Pred = -1;
    *Loc = -1;
  } else {
    HList.SubListPtr = HList.HashTable[HVal];
    SearchSynonymList(HList, KeyArg, Loc, Pred);
  }
}

void AddRec(HashListType *HList, ListElm InRec) {
  int Loc, Pred, New, HVal;

  if (!(FullHashList(*HList))) {
    Loc = -1;
    Pred = -1;
    SearchHashList(*HList, InRec.key, &Loc, &Pred);
    if (Loc == -1) {
      HList->Size = HList->Size + 1;
      New = HList->StackPtr;
      HList->StackPtr = HList->List[New].Link;
      HList->List[New] = InRec;
      if (Pred == -1) {
        HVal = HashKey(InRec.key);
        HList->HashTable[HVal] = New;
        HList->List[New].Link = EndOfList;
      } else {
        HList->List[New].Link = HList->List[Pred].Link;
        HList->List[Pred].Link = New;
      }
    }

    else {
      printf("YPARXEI HDH EGGRAFH ME TO IDIO KLEIDI \n");
    }
  } else {
    printf("Full list...");
  }
}
void DeleteRec(HashListType *HList, KeyType DelKey) {
  int Loc, Pred, HVal;

  SearchHashList(*HList, DelKey, &Loc, &Pred);
  if (Loc != -1) {
    if (Pred != -1) {
      HList->List[Pred].Link = HList->List[Loc].Link;
    } else {
      HVal = HashKey(DelKey);
      HList->HashTable[HVal] = HList->List[Loc].Link;
    }
    HList->List[Loc].Link = HList->StackPtr;
    HList->StackPtr = Loc;
    HList->Size = HList->Size - 1;
  } else {
    printf("DEN YPARXEI  EGGRAFH ME KLEIDI %d \n", DelKey);
  }
}

int FoldKey(char s[]) {
  int i, sum = 0;

  for (i = 0; s[i] != '\0'; i++) {
    sum += (i + 1) * (s[i] - 65 + 1);
  }

  return sum;
}

void Print_HashList(HashListType HList) {
  int i, SubIndex;

  for (i = 0; i < HMax; i++) {
    SubIndex = HList.HashTable[i];
    while (SubIndex != EndOfList) {
      printf("[%d, %s %d, %d]", HList.List[SubIndex].key,
             HList.List[SubIndex].Data.name, HList.List[SubIndex].Data.value,
             HList.List[SubIndex].Link);
      printf(" -> ");
      SubIndex = HList.List[SubIndex].Link;
      printf("TELOS % dHS YPO-LISTAS\n", i);
    }
  }
}

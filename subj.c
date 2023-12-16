#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "subj.h"


struct Base *Create(enum ItemType type) {
  struct Base *base = NULL;
  switch (type) {
    case Detail:
      base = (struct Base*)calloc(1, sizeof(struct Detail));
      break;
    case FurnitureSet:
      base = (struct Base *)calloc(1, sizeof(struct FurnitureSet));
      break;
    case None:
      printf("\nWrong item type!\n\n");
      break;
  }
  if (base) base->type = type;
  return base;
}

void InputDetail(struct Detail* detail) {
  printf("%d\n\n", detail->type);
  do {
    printf("Enter detail name:\n> ");
    detail->name = (char *)malloc(sizeof(char) * 100);
    scanf(" %100[^\n]", detail->name);
    if (detail->name != NULL)
      break;
    printf("Wrong input!\n");
    fflush(stdin);
  } while (1);
  do {
    printf("Enter detail length (mm):\n> ");
    if (scanf("%lf", &detail->length)) break;
    else printf("Wrong input!\n");
    fflush(stdin);
  } while (1);
  do {
    printf("Enter detail width (mm):\n> ");
    if (scanf("%lf", &detail->width)) break;
    else printf("Wrong input!\n");
    fflush(stdin);
  } while (1);
  do {
    printf("Enter detail code:\n> ");
    if (scanf("%d", &detail->code)) break;
    else printf("Wrong input!\n");
    fflush(stdin);
  } while (1);
  do {
    printf("Enter detail materil:\n> ");
    detail->material = (char *)malloc(sizeof(char) * 100);
    scanf(" %100[^\n]", detail->material);
    if (detail->material != NULL) 
        break;
    printf("Wrong input!\n");
    fflush(stdin);
  } while (1);
}

void InputFurnitureSet(struct FurnitureSet* furnitureSet) {
  if (!furnitureSet)
    return;

  do {
    fflush(stdin);
    printf("Enter furniture name:\n> ");
    furnitureSet->name = (char *)malloc(sizeof(char) * 100);
    scanf(" %100[^\n]", furnitureSet->name);
    if (furnitureSet->name != NULL)
      break;
    printf("Wrong input!\n");
  } while (1);
  do {
    printf("Enter code:\n> ");
    if (scanf("%d", &furnitureSet->code)) break;
    else printf("Wrong input!\n");
    fflush(stdin);
  } while (1);
  do {
    printf("Enter furniture quantity:\n> ");
    if (scanf("%d", &furnitureSet->quantity)) break;
    else printf("Wrong input!\n");
    fflush(stdin);
  } while (1);

}

void InputItem(struct Base* base) {
  if (!base)
    return;

  switch (base->type) {
    case Detail:
      InputDetail((struct Detail*)base);
      break;
    case FurnitureSet:
      InputFurnitureSet((struct FurnitureSet*)base);
      break;
    default:
      printf("Unknown object type!\n");
      break;
  }
}

void PrintDetail(struct Detail* detail) {
  printf("Name: %s\t Code: %lf\n", detail->name, detail->code);
  printf("Length: %lg\t Width: %lg\n", detail->length, detail->width);
  printf("Apparent magnitude: %s\n\n", detail->material);
}

void PrintFurnitureSet(struct FurnitureSet* furnitureSet) {
  printf("Name: %s\t Code: %lf\n", furnitureSet->name, furnitureSet->code);
  printf("quantity: %d\n\n", furnitureSet->quantity);
}

void PrintItem(struct Base *base) {
  if (!base)
    return;

  switch (base->type) {
    case Detail:
      PrintDetail((struct Detail*)base);
      break;
    case FurnitureSet:
      PrintFurnitureSet((struct FurnitureSet*)base);
      break;
  }
}

void PrintSpaceItems(struct List* list) {
  struct Base* curr;
  int i = 0;
  for (curr = (struct Base*)list->head; curr != NULL; curr = (struct Base*)curr->next) {
    printf("%d\t%p\t%p\t%p\n", i, curr, curr->prev, curr->next);
    PrintItem(curr);
    i++;
  }
  printf("\n");
}

struct Base *SearchByName(struct List* list, char *name) {
  struct Base* curr;
  for (curr = (struct Base*)list->head; curr != NULL; curr = (struct Base*)curr->next) {
    if (!strcmp(name, curr->name)) {
      return curr;
    }
  }
}

void SearchByCode(struct List* list, double start, double end) {
  struct Base* curr;
  int i = 0;
  for (curr = (struct Base*)list->head; curr != NULL; curr = (struct Base*)curr->next) {
    if (curr->type == Detail) {
      int code = ((struct Detail*)curr)->code;
      if (code >= start && code <= end) {
        printf("\n%d.\n", i);
        PrintItem(curr);
        i++;
      }
    }
  }
}

void Swap(struct List *list, int i1) {
  struct Item *tmp1 = Remove(list, i1);
  Insert(list, tmp1, i1 + 1);
}

int Compare(struct Base* curr) {
  if ((curr->type == Detail && ((struct Base*)curr->next)->type == Detail && strcmp(curr->name, ((struct Base*)curr->next)->name) > 0) ||
    (curr->type == FurnitureSet && ((struct Base*)curr->next)->type == FurnitureSet && strcmp(curr->name, ((struct Base*)curr->next)->name) > 0))
    return 1;
  else
    return 0;
}

void SortList(struct List *list) {
  struct Base *curr, *currDet, *tmp;
  
  int swapped = 1;
  for (int i = 0; i < Count(list); i++) {
    if (swapped == 0)
      break;

    swapped = 0;
    for (curr = (struct Base*)list->head; curr != NULL; curr = ((struct Base*)curr->next)) {  
      if (curr->next != NULL) {
        if (Compare(curr)) {
          Swap(list, GetIndex(list, (struct Item*)curr));
          swapped = 1;
          if (curr->prev != NULL)
            curr = ((struct Base*)curr->prev);
        }
      } else {
        break;
      }
    }
  }

  int count;
  curr = (struct Base*)list->head;
  currDet = (struct Base*)list->head;
  for (int i = 0; i < Count(list); i++) {
    if (currDet->type == Detail) {
      count = 0;
      curr = (struct Base*)currDet->next;
      for (int j = i + 1; j < Count(list); j++) {
        if (curr->type != FurnitureSet) {
          curr = (struct Base*)curr->next;
          continue;
        }
        if (((struct FurnitureSet*)curr)->code == currDet->code) {
          tmp = (struct Base*)curr->next;
          curr = (struct Base*)Remove(list, j);
          Insert(list, (struct Item*)curr, i + count + 1);
          curr = tmp;
          count++;
        } else {
          curr = (struct Base*)curr->next;
        }
      }
    }
    currDet = (struct Base*)currDet->next;
  }
}
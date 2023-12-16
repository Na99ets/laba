#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "List.h"

void Add(struct List *L, struct Item *I){
   if(L->head == NULL){
    L->head = I;
    L->tail = I;
    I->next = NULL;
    I->prev = NULL;
   } 
   else{
    L->tail->next = I;
    I->prev = L->tail;
    L->tail = I;
    I->next = NULL;
   }
}
int Count(struct List *L) {
   int count = 0;
   struct Item *I = L->head;
   while (I != NULL) {
      I = I->next;
      count++;
   }
   return count;
}
void PrintList(struct List *L) {
   if (Count(L) == 0){
      printf("List is null");
   }
   else {
      int count = 1;
      struct Item *I = L->head;
      while (I != NULL) {
         printf("%d\t%p\t%p\t%p\n", count, I, I->prev, I->next);
         I = I->next;
         count++;
      }
   }
}

struct Item* GetItem(struct List *L, int id) {
   int count = 0;
   struct Item *I = L->head;
   while (I != NULL) {
      if (count == id)
         break;
      count++;
   }
   return I;
}

int GetIndex(struct List *L, struct Item *item) {
   int id = 1;
   struct Item *I = L->head;
   while (I != NULL) {
      if (item == I)
         break;
      id++;
   }
   return id;
}

void Insert(struct List *L, struct Item *I,  int id) {
   struct Item *ItemInID = GetItem(L, id);
   if(ItemInID == NULL){
      Add(L, I);
   }
   else if(id == 0) {
      L->head->prev = I;
      I->next = L->head;
      L->head = I;
      I->prev = NULL;
   }
   else {
      I->next = ItemInID;
      I->prev = ItemInID->prev;
      ItemInID->prev->next = I;
      ItemInID->prev = I;
   }
}

struct Item* Remove(struct List *L, int id) {
   struct Item *I = GetItem(L, id);
   if (I == NULL) {
      return NULL;
   }
   else if (L->head == L->tail) {
      L->head = NULL;
      L->tail = NULL;
   }
   else if(I == L->head) {
      L->head = L->head->next;
      L->head->prev = NULL;
   }
   else if (I == L->tail) {
      L->tail = L->tail->prev;
      L->tail->next = NULL;
   }
   else {
      I->prev->next = I->next;
      I->next->prev = I->prev;
   }
   return I;
}

void Delete(struct List *L, int id) {
   struct Item *I = Remove(L, id);
   if(I)
      free(I);
}

void Clear(struct List *L) {
   while (L->head != NULL) {
      Delete(L, 1);
   }
   
}
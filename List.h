#ifndef LIST_H
#define LIST_H

#include "Item.h"

struct List
{
    struct Item *head;
    struct Item *tail;
};

void Add(struct List*, struct Item*);
int Count(struct List*);
void PrintList(struct List *L);
struct Item* GetItem(struct List *L, int id);
int GetIndex(struct List *L, struct Item *item);
void Insert(struct List *L, struct Item *I,  int id);
struct Item* Remove(struct List *L, int id);
void Delete(struct List *L, int id);
void Clear(struct List *L);

#endif
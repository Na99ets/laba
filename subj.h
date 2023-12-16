#ifndef SUBJ_H
#define SUBJ_H

#include "list.h"

enum ItemType {None, Detail, FurnitureSet};

struct Base {
  struct Item* next;
  struct Item* prev;
  enum ItemType type;
  char* name;
  int code;
};

struct Detail {
  struct Item* next;
  struct Item* prev;
  enum ItemType type;
  char* name;
  int code; 
  char* material;
  double length;
  double width;
};

struct FurnitureSet {
  struct Item* next;
  struct Item* prev;
  enum ItemType type;
  char* name;
  int code; 
  int quantity;
};

struct Base *Create(enum ItemType);
void InputStar(struct Detail*);
void InputPlanet(struct FurnitureSet*);
void InputItem(struct Base*);
void PrintDetail(struct Detail*);
void PrintFurnitureSet(struct FurnitureSet*);
void PrintItem(struct Base*);
void PrintSpaceItems(struct List*);
struct Base *SearchByName(struct List*, char*);
void SearchByCode(struct List*, double, double);
void SortList(struct List*);

#endif
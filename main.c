#include <stdio.h>
#include <stdlib.h>
#include "subj.h"
#include "List.h"

int DoMenu(char* s[], int len) {
  int i;
  for (i = 1; i <= len; i++) {
    printf("%i. %s\n", i, s[i]);
  }
  printf("> ");
  fflush(stdin);
  scanf("%i", &i);
  return i<0 || i>len ? 0 : i;
}

int main(void) {
  struct List list;
  struct Base* item;
  enum ItemType type;
  char *menuActions[] = {"(none)", "Add Item", "Count", "Print List", "Print Item", "Search By Name", "Search By Code", "Sort List", "Insert", "Delete", "Clear"};
  char *typeNames[] = {"(unknown)", "Detail", "FurnitureSet"};
  
  int buffInt;
  char *buffStr = (char*)calloc(1, sizeof(char) * 100);
  do {
    buffInt = DoMenu(menuActions, 9);
    switch (buffInt) {
      case 1:
        type = DoMenu(typeNames, 2);
        if (type != None) {
          item = Create(type);
          InputItem(item);
          printf("bilo");
          Add(&list, (struct Item*)item);
          printf("Item was added!\n\n");
        } else {
          printf("Wrong item type!\n\n");
        }
        break;
      case 2:
        printf("There\'s %i items in list\n\n", Count(&list));
        break;
      case 3:
        PrintSpaceItems(&list);
        break;
      case 4:
        printf("Enter index: ");
        scanf("%i", &buffInt);
        item = (struct Base*)GetItem(&list, buffInt);
        if (item)
          PrintItem(item);
        break;
      case 5:
        printf("Enter name: ");
        scanf(" %100[^\n]", buffStr);
        SearchByName(&list, buffStr);
        break;
      case 6:
        printf("Enter the interval: ");
        int start, end = -1;
        if (scanf("%d%d", &start, &end) == 2) {
          SearchByCode(&list, start, end);
        }
        break;
      case 7:
        SortList(&list);
        break;
      case 8:
        printf("Enter index: ");
        scanf("%i", &buffInt);
        type = DoMenu(typeNames, 2);
        if (type != None) {
          item = Create(type);
          InputItem(item);
          Insert(&list, (struct Item*)item, buffInt);
          printf("Item was inserted!\n\n");
        }
        break;
      case 9:
        printf("Enter index: ");
        scanf("%i", &buffInt);
        Delete(&list, buffInt);
        break;
      case 10:
        Clear(&list);
        printf("List was cleared\n\n");
        break;
      case -1:
        return 0;
        break;
      default:
        printf("Wrong option!\n\n");
        break;
    }
  } while (1);

}
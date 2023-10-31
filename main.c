#include <stdio.h>
#include <stdlib.h>
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

int main(void){
    struct List list;
    list.head = NULL;
    list.tail = NULL;
    int key, n;
    struct Item* item = (struct Item*)calloc(1, sizeof(struct Item));

    char *menuActions[] = {"(none)", "Add Item", "Count", "Print List", "Print Item", "Search By Name", "Search By Distance", "Sort List", "Insert", "Delete", "Clear"};
    char *typeNames[] = {"(unknown)", "Star", "Planet"};

    int buffInt;
    char *buffStr = (char*)calloc(1, sizeof(char) * 100);
    do
    {
        printf("\nCHOOSE OPERATION:\n\t 1 - Add\n\t 2 - Count\n\t"
            " 3 - Print List\n\t"
            " 4 - Delete\n\t"
            " 5 - Insert\n\t"
            " 6 - Clear\n"
            " 0 - EXIT\n");
        if (scanf("%d", &key) != 1)
            key = -1;
        system("cls");
        switch (key)
        {
        case 1:
            item = (struct Item*)calloc(1, sizeof(struct Item));
            Add(&list, item);
            printf("Item was successful added\n");
            break;
        case 2:

            printf("%d", Count(&list));
            break;
        case 3:
            PrintList(&list);
            break;
        case 4:
            printf("Input index to delete");
            scanf("%d", &n);
            Delete(&list, n);
            printf("Item was successful deleted");
            break;
        case 5:
            item = (struct Item*)calloc(1, sizeof(struct Item));
            printf("Input index to insert");
            scanf("%d", &n);
            Insert(&list, item, n);
            printf("Item was successful inserted");
            break;
        case 6:
            Clear(&list);
            printf("Item was successful cleared");
            break;
        case 0:
            break;
        }
    } while (key);
    return 0;
}
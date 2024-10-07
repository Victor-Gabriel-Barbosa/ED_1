#include <stdio.h>
#include <list.h>
#include <utils.h>

int main() {
  List mylist = newList();
  insertAtBegin(mylist, 2);
  insertAtEnd(mylist, 5);
  printsf("%L", mylist);
  destroyList(mylist);
}
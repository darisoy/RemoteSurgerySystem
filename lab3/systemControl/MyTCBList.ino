#include "MyTCBList.h"
#include "dataStructs.h"
#include <stdio.h>

void schedulerFunction(MyTCBList * TCBListPtr, MyTCB * front, MyTCB * back, int size){
  TCBListPtr->front = &front;
  TCBListPtr->back = &back;
  TCBListPtr->size = size;
}

void schedulerInsert(MyTCBList * TCBListPtr, MyTCB * ITCB, int location){
  if (location < *TCBListPtr.size){
    int count = 0;
    MyTCB * placeholder = TCBListPtr.front;
    while (count < location){
      placeholder = placeholder.next;
      count++;
    }
    ITCB.next = placeholder.next;
    ITCB.prev = placeholder;
    placeholder.next = ITCB;
    *TCBListPtr.size++;
  }
}

void schedulerDelete(MyTCBList * TCBListPtr, int location){
  if (location < TCBListPtr.size){
    int count = 0;
    MyTCB * placeholder = TCBListPtr.front;
    while (count < location){
      placeholder = placeholder.next;
      count++;
    }
    if (placeholder.prev != NULL){
      placeholder.prev.next = placeholder.next;
    }
    if (placeholder.next != NULL){
    placeholder.next.prev = placeholder.prev;
    }
    TCBListPtr.size--;
  }
}

#include "dataStructs.h"
#include "SchedulerFunction.h"

#ifndef SchedulerFunction
#define SchedulerFunction

void schedulerFunctionAdd(MyTCB* TCBPtr, void* list){
  struct LinkedList* newList = (struct LinkedList*) list;
  TCBPtr->next = newList->placeholder->next;
  TCBPtr->prev = newList->placeholder;
  newList->placeholder->next = TCBPtr;
  newList->placeholder->next->prev = TCBPtr;
  newList->size++;
}

void schedulerFunctionDelete(MyTCB* TCBPtr, void* list){
  struct LinkedList* newList = (struct LinkedList*) list;
  MyTCB* cur = newList->front;
  for (int i = 0; i < newList->size; i++){
    if (cur == TCBPtr){
      cur->prev->next = cur->next;
      cur->next->prev = cur->prev;
      break;
    }
    cur = cur->next;
  }
}

void schedulerFunctionRun(void* list){
  struct LinkedList* newList = (struct LinkedList*) list;
  (*newList->placeholder->timedActionPtr).check();
  newList->placeholder = newList->placeholder->next;
}

#endif

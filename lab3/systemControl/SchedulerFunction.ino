#include "dataStructs.h"                                                  //import the variables
#include "SchedulerFunction.h"                                            //import the header of this function

#ifndef SchedulerFunction                                                 //check to see if variables are defined elsewhere
#define SchedulerFunction                                                 //assigns definiton to dataStructs

void schedulerFunctionAdd(MyTCB* TCBPtr, void* list){
  struct LinkedList* newList = (struct LinkedList*) list;
  TCBPtr->next = newList->placeholder->next;
  TCBPtr->prev = newList->placeholder;
  newList->placeholder->next = TCBPtr;
  newList->placeholder->next->prev = TCBPtr;
  newList->size++;                                                        //increment size by 1
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
  newList->size--;                                                        //decrement size by 1
}

void schedulerFunctionRun(void* list){
  struct LinkedList* newList = (struct LinkedList*) list;
  (*newList->placeholder->timedActionPtr).check();
  MyTCB* cur = newList->placeholder;
  if (runCompute) {                                                         //if compute needs to be run
      schedulerFunctionAdd(&computeT, &scheduler);                          //add compute to task queue
      runCompute = false;
  } else {
      schedulerFunctionDelete(&computeT, &scheduler);                       //delete compute to task queue
  }
  newList->placeholder = newList->placeholder->next;
}

#endif

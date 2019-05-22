#include "dataStructs.h"                                                  //import the variables
#include "SchedulerFunction.h"                                            //import the header of this function

#ifndef SchedulerFunction                                                 //check to see if variables are defined elsewhere
#define SchedulerFunction                                                 //assigns definiton to dataStructs

void schedulerFunctionAdd(MyTCB* TCBPtr, void* list){                     //Function takes in a TCB pointer and a void pointer
    struct LinkedList* newList = (struct LinkedList*) list;                 //the void pointer is dereferenced into a linkedlist pointer
    TCBPtr->next = newList->placeholder->next;                              //the TCB pointer's next TCB is now the placeholder's next
    TCBPtr->prev = newList->placeholder;                                    //the TCB's pointer prev TCB is now the placeholder
    newList->placeholder->next = TCBPtr;                                    //the placeholder's next pointer TCB is now the TCBPtr
    newList->placeholder->next->prev = TCBPtr;                              //the placeholder's next TCB's prev pointer TCB is now the TCBPtr
    newList->size++;                                                        //increment size by 1
}

boolean schedulerContains(MyTCB* TCBPtr, void* list){
  struct LinkedList* newList = (struct LinkedList*) list;
  MyTCB* cur = newList->front;
  for (int i = 0; i < newList->size; i++){
    if (cur == TCBPtr){
      return true;
    }
  }
}

void schedulerFunctionDelete(MyTCB* TCBPtr, void* list){                  //the function takes in a TCB pointer and a void pointer
    struct LinkedList* newList = (struct LinkedList*) list;                 //the void pointer is dereferenced into a linkedlist pointer
    MyTCB* cur = newList->front;                                            //a MyTCB pointer is created pointing at the front of the newList
    for (int i = 0; i < newList->size; i++){                                //a for loop that runs for the size of the newList
        if (cur == TCBPtr){                                                   //if the MyTCB pointer cur is the same as the TCBPtr
            cur->prev->next = cur->next;                                        //the prev TCB's next pointer points to the cur's next pointer
            cur->next->prev = cur->prev;                                        //the prev TCB's prev pointer points to the cur's prev pointer
            newList->size--;                                                        //decrement size by 1
            break;                                                              //the code ends
        }
        cur = cur->next;                                                      //cur is not cur.next
    }
}

void schedulerFunctionRun(void* list){                                    //function takes in a void pointer
    struct LinkedList* newList = (struct LinkedList*) list;                 //the void pointer is dereferenced into a linkedlist pointer
    (*newList->placeholder->timedActionPtr).check();                        //the check method is run on the timedActionPtr of the MyTCB
    MyTCB* cur = newList->placeholder;                                      //the MyTCB pointer cur is now pointing to the placeholder
    if (runCompute && !schedulerContains(&computeT, list)) {                                                       //if compute needs to be run
        schedulerFunctionAdd(&computeT, &scheduler);                        //add compute to task queue
        runCompute = false;                                                 //change runCompute boolean value to false
    } else if (schedulerContains(&computeT, list)) {
        schedulerFunctionDelete(&computeT, &scheduler);                     //delete compute to task queue
    }
    newList->placeholder = newList->placeholder->next;                      //placeholder is now equal to placeholder.next
}

#endif

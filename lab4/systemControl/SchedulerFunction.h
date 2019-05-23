

void schedulerFunctionAdd(MyTCB* TCBPtr, void* LinkedList);        //header for schedulerFunctionAdd
                                                                    //takes in the pointer for task and for LinkedList
void schedulerFunctionDelete(MyTCB* TCBPtr, void* LinkedList);      //header for schedulerFunctionDelete
                                                                    //takes in the pointer for task and for LinkedList
void schedulerFunctionRun(void* LinkedList);                        //header for schedulerFunctionRun
                                                                    //takes in the pointer for LinkedList
boolean schedulerContains(MyTCB* TCBPtr, void* LinkedList);

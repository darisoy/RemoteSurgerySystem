#include "Buffer.h"
#include "dataStructs.h"
#include <stdio.h>

void BufferFunction(BufferData * buff, double * bufferPtr, int size){
  buff->list = bufferPtr;
  buff->front = 0;
  buff->back = 0;
  buff->size = size;
}

void BufferWrite(BufferData * buff, double data){
    if (buff->front == buff->back && buff->size != 0){
        buff->back += 1;
        if (buff->back >= buff->size){
            buff->back = 0;
        }
    }
    buff->list[buff->front] = data;
    buff->front += 1;
    if (buff->front >= buff->size){
        buff->front = 0;
    }
}

double BufferRead(BufferData * buff){
    if (buff->size > 0){
        double output = buff->list[buff->back];
        if (buff->back >= buff->size){
            buff->back = 0;
        } else {
            buff->back += 1;
        }
        buff->size -= 1;
        return output;
    }
    return NULL;
}

#include "Buffer.h"
#include "dataStructs.h"
#include <stdio.h>

Buffer * BufferFunction(Buffer * buff, char * bufferPtr, int size){
  buff->list = bufferPtr;
  buff->front = 0;
  buff->back = 0;
  buff->size = size;
  return buff;
}

void BufferWrite(Buffer * buff, (void*) data){
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

void * BufferRead(Buffer * buff){
  if (buff->size <= 0){
    throw new Exception();
  }
  (void*) output = buff->list[buff->back];
  if (buff->back >= buff->size){
  buff->back = 0;
  } else{
  buff->back += 1;
  }
  buff->size -= 1;
  return output;
}

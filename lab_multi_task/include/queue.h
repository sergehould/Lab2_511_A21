/**
  
*/

#ifndef QUEUE_H
#define QUEUE_H
/**
    Section: Includes
*/
#include <stdint.h>
#include <xc.h>
/**
    Section: Macros
*/

typedef struct  {
	int front, rear, size;
	unsigned capacity;
	int* array;
}QueueHandle_t;

QueueHandle_t* xQueueCreate(unsigned capacity);
int xQueueSendToBack(QueueHandle_t* queue, int* item);
int xQueueReceive(QueueHandle_t* queue,int* rx);

#endif

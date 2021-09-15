/* Name: queue.c 
 * 
 * Description: Implementation of a queue
 *
 * REVISION HISTORY:
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author        	Date      	Version     Comments on this revision
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Serge Hould      2019-09-13	v1.0        First version of source files
 *
 * 
 * 		
 *****************************************************************************/
 /*
 * 
 * For implementing queue, we need to keep track of two indices, front and rear. 
 * We enqueue an item at the rear and dequeue an item from the front. If we simply 
 * increment front and rear indices, then there may be problems, the front may reach the end of the array. 
 * The solution to this problem is to increase front and rear in circular manner.
 * Tested OK
 */
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/queue.h"


// function to create a queue
// of given capacity.
// It initializes size of queue as 0
QueueHandle_t* xQueueCreate(unsigned capacity)
{
	QueueHandle_t* queue = (QueueHandle_t*)malloc(sizeof(QueueHandle_t));
	queue->capacity = capacity;
	queue->front = queue->size = 0;

	// This is important, see the enqueue
	queue->rear = capacity - 1;
	queue->array = (int*)malloc(queue->capacity * sizeof(int));
	return queue;
}

// Queue is full when size becomes
// equal to the capacity
static int isFull(QueueHandle_t* queue)
{
	return (queue->size == queue->capacity);
}

// Queue is empty when size is 0
static int isEmpty(QueueHandle_t* queue)
{
	return (queue->size == 0);
}

// Function to add an item to the queue.
// Returns -1 if full
// Returns 0 if not full
// The content pointed by item is enqueued.  In other words,
// the content pointed by item is stored into the tail of the queue 
int xQueueSendToBack(QueueHandle_t* queue, int* item)
{
	if (isFull(queue)) return -1;
	queue->rear = (queue->rear + 1)
		% queue->capacity;
	queue->array[queue->rear] = *item;
	queue->size = queue->size + 1;
    return 0;
}

// Function to remove an item from queue.
// Returns -1 if empty
// Returns 0 if not empty
// It dequeues into the address pointed by rx.  
// In other words, the head of the queue is stored at the 
// address pointed by rx
int xQueueReceive(QueueHandle_t* queue,int* rx)
{
	if (isEmpty(queue)) return -1;
	int item = queue->array[queue->front];
	queue->front = (queue->front + 1)
		% queue->capacity;
	queue->size = queue->size - 1;
    *rx = item;
	return 0;
}

// Function to get front of queue
static int front(QueueHandle_t* queue)
{
	if (isEmpty(queue))	return -1;
	return queue->array[queue->front];
}

// Function to get rear of queue
static int rear(QueueHandle_t* queue)
{
	if (isEmpty(queue))	return -1;
	return queue->array[queue->rear];
}

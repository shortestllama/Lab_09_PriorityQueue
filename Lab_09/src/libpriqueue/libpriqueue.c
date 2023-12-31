/** @file libpriqueue.c
 */

#include <stdlib.h>
#include <stdio.h>

#include "libpriqueue.h"


/**
  Initializes the priqueue_t data structure.
  
  Assumtions
    - You may assume this function will only be called once per instance of priqueue_t
    - You may assume this function will be the first function called using an instance of priqueue_t.
  @param q a pointer to an instance of the priqueue_t data structure
  @param comparer a function pointer that compares two elements.
  See also @ref comparer-page
 */
void priqueue_init(priqueue_t *q, int(*comparer)(const void *, const void *))
{
  q->size = 0;
  q->comparer = comparer;
}


/**
  Insert the specified element into this priority queue.

  @param q a pointer to an instance of the priqueue_t data structure
  @param ptr a pointer to the data to be inserted into the priority queue
  @return The zero-based index where ptr is stored in the priority queue, where 0 indicates that ptr was stored at the front of the priority queue.
 */
int priqueue_offer(priqueue_t *q, void *ptr)
{
  for (int i = 0; i < q->size; i++) {
    // printf("%d\n%d\n%d\n%d\n", i, q->comparer((const void *) q->queue[i], ptr), q->size, *(int *) ptr);
    if (q->comparer((const void *) q->queue[i], ptr) >= 0) {
      q->size++;

      for (int j = q->size - 1; j > i; j--) {
        q->queue[j] = q->queue[j - 1];
      }

      q->queue[i] = ptr;
      return i;
    }
  }

  q->size++;
  q->queue[q->size - 1] = ptr;
  return 0;
}


/**
  Retrieves, but does not remove, the head of this queue, returning NULL if
  this queue is empty.
 
  @param q a pointer to an instance of the priqueue_t data structure
  @return pointer to element at the head of the queue
  @return NULL if the queue is empty
 */
void *priqueue_peek(priqueue_t *q)
{
	if (q->size == 0) {
  	return NULL;
  }

  return q->queue[q->size - 1];
}


/**
  Retrieves and removes the head of this queue, or NULL if this queue
  is empty.
 
  @param q a pointer to an instance of the priqueue_t data structure
  @return the head of this queue
  @return NULL if this queue is empty
 */
void *priqueue_poll(priqueue_t *q)
{
	if (q->size == 0) {
    return NULL;
  }

  void *temp = q->queue[0];

  for (int i = 0; i < q->size - 1; i++) {
    q->queue[i] = q->queue[i + 1];
  }

  q->size--;
  return temp;
}


/**
  Returns the element at the specified position in this list, or NULL if
  the queue does not contain an index'th element.
 
  @param q a pointer to an instance of the priqueue_t data structure
  @param index position of retrieved element
  @return the index'th element in the queue
  @return NULL if the queue does not contain the index'th element
 */
void *priqueue_at(priqueue_t *q, int index)
{
	if (q->size - 1 < index && 0 > index) {
    return NULL;
  }

  return q->queue[index];
}


/**
  Removes all instances of ptr from the queue. 
  
  This function should not use the comparer function, but check if the data contained in each element of the queue is equal (==) to ptr.
 
  @param q a pointer to an instance of the priqueue_t data structure
  @param ptr address of element to be removed
  @return the number of entries removed
 */
int priqueue_remove(priqueue_t *q, void *ptr)
{
	int count = 0;

  for (int i = 0; i < q->size; i++) {
    // printf("%d\n%d\n%d\n", i, *(int *) q->queue[i], *(int *) ptr);
    if (q->queue[i] == ptr) {
      for (int j = i; j < q->size - 1; j++) {
        q->queue[j] = q->queue[j + 1];
      }

      count++;
      q->size--;
      i--;
    }
  }

	return count;
}


/**
  Removes the specified index from the queue, moving later elements up
  a spot in the queue to fill the gap.
 
  @param q a pointer to an instance of the priqueue_t data structure
  @param index position of element to be removed
  @return the element removed from the queue
  @return NULL if the specified index does not exist
 */
void *priqueue_remove_at(priqueue_t *q, int index)
{
	for (int i = 0; i < q->size; i++) {
    if (i == index) {
      void *temp = q->queue[i];

      for (int j = i; j < q->size - 1; j++) {
        q->queue[j] = q->queue[j + 1];
      }

      q->size--;
      return temp;
    }
  }

	return NULL;
}


/**
  Return the number of elements in the queue.
 
  @param q a pointer to an instance of the priqueue_t data structure
  @return the number of elements in the queue
 */
int priqueue_size(priqueue_t *q)
{
	return q->size;
}


/**
  Destroys and frees all the memory associated with q.
  
  @param q a pointer to an instance of the priqueue_t data structure
 */
void priqueue_destroy(priqueue_t *q)
{

}

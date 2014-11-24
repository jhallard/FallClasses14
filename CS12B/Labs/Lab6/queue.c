//  file:     queue.c
//  Author  - John Allard
//  CruzID  - jhallard
//  Class   - CS12M, Lab #6s
//  Date    - Nov 20th, 2014
//  Prupose - This is the implementation (Source) file for the queue struct.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define STUBPRINTF(...) fprintf(stderr, __VA_ARGS__);

/* Internal implementation definitions */
struct queue_node {
   queue_item_t item;
   struct queue_node *link;
};

typedef struct queue_node queue_node;

struct queue {
   queue_node *front;
   queue_node *rear;
};

/* Functions */

queue *queue_new(void) {
   queue * temp = malloc(sizeof(queue));
   temp->front = NULL;
   temp->rear = NULL;
   return temp;
}

void queue_free(queue *this) {
   queue_node * temp = this->front;
   while(temp != NULL) {
      printf("%c\n", *temp->item);
      queue_node * temp2 = temp;
      temp = temp->link;
      free(temp2);
   }
   free(this);
}

void queue_insert(queue *this, queue_item_t item) {
   queue_node * temp = malloc(sizeof(struct queue_node));
   temp->item = item;
   temp->link = NULL;

   if(this->front == NULL)
      this->front = temp;
   if(this->rear == NULL)
      this->rear = temp;
   else {
      this->rear->link = temp;
      this->rear = temp;
   }


}

queue_item_t queue_remove(queue *this) {
   assert(!queue_isempty(this));
   struct queue_node * temp = this->front;
   queue_item_t ret = temp->item;
   this->front = this->front->link;
   free(temp);
   return ret;
}

bool queue_isempty(queue *this) {
   return this->front == NULL;
}

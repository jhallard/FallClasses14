#ifndef __QUEUE_H__
#define __QUEUE_H__


//  file:     queue.h
//  Author  - John Allard
//  CruzID  - jhallard
//  Class   - CS12M, Lab #6s
//  Date    - Nov 20th, 2014
//  Prupose - This is the header (declaration) file for the queue struct.


#include <stdbool.h>

/* External interface declarations */

struct queue;
typedef struct queue queue;
typedef char *queue_item_t;

/* Function declarations */

queue *queue_new(void);

void queue_free(queue*);

void queue_insert(queue*, queue_item_t);

queue_item_t queue_remove(queue*);

bool queue_isempty(queue*);

#endif

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "jval.h"

typedef JRB Queue;

Queue priority_make_queue();
void priority_enqueue(Queue queue,int key,JRB val);
void priority_dequeue(Queue queue,int key);
void priority_extract_min(Queue queue,int* key,JRB val);
void priority_free_queue(Queue queue);

#endif

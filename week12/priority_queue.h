#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

typedef JRB Queue;

Queue priority_make_queue();
void priority_enqueue(Queue queue,int key,Graph* val);
void priority_dequeue(Queue queue,int key);
void priority_extract_min(Queue queue);
void priority_free_queue(Queue queue);

#endif

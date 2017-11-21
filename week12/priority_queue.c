#include "prority_queue.h"

Queue priority_make_queue() {
  return make_jrb();
}
void priority_enqueue(Queue queue,int key,int* val) {
}

void priority_dequeue(Queue queue,int key) {
}
					  
void priority_extract_min(Queue queue) {
}

void priority_free_queue(Queue queue) {
  jrb_free_tree(queue);
}

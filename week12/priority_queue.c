#include "priority_queue.h"

Queue priority_make_queue() {
  return make_jrb();
}

int compare2(Jval a,Jval b) {
  if (jval_i(a)<jval_i(b)) return -1;
  else return 1;
}

void priority_enqueue(Queue queue,int key,JRB val) {
  jrb_insert_gen(queue,new_jval_i(key),new_jval_v(val),compare2);
}

void priority_dequeue(Queue queue,int key) {
  Queue node=jrb_find_gen(queue,new_jval_i(key),compare2);
  if (node) jrb_delete_node(node);
}

void priority_extract_min(Queue queue,int *key,JRB val) {
  int min=100000;
  Queue node;
  jrb_traverse(node,queue) {
    if (jval_i(node->key)<min) min=jval_i(node->key);
  }
  *key=min;
  JRB tmp=jrb_find_gen(queue,new_jval_i(min),compare2);
  printf("%d\n",jval_i(tmp->key));
  val=make_jrb();
  val=(JRB)jval_v(tmp->val);
  jrb_delete_node(tmp);
}

void priority_free_queue(Queue queue) {
  jrb_free_tree(queue);
}

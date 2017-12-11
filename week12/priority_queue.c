#include "priority_queue.h"

Queue priority_make_queue() {
  return make_jrb();
}

int compare_find(Jval a,Jval b) {
  if (jval_i(a)<jval_i(b)) return -1;
  else if (jval_i(a)==jval_i(b)) return 0;
  else return 1;
}

// use to enqueue with same key (insert after if same key)
int compare_insert(Jval a,Jval b) {
  if (jval_i(a)<jval_i(b)) return -1;
  else return 1;
}

void priority_enqueue(Queue queue,int key,JRB val) {
  jrb_insert_gen(queue,new_jval_i(key),new_jval_v(val),compare_insert);
}

void priority_dequeue(Queue queue,int key) {
  Queue node=jrb_find_gen(queue,new_jval_i(key),compare_find);
  if (node) jrb_delete_node(node);
}

void priority_extract_min(Queue queue,int* key,JRB *val) {
  int min=100000;
  Queue node,tmp;
  jrb_traverse(node,queue) {
    if (jval_i(node->key)<min) {min=jval_i(node->key);tmp=node;}
  }
  *key=min;
  //JRB tmp=jrb_find_gen(queue,new_jval_i(min),compare_find); somehow it do not find the first one so can't use this
  //printf("%d\n",jval_i(tmp->key));//min feq
  *val=(JRB)jval_v(tmp->val);
  //printf("%d\n",jval_i((*val)->key));//node key(char) have min feq
  jrb_delete_node(tmp);
}

void priority_free_queue(Queue queue) {
  jrb_free_tree(queue);
}

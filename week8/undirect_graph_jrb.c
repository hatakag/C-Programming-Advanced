#include "undirect_graph_jrb.h"

Graph createGraph(){
  return make_jrb();
}

void addEdge(Graph graph,int v1,int v2){
  Graph tree;
  Graph node=jrb_find_int(graph,v1); // graph_v1
  if (!node) {  //do not exist make new
    tree=make_jrb();
    jrb_insert_int(graph,v1,new_jval_v(tree));
    jrb_insert_int(tree,v2,new_jval_i(1));
  } else {      //already exist
    tree=(JRB)jval_v(node->val);
    jrb_insert_int(tree,v2,new_jval_i(1));
  }
  
  node=jrb_find_int(graph,v2); //graph_v2
  if (!node) {  //do not exist make new
    tree=make_jrb();
    jrb_insert_int(graph,v2,new_jval_v(tree));
    jrb_insert_int(tree,v1,new_jval_i(1));
  } else {      //already exist
    tree=(JRB)jval_v(node->val);
    jrb_insert_int(tree,v1,new_jval_i(1));
  }
}

int adjacent(Graph graph,int v1,int v2){
  Graph node_v1=jrb_find_int(graph,v1);
  Graph node_v2=jrb_find_int(graph,v2);
  if (node_v1 || node_v2) {
    Graph tree_v1,tree_v2;
    tree_v1=(JRB)jval_v(node_v1->val);
    tree_v2=(JRB)jval_v(node_v2->val);
    Graph node_tree_v1_v2=jrb_find_int(tree_v1,v2);
    Graph node_tree_v2_v1=jrb_find_int(tree_v2,v1);
    if (node_tree_v1_v2 || node_tree_v2_v1) 
      return jval_i(node_tree_v1_v2->val) || jval_i(node_tree_v2_v1->val);//1
    else return 0;
  } else return 0;
}

int getAdjacentVertices(Graph graph,int v,int *output) {
  int total=0;
  Graph node=jrb_find_int(graph,v);
  if (node) {
    Graph tree=(JRB)jval_v(node->val);
    Graph node_traverse;
    jrb_traverse(node_traverse,tree)
      output[total++]=jval_i(node_traverse->key);
  }
  return total;
}

void dropGraph(Graph graph){
  if (!jrb_empty(graph)) {
    Graph node;
    jrb_traverse(node,graph) 
      jrb_free_tree(jval_v(node->val));
  }
  jrb_free_tree(graph);
}

void BFS(Graph graph,int start,int stop,void (*func)(int)) {
  //check existing
  Graph node1=jrb_find_int(graph,start);
  Graph node2=jrb_find_int(graph,stop);
  if (!node1) {printf("Do not exist node %d\n",start);return;}
  if (!node2 && stop!=-1) {printf("Do not exist node %d\n",stop);return;}
  //number of node in graph
  int n=0;
  if (!jrb_empty(graph)) {
    Graph node;
    jrb_traverse(node,graph)
      n++;
  }
  // initialize array key of node in graph corresponding with array mark unvisited(0) 
  int mark[n],key[n],i=0,j,k;
  if (!jrb_empty(graph)) {
    Graph node;
    jrb_traverse(node,graph) {
      mark[i]=0;
      key[i++]=jval_i(node->key);
    }
  }
  // Queue
  Dllist queue=new_dllist();
  dll_append(queue,new_jval_i(start)); //enqueue
  while (dll_empty(queue)!=1) { //not empty
    Dllist node=dll_first(queue); 
    int v=jval_i(node->val);
    dll_delete_node(node);  //dequeue
    for (i=0;i<n;i++) 
      if (key[i]==v) break; // find key (i) corresponding with node value
    if (mark[i]==0) { // if unvisited
      func(v); //print node value
      mark[i]=1; // mark as visited
      if (v==stop) {free_dllist(queue);return;} 
      int adja[n];
      int total=getAdjacentVertices(graph,v,adja); // get adjacent vertices
      for (k=0;k<total;k++) 
	for (j=0;j<n;j++) 
	  if (key[j]==adja[k] && mark[j]==0) dll_append(queue,new_jval_i(adja[k]));
    }
  }
  free_dllist(queue);
}

void DFS(Graph graph,int start,int stop,void (*func)(int)) {
  //check existing
  Graph node1=jrb_find_int(graph,start);
  Graph node2=jrb_find_int(graph,stop);
  if (!node1) {printf("Do not exist node %d\n",start);return;}
  if (!node2 && stop!=-1) {printf("Do not exist node %d\n",stop);return;}
  //number of node in graph
  int n=0;
  if (!jrb_empty(graph)) {
    Graph node;
    jrb_traverse(node,graph)
      n++;
  }
  // initialize array key of node in graph corresponding with array mark unvisited(0) 
  int mark[n],key[n],i=0,j,k;
  if (!jrb_empty(graph)) {
    Graph node;
    jrb_traverse(node,graph) {
      mark[i]=0;
      key[i++]=jval_i(node->key);
    }
  }
  // Stack
  Dllist stack=new_dllist();
  dll_append(stack,new_jval_i(start)); //push
  while (dll_empty(stack)!=1) { //not empty
    Dllist node=dll_last(stack); 
    int v=jval_i(node->val);
    dll_delete_node(node);  //pop
    for (i=0;i<n;i++) 
      if (key[i]==v) break; // find key (i) corresponding with node value
    if (mark[i]==0) { //if unvisited
      func(v); //print node value
      mark[i]=1; //mark as visited
      if (v==stop) {free_dllist(stack);return;}
      int adja[n];
      int total=getAdjacentVertices(graph,v,adja); // get adjacent vertices
      for (k=0;k<total;k++) 
	for (j=0;j<n;j++) 
	  if (key[j]==adja[k] && mark[j]==0) dll_append(stack,new_jval_i(adja[k])); //push
    }
  }
  free_dllist(stack);
}

void BFS2(Graph g,int start,int stop,void(*func)(int)) {
  JRB check1 = jrb_find_int(g,start);
  JRB check2 = jrb_find_int(g,stop);
  if(check1 == NULL ) {
    printf("Graph does not have vertex %d\n", start);
    return;
  }
  if(stop != -1 && check2 == NULL) {
    printf("Graph does not have vertex %d\n", stop);
    return;
  }
  // Create a graph name 'visited' in which each node's key is
  // a vertex, and it's key indicate whether the vertex has been
  // visited (1) or not (0)
  Graph visited = createGraph();
  Graph tmp;
  int V = 0;
  jrb_traverse(tmp,g) {
    V++;
    jrb_insert_int(visited, jval_i(tmp->key), new_jval_i(0));
  }
  int output[V];
  
  // Create a queue and enqueue the first element
  Dllist queue = new_dllist();
  dll_append(queue,new_jval_i(start));
  // Traversing
  while(dll_empty(queue) != 1) {
    // Take first element in the queue
    Dllist node = dll_first(queue);
    int key = jval_i(node->val);
    // Dequeue this element
    dll_delete_node(node);
    
    tmp = jrb_find_int(visited, key);
    if(jval_i(tmp->val) == 0) {
      // Pass the vertex to external function
      func(key);
      // Mark this element as 'visited'
      jrb_delete_node(tmp);
      jrb_insert_int(visited, key, new_jval_i(1));		
    }
    
    // If this is the required vertex, return
    if (key == stop) {
      free_dllist(queue);
      jrb_free_tree(visited);
      return;
    }
    int i;
    int count = getAdjacentVertices(g, key, output);
    for (i = 0; i < count; i++)
      {
	JRB ptr = jrb_find_int(visited, output[i]);
	if(jval_i(ptr->val) == 0)
	  dll_append(queue,new_jval_i(output[i])); 
      }
    
  }
  free_dllist(queue);
  jrb_free_tree(visited);
}

// DFS ..........................................................

void DFS2(Graph g, int start, int stop, void (*func)(int)) {
  JRB check1 = jrb_find_int(g,start);
  JRB check2 = jrb_find_int(g,stop);
  if(check1 == NULL ) {
    printf("Graph does not have vertex %d\n", start);
    return;
  }
  if(stop != -1 && check2 == NULL) {
    printf("Graph does not have vertex %d\n", stop);
    return;
  }
  
  // Create a graph name 'visited' in which each node's key is
  // a vertex, and it's key indicate whether the vertex has been
  // visited (1) or not (0)
  Graph visited = createGraph();
  Graph tmp;
  int V = 0;
  jrb_traverse(tmp, g) {
    V++;
    jrb_insert_int(visited, jval_i(tmp->key), new_jval_i(0));
  }
  int output[V];
  
  // Create a stack and push the first element
  Dllist stack = new_dllist();
  dll_append(stack, new_jval_i(start));
  
  // Traversing
  while(dll_empty(stack) != 1) {
    // Take the top element in the stack
    Dllist dll_tmp = dll_last(stack);
    int key = jval_i(dll_tmp->val);
    
    tmp = jrb_find_int(visited, key);
    if(jval_i(tmp->val) == 0) {
      // Pass the vertex to external function
      func(key);
      // Mark this element as 'visited'
      jrb_delete_node(tmp);
      jrb_insert_int(visited, key, new_jval_i(1));
    } else {
      // Pop this element
      dll_delete_node(dll_tmp);
    }
    
    // If this is the required vertex, return
    if (key == stop) {
      free_dllist(stack);
      jrb_free_tree(visited);
      return;
    }
    int i;
    int count = getAdjacentVertices(g, key, output);
    for (i = 0 ; i < count; i++)
      {
	// If the vertice has not been visited, push it
	tmp = jrb_find_int(visited, output[i]);
	if (jval_i(tmp->val) == 0) {
	  key = jval_i(tmp->key);
	  dll_append(stack, new_jval_i(key));
	}
      }
    
    // JRB u_node = jrb_find_int(g, key);
    // if(u_node == NULL) continue;
    
    // JRB v_connect_to_u = (JRB)jval_v(u_node->val);
    // jrb_rtraverse(tmp, v_connect_to_u) {
    // 	JRB ptr = jrb_find_int(visited, tmp->key.i);
    // 	if(jval_i(ptr->val) == 0)
    // 		dll_append(stack, new_jval_i(tmp->key.i));
    // }
  }
  free_dllist(stack);
  jrb_free_tree(visited);
}

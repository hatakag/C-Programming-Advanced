#include "weighted_graph_jrb.h"

Graph createGraph() {
  Graph g;
  g.edges=make_jrb();
  g.vertices=make_jrb();
  return g;
}

void addVertex(Graph graph, int id, char* name) {
  JRB node=jrb_find_int(graph.vertices,id);
  if (!node) { //do not exist make new
    jrb_insert_int(graph.vertices,id,new_jval_s(name));
      
  } else { //exist
    printf("Already exist\n");
    printf("Modify ? (y/n)\n");
    char c=getchar();__fpurge(stdin);
    if (c=='y') jrb_insert_int(graph.vertices,id,new_jval_s(name));
    else if (c=='n') {}
    else printf("y or n\n");
  }
}

char *getVertex(Graph graph, int id) {
  JRB node=jrb_find_int(graph.vertices,id);
  if (!node) //do not exist
    return NULL;
  else return jval_s(node->val);
}

void addEdge(Graph graph, int v1, int v2,double weight) {
  if (getVertex(graph,v1)==NULL) {
    printf("Add Vertex %d first\n",v1);
    return;
  }
  if (getVertex(graph,v2)==NULL) {
    printf("Add Vertex %d first\n",v2);
    return;
  }
  if (hasEdge(graph,v1,v2)==0) {
    JRB tree;
    JRB node=jrb_find_int(graph.edges,v1);
    if (!node) {  //do not exist make new
      tree=make_jrb();
      jrb_insert_int(graph.edges,v1,new_jval_v(tree)); //only insert v1 to graph.edges, v2 is not
      jrb_insert_int(tree,v2,new_jval_d(weight));
    } else {      //already exist
      tree=(JRB)jval_v(node->val);
      jrb_insert_int(tree,v2,new_jval_d(weight));
    }
  }
}

int hasEdge(Graph graph, int v1, int v2) { //only edge from v1 to v2 (not from v2 to v1)
  if (getVertex(graph,v1)==NULL) {
    printf("Add Vertex %d first\n",v1);
    return 0;
  }
  if (getVertex(graph,v2)==NULL) {
    printf("Add Vertex %d first\n",v2);
    return 0;
  }
  JRB node=jrb_find_int(graph.edges,v1);
  if (node) { // exist node v1 in graph.edges
    JRB tree;
    tree=(JRB)jval_v(node->val);
    JRB node_tree=jrb_find_int(tree,v2);
    if (node_tree) //exist node v2 in tree(value of node v1 in graph.edges)
      return 1;//jval_i(node_tree->val);
    else return 0;
  } else return 0;
}

int indegree(Graph graph, int v, int* output) { // output all vertices go in node v
  int total=0;
  if (getVertex(graph,v)==NULL) {
    printf("Add Vertex %d first\n",v);
    return 0;
  }
  JRB node_traverse;
  jrb_traverse(node_traverse,graph.edges)
    if (hasEdge(graph,jval_i((node_traverse)->key),v)==1) //if has edge from other nodes to node v
      output[total++]=jval_i((node_traverse)->key);
  return total;
}

int outdegree(Graph graph, int v, int* output) { // output all vertices go out node v
  int total=0;
  if (getVertex(graph,v)==NULL) {
    printf("Add Vertex %d first\n",v);
    return 0;
  }
  JRB node=jrb_find_int(graph.edges,v);
  if (node) {
    JRB tree=(JRB)jval_v(node->val); //tree of all nodes from node v to them
    JRB node_traverse;
    jrb_traverse(node_traverse,tree)
      output[total++]=jval_i(node_traverse->key);
  }
  return total;
}

int DAG(Graph graph) { //1 is acyclic, 0 is not (have cycles)
  //number of node in graph
  int n=0;
  if (!jrb_empty(graph.vertices)) {
    JRB node;
    jrb_traverse(node,graph.vertices)
      n++;
  }
  // initialize array key of node in graph corresponding with array mark unvisited(0) 
  int mark[n],key[n],i=0,j,k;
  if (!jrb_empty(graph.vertices)) {
    JRB node;
    jrb_traverse(node,graph.vertices) {
      mark[i]=0;
      key[i++]=jval_i(node->key);
    }
  }
  // Stack
  Dllist stack=new_dllist();
  dll_append(stack,new_jval_i(key[0])); //push
  while (dll_empty(stack)!=1) { //not empty
    Dllist node=dll_last(stack); 
    int v=jval_i(node->val);
    dll_delete_node(node);  //pop
    for (i=0;i<n;i++) 
      if (key[i]==v) break; // find key (i) corresponding with node value
    if (mark[i]==0) { //if unvisited    
      mark[i]=1; //mark as visited
      
      int adja[n];
      int total=outdegree(graph,v,adja); // get adjacent vertices
      for (k=0;k<total;k++) {
	for (j=0;j<n;j++) {
	  if (key[j]==adja[k] && mark[j]==0) dll_append(stack,new_jval_i(adja[k])); //push
	  else if (key[j]==adja[k] && mark[j]==1) {free_dllist(stack);return 0;}  //visit again->have cycle
	}
      }
    } else {free_dllist(stack);return 0;} //visited
  }
  free_dllist(stack);
  return 1;
}

void dropGraph(Graph graph) {
  if (!jrb_empty(graph.edges)) { //not empty
    JRB node;
    jrb_traverse(node,graph.edges) 
      jrb_free_tree(jval_v(node->val));
  }
  jrb_free_tree(graph.edges);
  jrb_free_tree(graph.vertices);
}

void topologicalSort(Graph g,int *output,int *n) {
  // Queue
  int tmp[100],temp[100],indegreeOfNode[100],keyOfNode[100];
  Dllist queue=new_dllist();
  
  //number of node in graph
  int i=0;
  if (!jrb_empty(g.vertices)) {
    JRB node;
    jrb_traverse(node,g.vertices) {
      indegreeOfNode[i]=indegree(g,jval_i(node->key),tmp); // list of number of nodes go into node number i-th
      keyOfNode[i]=jval_i(node->key); //key of node number i-th
      if (indegreeOfNode[i]==0) 
	dll_append(queue,node->key); //enqueue
      i++;
    }
  }
  *n=i;
  i=0;
  int l;
  while (dll_empty(queue)!=1) { //not empty
    Dllist node=dll_first(queue); 
    int v=jval_i(node->val);
    dll_delete_node(node);  //dequeue
    
    output[i]=v;
    for (l=0;l<*n;l++) 
      if (keyOfNode[l]==v) break;
    indegreeOfNode[l]--;
    
    int total,j,k;
    total=outdegree(g,v,temp);
    for (j=0;j<total;j++) {
      k=temp[j];
      for (l=0;l<*n;l++) 
	if (keyOfNode[l]==k) break;
      indegreeOfNode[l]--;
      if (indegreeOfNode[l]==0)
	dll_append(queue,new_jval_i(k)); 
    }
    i++;
  }
}

void BFS(Graph graph,int start,int stop,void (*func)(int)) {
  //check existing
  JRB node1=jrb_find_int(graph.vertices,start);
  JRB node2=jrb_find_int(graph.vertices,stop);
  if (!node1) {printf("Do not exist node %d\n",start);return;}
  if (!node2 && stop!=-1) {printf("Do not exist node %d\n",stop);return;}
  //check outdegree start and indegree stop
  int temp[100];
  if (outdegree(graph,start,temp)==0) printf("Cannot go out node %d\n",start);
  if (indegree(graph,stop,temp)==0) printf("Cannot go in node %d\n",stop);
  //number of node in graph
  int n=0;
  if (!jrb_empty(graph.vertices)) {
    JRB node;
    jrb_traverse(node,graph.vertices)
      n++;
  }
  // initialize array key of node in graph corresponding with array mark unvisited(0) 
  int mark[n],key[n],i=0,j,k;
  if (!jrb_empty(graph.vertices)) {
    JRB node;
    jrb_traverse(node,graph.vertices) {
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
      int total=outdegree(graph,v,adja); // get adjacent vertices
      for (k=0;k<total;k++) 
	for (j=0;j<n;j++) 
	  if (key[j]==adja[k] && mark[j]==0) dll_append(queue,new_jval_i(adja[k]));
    }
  }
  free_dllist(queue);
}

void DFS(Graph graph,int start,int stop,void (*func)(int)) {
  //check existing
  JRB node1=jrb_find_int(graph.vertices,start);
  JRB node2=jrb_find_int(graph.vertices,stop);
  if (!node1) {printf("Do not exist node %d\n",start);return;}
  if (!node2 && stop!=-1) {printf("Do not exist node %d\n",stop);return;}
  //check outdegree start and indegree stop
  int temp[100];
  if (outdegree(graph,start,temp)==0) printf("Cannot go out node %d\n",start);
  if (indegree(graph,stop,temp)==0) printf("Cannot go in node %d\n",stop);
  //number of node in graph
  int n=0;
  if (!jrb_empty(graph.vertices)) {
    JRB node;
    jrb_traverse(node,graph.vertices)
      n++;
  }
  // initialize array key of node in graph corresponding with array mark unvisited(0) 
  int mark[n],key[n],i=0,j,k;
  if (!jrb_empty(graph.vertices)) {
    JRB node;
    jrb_traverse(node,graph.vertices) {
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
      int total=outdegree(graph,v,adja); // get adjacent vertices
      for (k=0;k<total;k++) 
	for (j=0;j<n;j++) 
	  if (key[j]==adja[k] && mark[j]==0) dll_append(stack,new_jval_i(adja[k])); //push
    }
  }
  free_dllist(stack);
}

void BFS2(Graph g,int start,int stop,void(*func)(int)) {
  JRB check1 = jrb_find_int(g.vertices,start);
  JRB check2 = jrb_find_int(g.vertices,stop);
  if(check1 == NULL ) {
    printf("Graph does not have vertex %d\n", start);
    return;
  }
  if(stop != -1 && check2 == NULL) {
    printf("Graph does not have vertex %d\n", stop);
    return;
  }
  //check outdegree start and indegree stop
  int temp[100];
  if (outdegree(g,start,temp)==0) printf("Cannot go out node %d\n",start);
  if (indegree(g,stop,temp)==0) printf("Cannot go in node %d\n",stop);
  // Create a graph name 'visited' in which each node's key is
  // a vertex, and it's key indicate whether the vertex has been
  // visited (1) or not (0)
  JRB visited = make_jrb();
  JRB tmp;
  int V = 0;
  jrb_traverse(tmp,g.vertices) {
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
    int count = outdegree(g, key, output);
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
  JRB check1 = jrb_find_int(g.vertices,start);
  JRB check2 = jrb_find_int(g.vertices,stop);
  if(check1 == NULL ) {
    printf("Graph does not have vertex %d\n", start);
    return;
  }
  if(stop != -1 && check2 == NULL) {
    printf("Graph does not have vertex %d\n", stop);
    return;
  }
  //check outdegree start and indegree stop
  int temp[100];
  if (outdegree(g,start,temp)==0) printf("Cannot go out node %d\n",start);
  if (indegree(g,stop,temp)==0) printf("Cannot go in node %d\n",stop);
  // Create a graph name 'visited' in which each node's key is
  // a vertex, and it's key indicate whether the vertex has been
  // visited (1) or not (0)
  JRB visited = make_jrb();
  JRB tmp;
  int V = 0;
  jrb_traverse(tmp, g.vertices) {
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
    int count = outdegree(g, key, output);
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

double getEdgeValue(Graph graph,int v1,int v2) { // return INFINITIVE_VALUE if no edge between v1 and v2
  if (getVertex(graph,v1)==NULL) {
    printf("Add Vertex %d first\n",v1);
    return INFINITIVE_VALUE;
  }
  if (getVertex(graph,v2)==NULL) {
    printf("Add Vertex %d first\n",v2);
    return INFINITIVE_VALUE;
  }
  if (hasEdge(graph,v1,v2)==0) {
    printf("No edges between %d and %d\n",v1,v2);
    return INFINITIVE_VALUE;
  } else {
    JRB tree;
    JRB node=jrb_find_int(graph.edges,v1);
    tree=(JRB)jval_v(node->val);
    JRB node_tree=jrb_find_int(tree,v2);
    return jval_d(node_tree->val);
  }
}

double shortestPath(Graph graph, int s, int t, int* path, int* length) { // return the total weight of the path and the path is given via path and its length. Return INFINITIVE_VALUE if no path is found 

  //check existing
  JRB node1=jrb_find_int(graph.vertices,s);
  JRB node2=jrb_find_int(graph.vertices,t);
  if (!node1) {printf("Do not exist node %d\n",s);return INFINITIVE_VALUE;}
  if (!node2) {printf("Do not exist node %d\n",t);return INFINITIVE_VALUE;}
  //check outdegree start and indegree stop
  int temp[100];
  if (outdegree(graph,s,temp)==0) {printf("Cannot go out node %d\n",s);return INFINITIVE_VALUE;}
  if (indegree(graph,t,temp)==0) {printf("Cannot go in node %d\n",t);return INFINITIVE_VALUE;}
  //number of node in graph
  int n=0;
  if (!jrb_empty(graph.vertices)) {
    JRB node;
    jrb_traverse(node,graph.vertices)
      n++;
  }

  // Queue
  Dllist queue=new_dllist();

  // set all node's weight (distace to node) is infinitive and ist parent is null(-1)  
  JRB setd=make_jrb();
  JRB setparent=make_jrb();
  JRB tmp;
  jrb_traverse(tmp,graph.vertices) {
    jrb_insert_int(setd,jval_i(tmp->key),new_jval_d(INFINITIVE_VALUE));
    jrb_insert_int(setparent,jval_i(tmp->key),new_jval_i(-1));
    dll_append(queue,tmp->key); //enqueue
  }
  
  // set d of s = 0
  tmp=jrb_find_int(setd,s);
  tmp->val=new_jval_d(0);
  
  while (dll_empty(queue)!=1) { //not empty queue
    
    /*-------------Extract Min In Queue--------------*/
    Dllist ptr;
    int id_min;
    double min=INFINITIVE_VALUE;
    JRB node;
    dll_traverse(ptr,queue) { //all elements in queue 
      node = jrb_find_int(setd,jval_i(ptr->val)); //find node in graph (id) in setd tree to take its distance
      if (jval_d(node->val)<min) {
	min=jval_d(node->val); //find the minimum distance of elements in queue 
	id_min=jval_i(ptr->val); //node (id) with min d
	//printf("%d %f\n",id_min,min);
      }
    }
    
    dll_traverse(ptr,queue) { //dequeue the node id_min
      if (id_min==jval_i(ptr->val)) {dll_delete_node(ptr);break;}
      //printf("%d %d\n",id_min,jval_i(ptr->val));
    }
    /*-----------------------------------------------*/
    

    /* stop if id_min is t (reached t with min d )
       or min value of all remain elements in queue is infinitive 
       (can not go in all remain elements, no path from s to t)  */
    if (id_min==t || min==INFINITIVE_VALUE) break;

    
    // Relaxing edges and Modify key
    int i,total,adja_out[n];
    total=outdegree(graph,id_min,adja_out); //all outdegree of node id_min
    for (i=0;i<total;i++) { //find outdegree of node id_min with min d
      node = jrb_find_int(setd,adja_out[i]); 
      double d=getEdgeValue(graph,id_min,adja_out[i]);
      //printf("%d %f %f %f\n",adja_out[i],jval_d(node->val),min,d);
      if (jval_d(node->val) > min + d) {
	node->val=new_jval_d(min + d);
	JRB node2 = jrb_find_int(setparent,adja_out[i]);
	node2->val=new_jval_i(id_min);
      }
    }
  }
  
  free_dllist(queue);
  
  //
  int x,i=0;
  tmp=jrb_find_int(setd,t);
  if (jval_d(tmp->val)==INFINITIVE_VALUE) {
    *path=0;*length=0;
    jrb_free_tree(setd);
    jrb_free_tree(setparent);
    return INFINITIVE_VALUE;
  } else {
    x=t;
    while (x!=-1) { //Null
      JRB temp=jrb_find_int(setparent,x);
      path[i++]=x;
      x=jval_i(temp->val);
    }
    *length=i;
    for (i=0;i<*length/2;i++) {
      x=path[i];path[i]=path[*length-i-1];path[*length-i-1]=x;
    }
    int d=jval_d(tmp->val);
    jrb_free_tree(setd);
    jrb_free_tree(setparent);
    return d;//jval_d(tmp->val);
  }
}

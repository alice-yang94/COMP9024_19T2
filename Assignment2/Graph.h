// Graph interface for undirected/unweighted graphs
// Provided by Prof. Albert Nymeyer

typedef int Vertex;     //define a vertex

typedef struct  {       //define an edge
    Vertex v;
    Vertex w;
} Edge;

typedef struct graphRep *Graph;     //define a graph

Graph newGraph(int);              //create a new graph
Graph freeGraph(Graph);           // free the graph mallocs
void showGraph(Graph);            // print the graph

Edge newEdge(Vertex, Vertex);     // create a new edge
void insertEdge(Edge, Graph);     // insert an edge
void removeEdge(Edge, Graph);     // remove an edge
void showEdge(Edge);              // print an edge
int isEdge(Edge, Graph);          // check edge exists

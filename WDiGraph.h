/** WDiGraph header
  * @author Zachariah Valenzuela
  * @file WDiGraph.h  */
#ifndef WDGRAPH_H
#define WDGRAPH_H
#include <vector>
#include <memory>
#include "WDiGraphInterface.h"
#include "WGraphNode.h"
using namespace std;

const int NoEdgeWeight = 0;

/** Weighted DiGraph - implementation using integer vertex labels(0 to n-1)*/
class WDiGraph : public WDiGraphInterface<int> 
{
friend  void displayGraph(const shared_ptr<WDiGraph> &graphPtr);
public:
  /** Default Constructor (default size is 10 vertices) 
    * @pre The graph is empty.
    * @post The graph is initialized to hold n vertices. */
  WDiGraph(int n=10);              

  /** Copy Constructor
    * @param graph - the graph to copy. */
  WDiGraph(const WDiGraph& graph); 

  /* Following are declared and commented in interface header*/
  int getNumVertices() const;
  int getNumEdges() const;
  bool add(int start, int end, int edgeweight);
  bool remove(int start, int end);
  bool edgeExists(int start, int end) const;
  int getEdgeWeight(int start, int end) const;

  /** Assignment operator overload for deep copy of rhs graph 
   * @pre The lhs and rhs graphs exist
   * @post The lhs graph is deallocated and now contains the rhs graph*/
  WDiGraph& operator=(const WDiGraph& rhs);

private:
  int numOfVertices;  /** Number of vertices in the graph. */
  int numOfEdges;     /** Number of edges in the graph. */
  std::vector<std::shared_ptr<WGraphNode<int, int>>> adjList;
}; //end WDiGraph

#endif


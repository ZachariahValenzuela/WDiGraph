/** WDiGraph implementation - creates a weighted directed graph
  * @author Zachariah Valenzuela
  * @file WDiGraph.cpp  */
#include "WDiGraph.h"
#include "WGraphNode.h"
#include <vector>
#include <memory>
#include <iostream>

using namespace std;
WDiGraph::WDiGraph(int n) : numOfVertices(n), numOfEdges(0)
{
	adjList.resize(n, nullptr);
  visited.resize(n, false);

} //end constuctor     

WDiGraph::WDiGraph(const WDiGraph& graph) 
{
   *this = graph;
}//end copy constructor

bool WDiGraph::edgeExists(int start, int end) const
{
	//create a new shared pointer and set it = head pointer
  shared_ptr<WGraphNode<int, int>> curPtr = adjList[start];
  bool found = false;

	//validation
  if(start >= 0 && start <= getNumVertices() - 1 && end >= 0 && end <= getNumVertices() - 1)
  {
    //begin traversal from start vertex 
    for(curPtr = adjList[start] ; curPtr != nullptr ; curPtr = curPtr->getNext())
    {
      //if the node is found return true, else return false
      if(curPtr->getVertex() == end)
      {
        found = true;
        break;
      }
    }
  }
  else
    cout << "Error! Invalid verticies." << endl;
  return found;
}//end edgeExists

int WDiGraph::getNumVertices() const
{
   return numOfVertices;
}  // end getNumVertices

int WDiGraph::getNumEdges() const
{
   return numOfEdges;
}  // end getNumEdges

int WDiGraph::getEdgeWeight(int start, int end) const
{
  //validation
	if(start >= 0 && start <= getNumVertices() - 1 && end >= 0 && end <= getNumVertices() - 1)
  {
    //create a new shared pointer and set it = head pointer
    shared_ptr<WGraphNode<int, int>> curPtr = adjList[start];
  
    //begin traversal from start vertex 
    for(curPtr = adjList[start] ; curPtr != nullptr ; curPtr = curPtr->getNext())
    {
      //if the node is found return weight, else return 0
      if(curPtr->getVertex() == end)
        return curPtr->getWeight();
    } 
  }
  else
    cout << "Error! Invalid verticies." << endl;
  return 0;//if verticies were invalid
} // end getWeight

bool WDiGraph::add(int start, int end, int w)
{
  if(edgeExists(start, end))
    return false;
  if(start == end)
    return false;
  if(start < 0 || start > getNumVertices() - 1)
    return false;
  if(end < 0 || end > getNumVertices() - 1)
    return false;
  //make a node and insert into front of chain
  shared_ptr<WGraphNode<int,int>> edge = make_shared<WGraphNode<int, int>>(end, w, adjList[start]);
  adjList[start] = edge;
  //increment numOfEdges
  numOfEdges++;
	return true;
}//end add

bool WDiGraph::remove(int start, int end)
{
	//validation
  bool ableToRemove = edgeExists(start, end);
	if(ableToRemove)
	{
		
    //create shared curPtr
    shared_ptr<WGraphNode<int, int>> curPtr = adjList[start];
		
    //if the node to be deleted is the first node
    if(curPtr != nullptr && adjList[start]->getVertex() == end)
		{
			adjList[start] = adjList[start]->getNext();
			numOfEdges--;
		}
		else
		{
			// find node that is before the one to delete
			for(curPtr = adjList[start] ; curPtr != nullptr; curPtr = curPtr->getNext())
			{
				if(curPtr->getNext() != nullptr && curPtr->getNext()->getVertex() == end)
				{
					// point to node to delete
					// disconnnect indicated node from chain by connecting the
					// prior node with the one after
					curPtr->setNext(curPtr->getNext()->getNext());
					numOfEdges--;
					break;
				}
			}	
		} 
	}
	return ableToRemove;
}  // end remove

bool WDiGraph::topoSortDFSRecurse(int vertex)
{
  cout << "in DFS recurse: " << vertex << endl;
  if(visited[vertex] == true)
    return false;
  visited[vertex] = true;
  vector<int> nextVertices = getNextVertex(vertex);
  if(nextVertices.size() == 0)
  { 
    cout << "in the if" << endl;
    int nextVertex = getFirstVertex();
    if(nextVertex < 0)
      return true;
    else 
    {
      nextVertices.resize(1, nextVertex);
    }
  }
  
   cout << endl;
  for(auto &nextVertex: nextVertices)  
    if(!topoSortDFSRecurse(nextVertex))
      for(int i = 0; i < numOfVertices; i++)
        if(!visited[i])
          return topoSortDFSRecurse(i);
    return false;
  
  return true;
}

bool WDiGraph::topoSortDFS()
{
	return topoSortDFSRecurse(getFirstVertex());
}

bool WDiGraph::topoSortSR(WDiGraph& graph)
{
  curListPosition.clear();
	curListPosition = adjList;
	return false;
}

int WDiGraph::getFirstVertex()
{
  for(int i = 0; i < numOfVertices; i++)
  {
    if(!visited[i] && adjList[i] != nullptr)
      return i;
	}
  return -1;
}

vector<int> WDiGraph::getNextVertex(int vertex)
{
  vector<int> nextVertices = vector<int>();
  
	for(shared_ptr<WGraphNode<int, int>> curPtr = adjList[vertex]; curPtr != nullptr; curPtr = curPtr->getNext())
  {
    nextVertices.push_back(curPtr->getVertex());
  }

  return nextVertices;
}

WDiGraph& WDiGraph::operator=(const WDiGraph& rhs)
{
  numOfVertices = rhs.getNumVertices();
  numOfEdges = rhs.getNumEdges();
  adjList.clear(); //remove all data in adjList
	adjList.resize(numOfVertices, nullptr);
  visited.resize(numOfVertices, false);
  for(int v = 0; v < numOfVertices; v++)
  {
    shared_ptr<WGraphNode<int, int>> origChainPtr = rhs.adjList[v];  // Points to original chain
  
    //if list is empty
    if (origChainPtr == nullptr)
      adjList[v] = nullptr;  // Original WGraphNode is empty
    else
    {
      // Copy first WGraphNode
      adjList[v] = make_shared<WGraphNode<int, int>>(origChainPtr->getVertex(), origChainPtr->getWeight(), origChainPtr->getNext()); 
	    
      // Copy remaining WGraphNodes
      shared_ptr<WGraphNode<int, int>> newChainPtr = adjList[v];
      origChainPtr = origChainPtr->getNext();  // Advance original-chain pointer
      while (origChainPtr != nullptr)
      {
        // Get next vertex and weight from original chain
        int vertex = origChainPtr->getVertex();
        int weight = origChainPtr->getWeight();
        shared_ptr<WGraphNode<int, int>> nextPtr = origChainPtr->getNext();
           
        // Create a new WGraphNode containing the next item
        shared_ptr<WGraphNode<int, int>> newWGraphNodePtr = make_shared<WGraphNode<int, int>>(vertex, weight, nextPtr);
      
        // Link new WGraphNode to end of new chain
        newChainPtr->setNext(newWGraphNodePtr);
      
        // Advance pointer to new last WGraphNode
        newChainPtr = newChainPtr->getNext();

        // Advance original-chain pointer
        origChainPtr = origChainPtr->getNext();
      }// end while
      newChainPtr->setNext(nullptr); // Flag end of chain
    }
  }
  return *this;
}
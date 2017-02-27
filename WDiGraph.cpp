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
} //end constuctor     

WDiGraph::WDiGraph(const WDiGraph& graph) 
{
  adjList.resize(graph.getNumVertices());
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
 cout << "in" << endl;
 //validation
  if(!edgeExists(start, end) && start != end && w > 0 && start >= 0 && 
     start - 1 < getNumVertices() && end >= 0 && end - 1 < getNumVertices()) 
    return false;
  cout << "past if" << endl;
  //make a node and insert into front of chain
  shared_ptr<WGraphNode<int,int>> edge = make_shared<WGraphNode<int, int>>(end, w, adjList[start]);
	
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

WDiGraph& WDiGraph::operator=(const WDiGraph& rhs)
{
	adjList.resize(rhs.getNumVertices());
	shared_ptr<WGraphNode<int, int>> origChainPtr = rhs.adjList[0];  // Points to original chain
  
  //if list is empty
  if (origChainPtr == nullptr)
    adjList[0] = nullptr;  // Original WGraphNode is empty
  else
  {
		// Copy first WGraphNode
		shared_ptr<WGraphNode<int, int>> headPtr = adjList[0];
    
    // Copy remaining WGraphNodes
    shared_ptr<WGraphNode<int, int>> newChainPtr = headPtr;
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
  return *this;//Overload operator =
}
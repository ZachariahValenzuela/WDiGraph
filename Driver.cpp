/** WDiGraph driver - creates and tests weighted directional graphs
  * @author Zachariah Valenzuela
  * @file Driver.cpp  */ 
#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include "WDiGraph.h"

using namespace std;

void testGraph(shared_ptr<WDiGraph> &graphPtr);
void readGraph(shared_ptr<WDiGraph> &graphPtr);
void displayGraph(const shared_ptr<WDiGraph> &graphPtr);

int main()
{
  shared_ptr<WDiGraph> myGraph = make_shared<WDiGraph>();
  cout << "Testing Graph . . . ." << endl << endl ;
	testGraph(myGraph);
	
  /*read graph from file and display it
	*/
  readGraph(myGraph);
  cout << "Number of Vertices in graph: " << myGraph->getNumVertices() << endl;
  shared_ptr<WDiGraph> graph2 = myGraph;
	displayGraph(myGraph);
	
	
	//displayGraph(graph2);
	return 0;
}  // end main


/**Remember to comment all functions below 
*/
void testGraph(shared_ptr<WDiGraph> &graphPtr)
{
	cout << "in test" << endl;	
	//test add function
  graphPtr->add(3,2,1);
  cout << "Number of edges in graph:" << graphPtr->getNumEdges() << endl;
  
  //test edgeExists function
  if(graphPtr->edgeExists(3,2))
    cout << "edge exists with weight: " << graphPtr->getEdgeWeight(3,2) << endl;
    
  //test remove function
  graphPtr->remove(3,2);
  cout << "Number of edges in graph:" << graphPtr->getNumEdges() << endl;
  cout << "Number of vertices in graph:" << graphPtr->getNumVertices() << endl;
}

void readGraph(shared_ptr<WDiGraph> &graphPtr)
{
  //fstream setup
  string filename;
	string line;
	string numOfVertices, start, end, weight;
	bool valid = false;

  do
  {
    cout << "Please type the filename of the graph: ";
    cin >> filename;
    fstream fin;
    fin.open(filename);
    if(!fin)
		cout << "File did not open!" << endl;
    else
    {
      getline(fin, numOfVertices);
      int vertexNum = stoi(numOfVertices);//convert string to int
      shared_ptr<WDiGraph> graph = make_shared<WDiGraph>(vertexNum);
      bool done = false;
			while(!done)
      {	
        fin >> start >> end >> weight;
        
				//convert string to int
				int begin = stoi(start);
				int finish = stoi(end);
				int mass = stoi(weight);
				
				//add the node to the graph using converted parameters 
				graphPtr->add(begin, finish, mass);
				if(fin.eof())
					done = true;
      }
    graph = graphPtr;
    fin.close();
    valid = true;
    }
  }
  while(!valid);
}//end readGraph

void displayGraph(const shared_ptr<WDiGraph> &graphPtr)
{
  //loop over the graph based on number of vertices
  for( int i = 0; i < graphPtr->getNumVertices(); i++)
  {
    //format output
    cout << i << ": ";
    for(shared_ptr<WGraphNode<int,int>> curPtr = graphPtr->adjList[i];
      curPtr != nullptr; curPtr = curPtr->getNext())
      cout << "-> [" << curPtr->getVertex() << "|" << curPtr->getWeight()<< "]";
    cout << endl;
  }//end for
}//end displayGraph

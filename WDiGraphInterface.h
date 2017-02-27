// Based on code from  Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
// Modified by J. Braun 

/** An interface for the ADT directed weighted graph.
 @file WDiGraphInterface.h */

#ifndef _WDIGRAPH_INTERFACE
#define _WDIGRAPH_INTERFACE

template<class LabelType>
class WDiGraphInterface
{
public:
   /** Gets the number of vertices in this graph.
    @pre   None.
    @return  The number of vertices in the graph. */
   virtual int getNumVertices() const = 0;
   
   /** Gets the number of edges in this graph.
    @pre   None.
    @return  The number of edges in the graph. */
   virtual int getNumEdges() const = 0;
   
   /** Creates an directed edge between two vertices that have the given labels.
    Loops and multiedges are not allowed.
    @param start  A label for the first vertex. 
    @param end  A label for the second vertex.
    @param edgeWeight  The integer weight of the edge.
    @return  True if the edge is created, or false otherwise. */
   virtual bool add(LabelType start, LabelType end, int edgeWeight) = 0;
   
   /** Removes an edge from this graph.  
    @pre  None.
    @param start  A label for the first vertex.
    @param end  A label for the second vertex.
    @return  True if the edge is removed, or false otherwise. */
   virtual bool remove(LabelType start, LabelType end) = 0;
   
   /** Gets the weight of an edge in this graph.
    @return  The weight of the specified edge. 
       If no such edge exists, returns a nonpositive integer. */
   virtual int getEdgeWeight(LabelType start, LabelType end) const = 0;
   
   /** Checks if an edge in this graph.
    @return  true if the specified edge is in the graph. 
       If no such edge exists, returns false. */
   virtual bool edgeExists(LabelType start, LabelType end) const = 0;
   
}; // end GraphInterface
#endif

/** WGraphNode implementation - creates a node for use in a weighted digraph
  * @author Zachariah Valenzuela
  * @file WGraphNode.cpp  */
#include "WGraphNode.h"
#include <cstddef> 
#include <vector>
#include <iostream>

template<class LabelType, class WtType>
WGraphNode<LabelType, WtType>::WGraphNode()
{
} // end default constructor  

template<class LabelType, class WtType>
WGraphNode<LabelType, WtType>::WGraphNode(LabelType vertex, WtType weight,
                                    shared_ptr<WGraphNode<LabelType, WtType>> nextPtr)
{
	this->vertex = vertex;
  this->weight = weight;
  this->nextPtr = nextPtr;
} // end constructor

template<class LabelType, class WtType>
shared_ptr<WGraphNode<LabelType, WtType>> WGraphNode<LabelType, WtType>::getNext()
{
  return nextPtr;
}

template<class LabelType, class WtType>
void WGraphNode<LabelType, WtType>::setNext(shared_ptr<WGraphNode<LabelType, WtType>> next)
{
   nextPtr = next;
} 

template<class LabelType, class WtType>
LabelType WGraphNode<LabelType, WtType>::getVertex() const
{
  return vertex;
}

template<class LabelType, class WtType>
WtType WGraphNode<LabelType, WtType>::getWeight() const
{
  return weight;
}
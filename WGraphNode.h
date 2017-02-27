/** WGraphNode header
  * @author Zachariah Valenzuela
  * @file WGraphWGraphNode.h  */
#ifndef WGraphNode_
#define WGraphNode_
#include <memory>

using namespace std; 

template<class LabelType, class WtType>
class WGraphNode 
{
private:
   LabelType vertex; /** start or end point */
   WtType weight; /** edge weight */
   shared_ptr<WGraphNode<LabelType, WtType>> nextPtr = NULL; /** Pointer to next WGraphNode */
   
public:
   /** default constructor
     * @pre none
     * @post node is initialized to null */
   WGraphNode();
   
   /** constructor used to initialize a graph node to hold a vertex, weight, and next pointer
     * @pre none
     * @post graph node constructed carrying vertex, weight, and nextPtr */
   WGraphNode(LabelType vertex, WtType weight, shared_ptr<WGraphNode<LabelType, WtType>> nextPtr);
   
   /** getNext() - returns next pointer
     * @pre next node can exist or be null
     * @post nextPtr remains unchanged */
   shared_ptr<WGraphNode<LabelType, WtType>> getNext();
   
   /** setNext() - set nextPtr to the next node in the chain
     * @pre next node can exist or be null
     * @post nextPtr points at next node in chain */
   void setNext(shared_ptr<WGraphNode<LabelType, WtType>> nextPtr);
   
   /** getVertex() - returns vertex of current nodePtr
     * @pre node must be instantiated
     * @post node remains unchanged */
   LabelType getVertex() const; 
   
   /** setVertex() - sets vertex of a node
     * @pre node must be initialized
     * @post vertex is stored withtin node */
   void setVertex(LabelType end);
   
   /** getWeight() - returns the weight of the edge
     * @pre node must be initialized
     * @post node remains unchanged */
   WtType getWeight() const ;
   
   /** setWeight() - sets the weight of the edge
     * @pre node must be initialized
     * @post weight is stored within node */
   void setWeight(WtType wt);
}; // end WGraphNode

#include "WGraphNode.cpp"
#endif

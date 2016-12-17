/* Abhinav Rana
  * U06971709
  * Anna Kaplan 
  * A99039352
  * HCTree.cpp
*/
#include "HCTree.h"

  /** Use the Huffman algorithm to build a Huffman coding trie.
     *  PRE-condition: freqs is a vector of ints, such that freqs[i] is 
     *  the frequency of occurrence of byte i in the message.
     *  POST-condition:  root points to the root of the trie,
     *  and leaves[i] points to the leaf node containing byte i.
  */
void HCTree::build(const vector<int>& freqs)
{
	//step 1 : Create the HC Nodes and add them to the Priority Queue and Leaves
	HCNode* newNode;
	for (int i = 0; i < freqs.size(); i++) 
	{
		if (freqs[i] > 0) //if the size of index is > 0
		{
			newNode = new HCNode(freqs.at(i), (byte) i, NULL, NULL, NULL);
			minHeap.push(newNode); 		//create new hc node and push to min-heap 
			leaves[i] = newNode;  		// stores the reference to the newly created node  
		}		
	}

	if (minHeap.size() == 0)
		return;

	//step 2 : Build the Huffman Tree
		
	HCNode* smaller; // first node that gets popped out 
	HCNode* larger;  // sey node that gets popped out 
	HCNode* combined;

	while (minHeap.size() > 1) // keep executing until 1 node remains in the minheap
	{
		smaller = minHeap.top(); //gets top element from minHeap
		minHeap.pop();
		larger = minHeap.top();  // gets next top element from minHeap
		minHeap.pop();

		// add the frequency of the two nodes
		// take the smaller symbol to be the new node's symbol
		// assign the 0 child to be smaller
		// assign the 1 child to be larger
		// parent will be null and will be updated next time
		combined = new HCNode(smaller->count + larger->count, smaller->symbol, 
							  smaller, larger, NULL);
		smaller->p = larger->p = combined; //assigns the parent node	

		minHeap.push(combined); // add the new node back to the minheap.

	}

	// assign the root of the tree to be the top and last element of minheap
	root = minHeap.top();
	minHeap.pop();

} // end of build function 

void HCTree::encode(byte symbol, BitOutputStream& out) const
{
  HCNode* curr = leaves[(int) symbol];
  if(!curr) // should not happen, to be honest
    return;
     
  std::vector<unsigned char> output; //chars
  while(curr->p) //while parent exists
  {
    if(curr->p->c0 == curr)
    {
      output.push_back((byte)'0');
      curr = curr->p; 
    }
    else if(curr->p->c1 == curr)
    {
      output.push_back((byte)'1');
      curr = curr->p;
    }
    else      
      return; // this should not happen     
  }
  
  int x = output.size() - 1;
  unsigned char charOutput;
  while(x >= 0)
  {
    charOutput = output[x];
    if(charOutput == '1')
        out.writeBit(1);  
    else if(charOutput == '0')
        out.writeBit(0);    
    else
    {
      // hopefully this never happens or else bad, bad, bad
    }
    x--;
  }
} // end of the encode function 

int HCTree::decode(BitInputStream& in) const
{
  HCNode* curr = root;
  int value;

  while(curr->c0 || curr->c1) // means its not a leaf node
  {
    value = in.readBit();

    if(value == 0)
        curr = curr->c0;  
    else 
        curr = curr->c1;
  }

  return curr->symbol; 
}



HCTree::~HCTree() //destructor for no memory leaks
{
    deleteAll(root);
}


void HCTree::deleteAll(HCNode* n)
{
   	if (n) // if exists
    	{
       	deleteAll(n->c0);
    		deleteAll(n->c1);
    		delete n;
    	}
}

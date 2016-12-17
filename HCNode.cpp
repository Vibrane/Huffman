/* Abhinav Rana
  * U06971709
  * Anna Kaplan 
  * A99039352
  * HCNode.cpp
*/
#include "HCNode.h"

bool HCNode::operator<(const HCNode& other) const
{
	if (count != other.count) 	//smaller count is higher priority 
		return count > other.count; 

	return symbol > other.symbol; //smaller symbol as higher priority 
}
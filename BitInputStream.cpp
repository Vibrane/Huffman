/* Abhinav Rana
  * U06971709
  * Anna Kaplan 
  * A99039352
  * BitInputStream.cpp
*/

#include "BitInputStream.h"

//Fill the buffer from the input
void BitInputStream::fill()
{
  buf = in.get();
  nbits = 8;
}


// Read the next bit from the bit buffer. Return 1 if it's 1 or else it's 
 
int BitInputStream::readBit() 
{

  if(nbits == 0)
    fill(); // call when all bits are read in buffer.

  int value = getBit(buf, nbits); //get bit at apppropriate location
  nbits--;  //decement counter
  return value; 
}

int BitInputStream::getBit(unsigned char c, int l)
{
  // this will return the bit at the specified location.

  int m = 8 - l; 
  c = c << m;
  c = c >> 7;
  return c; 
}

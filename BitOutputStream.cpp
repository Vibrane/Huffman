/* Abhinav Rana
  * U06971709
  * Anna Kaplan 
  * A99039352
  * BitOutputStream.cpp
*/
#include "BitOutputStream.h"  

 void BitOutputStream::flush()
 {
    out.put(buf);
    out.flush();
    buf = 0;
    nbits = 0;
 }

/** Write the least significant bit of the argument to
* the bit buffer, and increment the bit buffer index.
* But flush the buffer first, if it is full.
*/

void BitOutputStream::writeBit(int i) 
{
  if(nbits == 8)
    flush();

  buf = buf << 1;
  unsigned char t = i;
  buf = (buf | t);
  nbits++;
}

//call this at the end of the main
void BitOutputStream::anotherFlush()
{
  int m = 8 - nbits;
  buf = buf << m;
  flush();
}

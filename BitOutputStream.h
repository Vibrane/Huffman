/* Abhinav Rana
  * U06971709
  * Anna Kaplan 
  * A99039352
  * BitInputStream.h
*/

#include <iostream>
class BitOutputStream 
{

  private:
    unsigned char buf;  // one byte of buffer
    int nbits;          // how many bits have been written to the buf
    std::ostream & out; // reference to the output stream to use
  public:
    // Initialize a BitOutputStream that will use the given ostream for output.     
    explicit BitOutputStream(std::ostream & os) : out(os) 
    {
  		buf = 0;
  		nbits = 0;
    } 

 void flush(); 

/** Write the least significant bit of the argument to
* the bit buffer, and increment the bit buffer index.
* But flush the buffer first, if it is full.
*/

void writeBit(int);

// Flush when bit buffer is full. 
// Write the least significant bit of i into the buffer at the current index
// Increment the index

void anotherFlush();

};

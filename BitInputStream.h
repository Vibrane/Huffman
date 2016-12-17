/* Abhinav Rana
  * U06971709
  * Anna Kaplan 
  * A99039352
  * BitInputStream.h
*/
#include <iostream>
class BitInputStream{

private:

	unsigned char buf;   // one byte buffer of bits
	int nbits; // how many bits have been read from buf
	std::istream & in; // the input stream to use

public:

// constructor for the bitinputstream.
explicit BitInputStream(std::istream & i) : in(i)
{
 	buf = 0;
  	nbits = 0;  
}

//Fill the buffer from the input
void fill();

//reading 1 and 0 from the bit buffer
int readBit();

//this will get the bit at the specified location. 
int getBit(unsigned char, int);

};


/* Abhinav Rana
  * U06971709
  * Anna Kaplan 
  * A99039352
  * compress.cpp
*/
#include <iostream>
#include <fstream>
#include "HCTree.h"
#include "HCNode.h"

int main (int argc, char *argv[])
{
  if (argc != 3) 
  {
   	std::cout << "Invalid number of arguments." << std::endl;
    std::cout << "Usage: ./compress infile outfile" << std::endl;
   	return -1;
  }

  ifstream inFile (argv[1], ifstream::binary); //initializing the input file
  ofstream outFile (argv[2], ofstream::binary);//intiializing the output file

  if(inFile.peek() == std::ifstream::traits_type::eof()) 
  	return -1;  //stop if the input file is empty, no point in compressing.

  BitInputStream in (inFile); 	 // initializing of the BitInputFile
  BitOutputStream out (outFile); // initializing of the BitOutputFile.
  std::vector<int> freq(256,0);  // storing of the frequency of each byte

  unsigned char getByte; 
  while (1)
  {
    getByte = inFile.get();

    if(inFile.eof())
      break;

    freq.at(getByte)++; 
  } // reads every byte in the file and stores the frequency in vector 

  int count = 0;
  
  while(count < freq.size())
  {
    outFile.write((char*)&freq[count],(sizeof(char)*3)); 
    count++;
  }

  HCTree tree; //initialize and create tree
  tree.build(freq);

  inFile.clear();
  inFile.seekg(0, ios::beg);

  while (1)
  {
    getByte = inFile.get();

    if(inFile.eof())
    	break;
    
    tree.encode(getByte, out); //encoding here
  }

  out.anotherFlush(); //calling the flush at end of main

  outFile.close();
  inFile.close();
  
  return 0;

}

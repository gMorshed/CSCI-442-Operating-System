/**
 * This file contains implementations for methods in the PhysicalAddress class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "physical_address/physical_address.h"
#include <iostream> 
#include <bitset> 
#include<string>
using namespace std;


string PhysicalAddress::to_string() const {
  // TODO: implement me
  // string result = std::to_string(this->frame);
  // result = result + std::to_string(this->offset);
  //cout<<this->frame<<endl<<this->offset<<endl;
  bitset <this->FRAME_BITS> f (this->frame);
  bitset <this->OFFSET_BITS> off (this->offset);
  string result="";
  result = f.to_string();
  result += off.to_string();
  return result; 
}


ostream& operator <<(ostream& out, const PhysicalAddress& address) {
  out<<address.to_string()<<" [frame: "<<address.frame<<"; offset: "<<address.offset<<"]";
  return out;
}

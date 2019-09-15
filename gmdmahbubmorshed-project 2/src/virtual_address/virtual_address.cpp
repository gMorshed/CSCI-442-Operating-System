/**
 * This file contains implementations for methods in the VirtualAddress class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "virtual_address/virtual_address.h"
#include <string>
#include<iostream>
#include <bitset>
using namespace std;


VirtualAddress VirtualAddress::from_string(int process_id, string address) {
  string p="",off="";
  for(unsigned int i=0; i< PAGE_BITS;i++){
    p += address[i];
  }
  for(unsigned int i=PAGE_BITS; i<PAGE_BITS+OFFSET_BITS;i++){
    off += address[i];
  }
  int p_int =  bitset<PAGE_BITS>(p).to_ulong();
  int off_int =  bitset<OFFSET_BITS>(off).to_ulong();
  return VirtualAddress(process_id, p_int,off_int);
}


string VirtualAddress::to_string() const {
  bitset <this->PAGE_BITS> p (this->page);
  bitset <this->OFFSET_BITS> off (this->offset);
  string result="";
  result = p.to_string();
  result += off.to_string();
  return result;
}


ostream& operator <<(ostream& out, const VirtualAddress& address) {
  out<<"PID "<<address.process_id<<" @ " <<address.to_string()<<" [page: "<<address.page<<"; offset: "<<address.offset<<"]";
  return out;
}

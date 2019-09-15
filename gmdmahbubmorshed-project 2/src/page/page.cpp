/**
 * This file contains implementations for methods in the Page class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "page/page.h"
#include<iostream>
#include<vector>
using namespace std;


// Ensure PAGE_SIZE is initialized.
const size_t Page::PAGE_SIZE;


Page* Page::read_from_input(std::istream& in) {
  char flag;
  flag = in.peek();
  if(flag == EOF){
    return nullptr;
  }
  unsigned int i=0;
  char c;
  vector<char> vec;
  while(i<PAGE_SIZE){
    if(in.get(c)){
      vec.push_back(c);
      i++;
      continue;
    }
    break;
  }
  Page * page= new Page(vec);
  return page;
}


size_t Page::size() const {
  return this->bytes.size();
}


bool Page::is_valid_offset(size_t offset) const {
  if(this->size() !=0  && this->size() > offset){
    return true;
  }
  return false;
}


char Page::get_byte_at_offset(size_t offset) {
  if(is_valid_offset(offset)){
    return this->bytes[offset];
  }
  return false;
  
}

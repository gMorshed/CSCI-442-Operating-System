/**
 * This file contains implementations for methods in the Process class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "process/process.h"
#include <string>
#include<iostream>
using namespace std;


Process* Process::read_from_input(std::istream& in) {
  size_t b=0;
  vector<Page*> p;
  while(in){
    Page *page = Page::read_from_input(in);
    b += page->size();
    p.push_back(page);
  }
  if(p.size() > 0){
    Process * process = new Process(b,p);
    return process;
  }
  return nullptr;
}


size_t Process::size() const {
  return this->num_bytes;
}


bool Process::is_valid_page(size_t index) const {
  return index < this->pages.size();
}


size_t Process::get_rss() const {
  int count=0;
  for(unsigned int i=0;i<this->page_table.rows.size();i++){
    if(this->page_table.rows[i].present){
      count++;
    }
  }
  return count;
}


double Process::get_fault_percent() const {
  if(this->memory_accesses == 0){
    return 0.0;
  }
  return (double(this->page_faults) / double(this->memory_accesses))*100;
}

/**
 * This file contains implementations for methods in the PageTable class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "page_table/page_table.h"
#include<iostream>
using namespace std;


size_t PageTable::get_present_page_count() const {
  int count_present_page=0;
  for(unsigned int i=0;i<this->rows.size();i++){
    if(rows[i].present == true){
      count_present_page++;
    }
  }
  return count_present_page;
}


size_t PageTable::get_oldest_page() const {
  size_t num=-1;
  int index=-1;
    for(unsigned int i=0;i<this->rows.size();i++){
    if(rows[i].present == true){
      if(rows[i].loaded_at < num){
        num = rows[i].loaded_at;
        index=i;
      }
    }
  }
  return index;
}


size_t PageTable::get_least_recently_used_page() const {
  size_t num=-1;
  int index=-1;
    for(unsigned int i=0;i<this->rows.size();i++){
    if(rows[i].present == true){
      if(rows[i].last_accessed_at < num){
        num = rows[i].last_accessed_at;
        index=i;
      }
    }
  }
  return index;
}

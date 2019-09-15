/**
 *
 * author :Gazi Mahbub Morshed
 * Operating System's
 * Project 1: Scheduling. 
*/

#pragma once
#include "thread.h"
#include "newVariables.h"
#include <iostream>
using namespace std;
class Scheduler {
public:
  virtual Thread * next_thread(){
      cout<<"SHOULD GET FROM CHILD CLASSES"<<endl;
      return NULL;
  }
  
  virtual void add_thread(Thread *t, Event_type e_type){
      cout<<"SHOULD GET FROM CHILD CLASSES"<<endl;
  }
  virtual int get_size(){
        return -10000000;
    }
    virtual int get_time_slice(){
      return -1000000;
    }
    virtual bool status_of_new_thread(){
      return false;
    }
};
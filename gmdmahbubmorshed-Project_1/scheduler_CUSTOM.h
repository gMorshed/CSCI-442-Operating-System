/*
Process -Priority preemptive CUSTOM algorithm with multilevel queues. preemption is based on if there are new threads that just has arrived.

*/


#pragma once
#include<queue>
#include "thread.h"
#include "scheduler.h"
#include "newVariables.h"
#include <iostream>
using namespace std;
class scheduler_custom : public Scheduler {
    private:
    queue<Thread* >  system_ready_queue;
    queue<Thread* >  interactive_ready_queue;
    queue<Thread* >  normal_ready_queue;
    queue<Thread* >  batch_ready_queue;
    queue<Thread *>   thread_arrived_queue;
    int time_quantum = 1000000;
    
    public:
    Thread * next_thread(){
        if(!thread_arrived_queue.empty()){
            Thread * t= thread_arrived_queue.front();
            thread_arrived_queue.pop();
            return t;
        }
        
        else if(!system_ready_queue.empty()){
            Thread * t= system_ready_queue.front();
            system_ready_queue.pop();
            return t;
        }
        else if(!interactive_ready_queue.empty()){
            Thread * t= interactive_ready_queue.front();
            interactive_ready_queue.pop();
            return t;
        }
        else if(!normal_ready_queue.empty()){
            Thread * t= normal_ready_queue.front();
            normal_ready_queue.pop();
            return t;
        }
        else if(!batch_ready_queue.empty()){
            Thread * t= batch_ready_queue.front();
            batch_ready_queue.pop();
            return t;
        }
        return NULL;
  }
  
  void add_thread(Thread *t, Event_type e_type){
     if(e_type == Event_type::THREAD_ARRIVED){
        thread_arrived_queue.push(t);
     }
     else{
        if(t->p_prio == Process_priority::SYSTEM){
            system_ready_queue.push(t);
        }
        else if(t->p_prio == Process_priority::INTERACTIVE){
            interactive_ready_queue.push(t);
        }
        else if(t->p_prio == Process_priority::NORMAL){
            normal_ready_queue.push(t);
        }
        else if(t->p_prio == Process_priority::BATCH){
            batch_ready_queue.push(t);
        }
     }
  }
  int get_size(){
       return ( system_ready_queue.size()+interactive_ready_queue.size()+normal_ready_queue.size()+batch_ready_queue.size()+ thread_arrived_queue.size() );
    }
    int get_time_slice(){
      return time_quantum;
    }
    
    bool status_of_new_thread(){
    if(!thread_arrived_queue.empty()){
        return true;
    }
      return false;
    }
};
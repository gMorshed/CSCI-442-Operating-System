/*

Round Robin is basically a FCFS but preempted with a time slice

*/
#pragma once
#include<queue>
#include "thread.h"
#include "scheduler.h"
#include "newVariables.h"
#include <iostream>
using namespace std;
class scheduler_rr : public Scheduler {
    queue<Thread* >  ready_queue_rr;
    int time_quantum = 3;
    public:
    Thread * next_thread(){
        if(!ready_queue_rr.empty()){
            Thread * t= ready_queue_rr.front();
            ready_queue_rr.pop();
            return t;
        }
        return NULL;
    }
    
    void add_thread(Thread *t, Event_type e_type){
        ready_queue_rr.push(t);
    }
    
    int get_size(){
        return ready_queue_rr.size();
    }
    int get_time_slice(){
        return time_quantum;
    }
    
    bool status_of_new_thread(){
      return false;
    }
};
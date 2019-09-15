/**
 *
 * author :Gazi Mahbub Morshed
 * Operating System's
 * Project 1: Scheduling. 
*/

#pragma once
#include<queue>
#include "thread.h"
#include "scheduler.h"
#include "newVariables.h"
#include <iostream>
using namespace std;
class scheduler_fcfs : public Scheduler {
    queue<Thread* >  ready_queue_fcfs;
    int time_quantum = 1000000;
    public:
    Thread * next_thread(){
        if(!ready_queue_fcfs.empty()){
            Thread * t= ready_queue_fcfs.front();
            ready_queue_fcfs.pop();
            return t;
        }
        return NULL;
    }
    
    void add_thread(Thread *t, Event_type e_type){
        ready_queue_fcfs.push(t);
    }
    
    int get_size(){
        return ready_queue_fcfs.size();
    }
    int get_time_slice(){
        return time_quantum;
    }
    bool status_of_new_thread(){
      return false;
    }
    
};





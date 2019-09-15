/**
 *
 * author :Gazi Mahbub Morshed
 * Operating System's
 * Project 1: Scheduling. 
*/

#pragma once
#include "newVariables.h"
#include "burst.h"
#include "process.h"
#include<vector>
using namespace std;

struct Thread {
    int thread_id;
    int arrival_time;
    int p_id;
    Process_priority p_prio;;
    vector<Burst *> brusts;
    int end_time=0;
    State_type state;
    int start_time=0; //when it is first allocated in CPU 
    bool new_here=true;
    Thread(){};
    Thread (int p, Process_priority p_pri, int t_id, int arr_time, State_type s, vector <Burst *> b ){
        p_id = p;
        p_prio = p_pri;
        thread_id = t_id;
        arrival_time = arr_time;
        state = s;
        brusts = b;
    }
};

int priority_number_converter(Process_priority pp){
    int a;
    switch (pp){
        case(Process_priority::SYSTEM):
            a =0;
            break;
        case(Process_priority::INTERACTIVE):
            a=1;
            break;
        case(Process_priority::NORMAL):
            a=2;
            break;
        case(Process_priority::BATCH):
            a=3;
            break;
    }
    return a;
}


struct sort_Thread_main { //comparator for priority queue
	bool operator()( Thread* t1,  Thread* t2){
		return priority_number_converter(t1->p_prio) > priority_number_converter(t2->p_prio) ; 
	}
};

struct sort_Thread_per_thread { //comparator for priority queue
	bool operator()( Thread* t1,  Thread* t2){
		return t1->p_id > t2->p_id || (t1->p_id == t2->p_id && t1->thread_id > t2->thread_id)  ; 
	}
};






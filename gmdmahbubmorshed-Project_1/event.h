/**
 *
 * author :Gazi Mahbub Morshed
 * Operating System's
 * Project 1: Scheduling. 
*/

#pragma once
#include<iostream>
using namespace std;
#include "thread.h"
#include "process.h"
#include "newVariables.h"
class Event {
    public:
    int time_event_happened;
    Thread * what_thread;
    Event_type event_type;
    Event (int t, Thread *th, Event_type ev){
        time_event_happened = t;
        what_thread = th;
        event_type = ev;
    }
    
    
    int get_time(){
        return time_event_happened;
    }
    
    void thread_arrive_print(){
            cout<<"At time "<<this->time_event_happened<<":"<<endl;  
            cout<<"    "<<print_Event_type(this->event_type)<<endl;
            cout<<"    "<<"Thread "<<this->what_thread->thread_id<<" in process "<<this->what_thread->p_id<<" ["<<print_Process_priority(this->what_thread->p_prio)<<"]"<<endl;
            cout<<"    Transitioned from "<<print_State_type(this->what_thread->state)<<" to ";
            this->what_thread->state = State_type :: READY;
            cout<<print_State_type(this->what_thread->state)<<endl<<endl;
    }
    
    void dispatcher_invoke_print(int size, string name_of_algorithm,int t){
            cout<<"At time "<<this->time_event_happened<<":"<<endl;  
            cout<<"    "<<print_Event_type(this->event_type)<<endl;
            cout<<"    "<<"Thread "<<this->what_thread->thread_id<<" in process "<<this->what_thread->p_id<<" ["<<print_Process_priority(this->what_thread->p_prio)<<"]"<<endl;
            cout<<"    Selected from "<<size<<" threads; ";
            if(name_of_algorithm == "RR"){
                cout<<"allotted time slice of "<<t<<"."<<endl<<endl;
            }
            else if(name_of_algorithm == "CUSTOM"){
                cout<<"no specific time allocated, new arrived thread will preempted already dispatched thread before CPU allocation"<<endl;
            }
            else{
                cout<<"will run to completion of burst"<<endl<<endl;    
            }
                
        
    }
    
    void process_dispatch_completed_print(){
            cout<<"At time "<<this->time_event_happened<<":"<<endl;  
            cout<<"    "<<print_Event_type(this->event_type)<<endl;        
            cout<<"    "<<"Thread "<<this->what_thread->thread_id<<" in process "<<this->what_thread->p_id<<" ["<<print_Process_priority(this->what_thread->p_prio)<<"]"<<endl;
            cout<<"    Transitioned from "<<print_State_type(State_type::READY)<<" to "<<print_State_type(this->what_thread->state)<<endl<<endl;
    }
    
    void thread_dispatch_completed_print(){
            cout<<"At time "<<this->time_event_happened<<":"<<endl;  
            cout<<"    "<<print_Event_type(this->event_type)<<endl;        
            cout<<"    "<<"Thread "<<this->what_thread->thread_id<<" in process "<<this->what_thread->p_id<<" ["<<print_Process_priority(this->what_thread->p_prio)<<"]"<<endl;
            cout<<"    Transitioned from "<<print_State_type(State_type::READY)<<" to "<<print_State_type(this->what_thread->state)<<endl<<endl;
    }
    
    
    void cpu_burst_completed_print(){
        cout<<"At time "<<this->time_event_happened<<":"<<endl;  
        cout<<"    "<<print_Event_type(this->event_type)<<endl;        
        cout<<"    "<<"Thread "<<this->what_thread->thread_id<<" in process "<<this->what_thread->p_id<<" ["<<print_Process_priority(this->what_thread->p_prio)<<"]"<<endl;
        cout<<"    Transitioned from "<<print_State_type(this->what_thread->state)<<" to "<<print_State_type(State_type::BLOCKED)<<endl<<endl;
    }
    
    
    void io_burst_completed_print(){
        cout<<"At time "<<this->time_event_happened<<":"<<endl;  
        cout<<"    "<<print_Event_type(this->event_type)<<endl;        
        cout<<"    "<<"Thread "<<this->what_thread->thread_id<<" in process "<<this->what_thread->p_id<<" ["<<print_Process_priority(this->what_thread->p_prio)<<"]"<<endl;
        cout<<"    Transitioned from "<<print_State_type(State_type::BLOCKED)<<" to "<<print_State_type(this->what_thread->state)<<endl<<endl; 
    }
    
    void thread_completed_print(){
        cout<<"At time "<<this->time_event_happened<<":"<<endl;  
        cout<<"    "<<print_Event_type(this->event_type)<<endl;        
        cout<<"    "<<"Thread "<<this->what_thread->thread_id<<" in process "<<this->what_thread->p_id<<" ["<<print_Process_priority(this->what_thread->p_prio)<<"]"<<endl;
        cout<<"    Transitioned from "<<print_State_type(State_type::RUNNING)<<" to "<<print_State_type(this->what_thread->state)<<endl<<endl;
    }
    
    void thread_preempted_print(){
        cout<<"At time "<<this->time_event_happened<<":"<<endl;
        cout<<"    "<<print_Event_type(this->event_type)<<endl;
        cout<<"    "<<"Thread "<<this->what_thread->thread_id<<" in process "<<this->what_thread->p_id<<" ["<<print_Process_priority(this->what_thread->p_prio)<<"]"<<endl;
        cout<<"    Transitioned from "<<print_State_type(State_type::RUNNING)<<" to "<<print_State_type(this->what_thread->state)<<endl<<endl;
    }
    
};
    
struct EventComparator { //comparator for priority queue
	bool operator()( Event* e1,  Event* e2){	
		return e1->get_time() > e2->get_time(); 
	}
};




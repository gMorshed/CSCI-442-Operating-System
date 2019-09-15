/**
 *
 * author :Gazi Mahbub Morshed
 * Operating System's
 * Project 1: Scheduling. 
*/

#pragma once
using namespace std;
#include<string>
enum Process_priority {SYSTEM, INTERACTIVE, NORMAL, BATCH};
enum State_type {NEW, READY, RUNNING,BLOCKED, EXIT };
enum Event_type {THREAD_ARRIVED, THREAD_DISPATCH_COMPLETED, PROCESS_DISPATCH_COMPLETED, CPU_BURST_COMPLETED, IO_BURST_COMPLETED, THREAD_COMPLETED, THREAD_PREEMPTED, 
    DISPATCHER_INVOKED };
    
    string print_Event_type(Event_type e){
        switch(e){
        case THREAD_ARRIVED:
            return "THREAD_ARRIVED";
        case THREAD_DISPATCH_COMPLETED:
            return "THREAD_DISPATCH_COMPLETED";
        case PROCESS_DISPATCH_COMPLETED:
            return "PROCESS_DISPATCH_COMPLETED";
        case CPU_BURST_COMPLETED:
            return "CPU_BURST_COMPLETED";
        case IO_BURST_COMPLETED:
            return "IO_BURST_COMPLETED";
        case THREAD_COMPLETED:
            return "THREAD_COMPLETED";
        case THREAD_PREEMPTED:
            return "THREAD_PREEMPTED";
        case DISPATCHER_INVOKED:
            return "DISPATCHER_INVOKED";
        }
        return "THERE IS A PROBLEM IF U GOT HERE";
        
    }
    
    
     
    Process_priority convert_process_priority(int num){
        switch(num) {
            case 0:
                return Process_priority::SYSTEM;
            case 1:
                return Process_priority::INTERACTIVE;
            case 2:
                return Process_priority::NORMAL;               
            case 3:
                return Process_priority::BATCH;            
        }
        cout<<"THERE IS A PROBLEM IN converting"<<endl;
        return Process_priority::SYSTEM;
    }
    
    
      string print_Process_priority(Process_priority pp){
    switch(pp) {
    case SYSTEM:
        return "SYSTEM";
    case INTERACTIVE:
        return "INTERACTIVE";
    case NORMAL:
        return "NORMAL";
    case BATCH:
        return "BATCH";
    }
    return "THERE IS A PROBLEM IF U GOT HERE";
}



string print_State_type(State_type s){
    switch(s){
    case NEW:
        return "NEW";
    case READY:
        return "READY";
    case RUNNING:
        return "RUNNING";
    case BLOCKED:
        return "BLOCKED";
    case EXIT:
        return "EXIT";
    }
    return "THERE IS A PROBLEM IF U GOT HERE";
}
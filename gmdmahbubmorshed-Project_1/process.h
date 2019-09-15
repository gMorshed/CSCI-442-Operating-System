/**
 *
 * author :Gazi Mahbub Morshed
 * Operating System's
 * Project 1: Scheduling. 
*/

#pragma once
#include "newVariables.h"
#include<string> 
#include<map>
#include<vector>
#include<iostream>
#include "thread.h"
using namespace std;
  struct Process {
        int pID; //process id
        Process_priority Get_priority () { return p_priority; } 
        Process_priority p_priority; //system priority
        vector<Thread * > threads;
        Process (int p_ID, Process_priority p, vector< Thread *> threads_for_process) {
            pID = p_ID;
            p_priority = p;
            threads = threads_for_process;
        }
    /* I was priting out the process for bugging, you can ignore this function
    friend ostream& operator << (ostream & o, const Process *p) {
        for (Thread * item : p->threads){
            switch(p->p_priority) {
            case SYSTEM:
                  o << "(" << p->pID << ", ""SYSTEM"<<","<<item->print()<<")";
                  break;
            case INTERACTIVE:
                 o << "(" << p->pID << ", ""INTERACTIVE"<<","<<item->print()<<")";
                 break;
            case NORMAL:
                 o << "(" << p->pID << ", ""NORMAL"<<","<<item->print()<<")";     
                 break;
            case BATCH:
                 o << "(" << p->pID << ", ""BATCH"<<","<<item->print()<<")";
                 break;
          }
          o<<endl;
        }
        return o;
          
    }
    */
        
  };
  

  
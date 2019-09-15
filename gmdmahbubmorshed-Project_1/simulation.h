/**
 *
 * author :Gazi Mahbub Morshed
 * Operating System's
 * Project 1: Scheduling. 
*/

#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include "process.h"
#include "thread.h"
#include "event.h"
#include "burst.h"
#include "newVariables.h"
#include "scheduler.h"
#include "scheduler_FCFS.h"
#include "boost/format.hpp"
#include <math.h>
#include<iomanip>
#include<map>
#include <sstream>
using boost::format;
using boost::io::group;
#include <assert.h>
#include<vector>
#include <queue>  
using namespace std;
class Simulation {
    private:
    int current_time=0;
    vector <Process * > sim_vec;
    vector<Thread * > all_threads;
    vector<Burst *> all_bursts;
    bool processor_idle=true;
    string algo="FCFS";
    int NUM_OF_PROCESS, PROCESS_OVERHEAD, THREAD_OVERHEAD;
    Scheduler *schduler_to_run;
    priority_queue<Event*, vector<Event*>, EventComparator >  mypq;
    bool flag_verbose=false;
    Thread *last_thread=NULL;
    int time_slice = 1000000;
    Burst * burst_to_run=NULL;
    string algorithm_name;
    int simulator_start_time=0, simulator_end_time=0, service_time=0, i_o_time=0, total_dispatch_time=0;
    
    
    public:
    
    Simulation(Scheduler *s, bool f,string algo_name, int t=10000000){ //time slice is unless it's round robin
    	schduler_to_run = s;
    	time_slice =t;
    	flag_verbose = f;
    	algorithm_name =algo_name;
    }
        ~Simulation(){ //destructor to delete the pointers
    	for(Process *p: sim_vec){
    		for(Thread *t : p->threads){
    			for (Burst *b: t->brusts){
    				delete b;
    			}
    			delete t;
    		}
    		delete p;
    	}
    }
    
        void create_event(Thread * thread){ //creating event and putting them on queue
    	Event * event =new  Event(thread->arrival_time, thread, Event_type::THREAD_ARRIVED);
    	mypq.emplace(event);
    }
    
    void read_in(string filename){
        ifstream fin;
	    fin.open(filename);
	    
	    
	    fin>>NUM_OF_PROCESS>>THREAD_OVERHEAD>>PROCESS_OVERHEAD;
	    int process_ID;
	        int priority, num_of_thread;
	     do { //making process
	        fin>>process_ID>>priority>>num_of_thread;
	        int count_thread=0;
	        vector<Thread * > thread_vec;
	        while(count_thread < num_of_thread){ //making threads
	            int arr_time, num_of_brust;
	            fin>>arr_time>>num_of_brust;
	            int count_brust=0;
	            vector <Burst *> burst_vec;
	            while(count_brust<num_of_brust){  //scheduler making burst
	                int time_runing_CPU, time_runing_IO;
	                if(count_brust == num_of_brust-1){
	                    fin>>time_runing_CPU;
	                    Burst * burst = new Burst(time_runing_CPU, count_thread, true);
	                    burst_vec.push_back(burst);
	                }
	                else{
	                    fin>>time_runing_CPU>>time_runing_IO;
	                    Burst * burst1 = new Burst(time_runing_CPU, count_thread,false, time_runing_IO);
	                    burst_vec.push_back(burst1);
	                }
	                count_brust++;
	            }
	            Thread *thread = new Thread(process_ID,convert_process_priority(priority),count_thread, arr_time, State_type::NEW, burst_vec);
	            thread_vec.push_back(thread);
	            create_event(thread);
	            count_thread++;
	            
	        }
	        Process *process = new Process(process_ID, convert_process_priority(priority), thread_vec);
	        sim_vec.push_back(process);
	    } while(process_ID+1< NUM_OF_PROCESS); //because process starts from 0
	    fin.close();
    }
    
    
    
    
    void simulation_run(){
    	
    	while (!mypq.empty()) { //handle those event
    		Event * d_event = mypq.top();
    		mypq.pop();
    		
    		bool badCodeButWorks =true;
    		vector<Event *> events_to_add;
    		//handle all events that are not of type dispatcher_invoked first.
    		while(badCodeButWorks){//avoid error of multiple DISPATCHER_INVOKED
    			if( (d_event->event_type == Event_type::DISPATCHER_INVOKED)  && !mypq.empty()){
    				//have to check if its not empty to avoid possible errors on next line!
    				if(mypq.top()->time_event_happened == d_event->time_event_happened) {
    					events_to_add.push_back(d_event);
    					d_event = mypq.top();
    					mypq.pop();
    				}
    				else{ //event at front of queue occurs later, don't need to worry about it
    					badCodeButWorks = false;
    				}
    			}
    			else{
    				badCodeButWorks =false;
    			}
    		}
    		//replace the removed events in priority queue
	        for (auto& e: events_to_add){
	            mypq.push(e);
	        }
    		events_to_add.clear();
    		
    		switch(d_event->event_type){
    			
    			case(Event_type::THREAD_ARRIVED): 
    				schduler_to_run->add_thread(d_event->what_thread, d_event->event_type); //get the next thread based on the algorithm
    				current_time = d_event->time_event_happened; //update current time to thread arrive time, this switch statement is the only place current time gets updated
    				handle_thread_arrive(d_event); 
    				if(simulator_start_time > current_time){
    					simulator_start_time = current_time;
    				}
    				break;
    				
    			case(Event_type::DISPATCHER_INVOKED):
					current_time = d_event->time_event_happened;
    				handle_dispatcher_invoke(d_event);
    				break;
    				
    			case (Event_type::PROCESS_DISPATCH_COMPLETED):
    				current_time = d_event->time_event_happened;
    				handle_process_dispatch_completed(d_event);
    				break;
    			
    			case (Event_type::THREAD_DISPATCH_COMPLETED):
    				current_time = d_event->time_event_happened;
    				handle_thread_dispatch_completed(d_event);
    				break;
    			
    			case (Event_type::CPU_BURST_COMPLETED):
    				current_time = d_event->time_event_happened;
    				handle_cpu_burst_completed(d_event);
    				break;
    				
    			case (Event_type::IO_BURST_COMPLETED):
    				current_time = d_event->time_event_happened;
    				handle_io_burst_completed(d_event);
    				break;
    			case (Event_type::THREAD_COMPLETED):
    				current_time = d_event->time_event_happened;
    				handle_thread_completed(d_event);
    				if(simulator_end_time < current_time){
    					simulator_end_time =current_time;
    				}
    				break;
    			case(Event_type ::THREAD_PREEMPTED):
    				current_time =d_event->time_event_happened;
    				handle_thread_preempted(d_event);
    				break;
    		}
    		
    		
    		delete d_event;
		}
    }
    
    void handle_thread_arrive(Event * d_event){
    	assert(d_event->what_thread->state == State_type::NEW);
    	if(flag_verbose){
    		d_event->thread_arrive_print();
    		 
    	}
    	if(processor_idle){ //if the processor is idle, we invoke the dispatcher,,otherwise continue
	    	Event * e = new Event(current_time, d_event->what_thread, Event_type::DISPATCHER_INVOKED);
	    	mypq.push(e);
    	}
    }
    
    void handle_dispatcher_invoke(Event * d_event){
    	d_event->what_thread = schduler_to_run->next_thread(); //picking a new process
    	int size_selecting_from = schduler_to_run->get_size()+1; //I actually pick a thread and then get the size,, so have to add one.
    	//I have to see,,if I got a thread from ready queue, if not,,go to next event
    	if(d_event->what_thread == NULL){
    		return;
    	}
    	
    	if(flag_verbose){
    		d_event->dispatcher_invoke_print(size_selecting_from,algorithm_name,time_slice);
    		 
    	}
    	
    	processor_idle = false; //dispatcher has been invoked and processor is running
    	if(last_thread==NULL || last_thread->p_id != d_event->what_thread-> p_id){
    		Event *e  = new Event(current_time+PROCESS_OVERHEAD, d_event->what_thread, Event_type::PROCESS_DISPATCH_COMPLETED);
    		mypq.push(e);
    		total_dispatch_time += PROCESS_OVERHEAD;
    	}
    	else {
    		Event *e  = new Event(current_time+THREAD_OVERHEAD, d_event->what_thread, Event_type::THREAD_DISPATCH_COMPLETED);
    		mypq.push(e);
    		total_dispatch_time += THREAD_OVERHEAD;
    	}

    }
    
    void handle_process_dispatch_completed(Event * d_event){
    	d_event->what_thread->state = State_type::RUNNING;
    	if(d_event->what_thread->new_here){
    		d_event->what_thread->start_time = d_event->time_event_happened;
    		d_event->what_thread->new_here =false;
    	}
    	
    	last_thread=d_event->what_thread;
		if(flag_verbose){
			d_event->process_dispatch_completed_print();
			 
		}
		
		
		burst_to_run = d_event->what_thread->brusts.front(); //the burst to run, getting the front burst
		if(time_slice < burst_to_run->running_time_CPU){ //thread preempyted
		
			burst_to_run->time_slice_used++; //I need to know how many times a thread has used time slice
			
			burst_to_run->running_time_CPU = burst_to_run->running_time_CPU - time_slice; //only run for time slice amount
			Event *e = new Event (current_time+time_slice, d_event->what_thread, Event_type::THREAD_PREEMPTED);
			mypq.push(e);
		}
		
		else if(schduler_to_run->status_of_new_thread()){ //if there is new thread, I will run it after preempting the current thread after one time unit for the custom algorithm in order to optimize response time
			Event *e = new Event (current_time, d_event->what_thread, Event_type::THREAD_PREEMPTED);
			mypq.push(e);
		}		
		
		else{ 
			Event * e =new Event(current_time+burst_to_run->running_time_CPU, d_event->what_thread, Event_type::CPU_BURST_COMPLETED);
			mypq.push(e);
			
			d_event->what_thread->brusts.erase(d_event->what_thread->brusts.begin(), d_event->what_thread->brusts.begin()+1); //removing the front brust
			
			burst_to_run->running_time_CPU += burst_to_run->time_slice_used * time_slice; //as I decreased the burst time of the CPU to keep track of how time left to run, I need to add that back in.
			
			d_event->what_thread->brusts.push_back(burst_to_run);//adding is back to the vector becasue I'll need that bursts
		}
    }
    
    void handle_thread_dispatch_completed(Event * d_event){
    	d_event->what_thread->state = State_type::RUNNING;
    	if(d_event->what_thread->new_here){
    		d_event->what_thread->start_time = d_event->time_event_happened;
    		d_event->what_thread->new_here =false;
    	}
    	last_thread = d_event->what_thread;
    	
		if(flag_verbose){
			d_event->thread_dispatch_completed_print();	
			 
		}    	
    	
    	
    	burst_to_run = d_event->what_thread->brusts.front();
    	if(time_slice<burst_to_run->running_time_CPU){ //thread preempyted
    	
    		burst_to_run->time_slice_used++; //I need to know how many times a thread has used time slice
    		
			burst_to_run->running_time_CPU = burst_to_run->running_time_CPU - time_slice; //only run for time slice amount
			Event *e = new Event (current_time+time_slice, d_event->what_thread, Event_type::THREAD_PREEMPTED);
			mypq.push(e);
		}
		
		else if(schduler_to_run->status_of_new_thread()){ //if there is new thread, I will run it after preempting the current thread after one time unit for the custom algorithm in order to optimize response time
			Event *e = new Event (current_time, d_event->what_thread, Event_type::THREAD_PREEMPTED);
			mypq.push(e);
		}
		
		else{ 
			Event * e =new Event(current_time+burst_to_run->running_time_CPU, d_event->what_thread, Event_type::CPU_BURST_COMPLETED);
			mypq.push(e);
			
			d_event->what_thread->brusts.erase(d_event->what_thread->brusts.begin(), d_event->what_thread->brusts.begin()+1); //removing the front brust
			
			burst_to_run->running_time_CPU += burst_to_run->time_slice_used * time_slice; //as I decreased the burst time of the CPU to keep track of how time left to run, I need to add that back in.
	    	
	    	d_event->what_thread->brusts.push_back(burst_to_run); //adding is back to the vector becasue I'll need that bursts
		}
    	
    }
    
    void handle_cpu_burst_completed(Event *d_event){
    	
    	processor_idle = true;
    	Event *ee = new Event(current_time, d_event->what_thread, Event_type::DISPATCHER_INVOKED);
    	mypq.push(ee);

    	
    	if(burst_to_run->last_burst){ //if this is the last cpu burst,, prepare to exit
    		Event *e = new Event(current_time, d_event->what_thread, Event_type::THREAD_COMPLETED);
    		mypq.push(e);
    	}
    	else{
    		
			if(flag_verbose){
				d_event->cpu_burst_completed_print();	
				 
			}    		
    		
    		d_event->what_thread->state= State_type::BLOCKED;
    		Event *e =new Event(current_time+burst_to_run->running_time_IO, d_event->what_thread, Event_type::IO_BURST_COMPLETED);
    		mypq.push(e);
    	}

    }
    
    
    void handle_io_burst_completed(Event * d_event){
    	d_event->what_thread->state=State_type::READY;
    	schduler_to_run->add_thread(d_event->what_thread, d_event->event_type);
    	if(flag_verbose){
    		d_event->io_burst_completed_print();
    		 
    	}
    	
    	
    	if(processor_idle){
    		Event * e = new Event(current_time, d_event->what_thread, Event_type::DISPATCHER_INVOKED);
	    	mypq.push(e);
    	}
    }
    
    void handle_thread_completed(Event *d_event){
    	d_event->what_thread->state = State_type::EXIT;
    	if(flag_verbose){
    		d_event->thread_completed_print();	
    		 
    	}
    	d_event->what_thread->end_time = d_event->time_event_happened;
    	all_threads.push_back(d_event->what_thread);	
    }
    
    void handle_thread_preempted(Event * d_event){
    	d_event->what_thread->state = State_type::READY;
    	schduler_to_run->add_thread(d_event->what_thread, d_event->event_type);
    	if(flag_verbose){
    		d_event->thread_preempted_print();	
    	}
    	Event *ee = new Event(current_time, d_event->what_thread, Event_type::DISPATCHER_INVOKED);
    	mypq.push(ee);
    }
    
    
    
    void print_system_analysis(){
    	cout<<"SIMULATION COMPLETED!"<<endl<<endl;
    	//insert thread details by system priority
    	priority_queue<Thread*, vector<Thread*>, sort_Thread_main >  pq_tem;
    	for(Thread *t: all_threads){
    		pq_tem.push(t);
    	}
    	map<Process_priority, vector<Thread *> > myMap;
    	vector<Thread*> vec;
    	myMap[Process_priority::SYSTEM]=vec;
    	myMap[Process_priority::INTERACTIVE] =vec;
    	myMap[Process_priority::NORMAL] =vec;
    	myMap[Process_priority::BATCH] =vec;
    	for(Thread *t : all_threads){
    		myMap[t->p_prio].push_back(t);
    	}
    	
    	for(auto item: myMap){
    		int count_t=0, response_total=0, turn_around_total=0;
			if(item.second.size()!=0){
				for(Thread *t: item.second){
					response_total += (t->start_time - t->arrival_time);
					turn_around_total += (t->end_time -t->arrival_time );
					count_t++;
				}
			}
			cout<<print_Process_priority(item.first)<<" THREADS:"<<endl;\
			double avg_response=0.0,avg_turn_time=0.0;
			if(count_t != 0){
				avg_response=double(response_total)/double(count_t);
				avg_turn_time =double(turn_around_total)/double(count_t);
			}
			cout<<format("    Total count:%_17s\n") % (count_t);
			avg_response = avg_response + 0.005;
			avg_turn_time = avg_turn_time + 0.005;
			int e = (avg_response*100);
			avg_response = double(e)/100.0;
			string s =to_string(avg_response);
			if(count_t == 0){
				s= s.substr(0,4);
			}
			else{
				s= s.substr(0,5);
			}
			cout<<format("    Avg response time:%_11s\n") % (s);
			e = (avg_turn_time*100);
			avg_turn_time = double(e)/100.0;
			s =to_string(avg_turn_time);
			if(count_t == 0){
				s= s.substr(0,4);
			}
			else{
				s= s.substr(0,5);
			}
			
			cout<<format("    Avg turnaround time:%_9s\n") % (s);
			cout<<endl;
    	}
    	cout<<format("Total elapsed time:%_14s\n") % (simulator_end_time-simulator_start_time);
    	cout<<format("Total service time:%_14s\n") %service_time;
    	cout<<format("Total I/O time:%_18s\n") %i_o_time;
    	cout<<format("Total dispatch time:%_13s\n") %total_dispatch_time;
    	cout<<format("Total idle time:%_17s\n") %(simulator_end_time-simulator_start_time-service_time-total_dispatch_time);
    	cout<<endl;
    	double utilize = ( double(total_dispatch_time+service_time)/ double(simulator_end_time-simulator_start_time) ) *100;
    	utilize = utilize + 0.005;
		int e = (utilize*100);
		utilize = double(e)/100.0;
		string s =to_string(utilize);
		s= s.substr(0,5);
		s=s+"%";
    	cout<<format("CPU utilization:%_17s\n") %s;
    	double efficency = (double(service_time)/double(simulator_end_time-simulator_start_time) )*100;
    	efficency = efficency + 0.005;
		e = (efficency*100);
		efficency = double(e)/100;
		s =to_string(efficency);
		s= s.substr(0,5);
		s=s+"%";
    	cout<<format("CPU efficiency:%_18s\n") %s;
    	
    	
    }
    
    void print_per_thread_info(bool per__thread) { //if the user requested per thread, than I'll show the content,,otherwise just calculate it
    	for(Process *p : sim_vec){
    		if(per__thread){
    			cout<<"Process "<<p->pID<<" ["<<print_Process_priority(p->p_priority)<<"]:"<<endl;	
    		}
    		for(Thread *t: p->threads){
    			int total_cpu_time=0, total_io_time=0;
    			for(Burst * b: t->brusts){
    					total_cpu_time += b->running_time_CPU;
    					service_time += b->running_time_CPU;
    					total_io_time += b->running_time_IO;
    					i_o_time += b->running_time_IO;
    					
    			}
    	if(per__thread){
    			string s = to_string(t->thread_id)+":";
    			cout<<format("    Thread%=4s ARR: %-6s CPU: %-6s I/O: %-6s TRT: %-6s END: %-6s") %s % t->arrival_time % total_cpu_time %total_io_time %(t->end_time-t->arrival_time) %t->end_time;
    			cout<<endl;
    			}
    		}
    		if(per__thread){
    			cout<<endl;	
    		}
    	}
    }
};


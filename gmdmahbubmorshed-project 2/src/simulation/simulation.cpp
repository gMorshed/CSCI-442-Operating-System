/**
 * This file contains implementations for the methods defined in the Simulation
 * class.
 *
 * You'll probably spend a lot of your time here.
 */

#include "simulation/simulation.h"
#include "physical_address/physical_address.h"
#include<iostream>

using namespace std;


void Simulation::run() {
  for(VirtualAddress address: query_of_virtual_address){
    if(verbose) cout<<address<<endl;
    perform_memory_access(address);
    artificial_time_stamp++;
  }
  //now print the statistics of the simulation
  cout<<endl;
  cout<<"DONE!"<<endl<<endl;
  int total_memory_access=0;
  int total_page_faults=0;
  for(auto each_process: processes){
    //cout<<"Process  "<<each_process.first<<":  "<<"ACCESSES: "<<each_process.second->memory_accesses<<"     FAULTS: "<<each_process.second->page_faults<<"     FAULT RATE: "<<each_process.second->get_fault_percent()<<"    RSS: "<<each_process.second->get_rss()<<endl;
    
	  int e = (each_process.second->get_fault_percent() *100);
		double ee = double(e)/100.0;
		string s =to_string(ee);
		if(ee<10) s= s.substr(0,4);
		else if(ee<100) s= s.substr(0,5);
		else s= s.substr(0,6);
    
    cout<<format("Process%_4s:  ACCESSES: %-7sFAULTS: %-7sFAULT RATE: %-9sRSS: %-6s\n") %each_process.first %each_process.second->memory_accesses %each_process.second->page_faults %s %each_process.second->get_rss();
    total_memory_access += each_process.second->memory_accesses;
    total_page_faults += each_process.second->page_faults;
  }
  cout<<format("\nTotal memory accesses:%_16s\n") %total_memory_access;
  cout<<format("Total page faults:%_20s\n") %total_page_faults;
  cout<<format("Free frames remaining:%_16s\n")%(NUM_FRAMES-current_frame);
  
}


char Simulation::perform_memory_access(const VirtualAddress& address) {
  processes[address.process_id]->memory_accesses++;
  if(processes[address.process_id]->page_table.rows.at(address.page).present){
    if(verbose) cout<<"  -> IN MEMORY"<<endl;
    processes[address.process_id]->page_table.rows.at(address.page).last_accessed_at = artificial_time_stamp;
  }
  else{
    if(verbose) cout<<"  -> PAGE FAULT"<<endl;
    handle_page_fault(processes[address.process_id], address.page);
    processes[address.process_id]->page_faults++;
  }
  if(verbose) {
    cout<<"  -> physical address "<<PhysicalAddress(processes[address.process_id]->page_table.rows.at(address.page).frame, address.offset)<<endl;
    cout<<"  -> RSS: "<<processes[address.process_id]->get_rss()<<"     "<<endl<<endl;
  }
  return processes[address.process_id]->pages[address.page]->get_byte_at_offset(address.offset);
  //physical address is the frame number, doesn't matter if it got from page fault or not, and the offset
}


void Simulation::handle_page_fault(Process* process, size_t page) {
  if(current_frame < NUM_FRAMES && process->get_rss() < frames_per_process){
    process->page_table.rows.at(page).frame = current_frame;
    process->page_table.rows.at(page).present = true;
    process->page_table.rows.at(page).loaded_at = artificial_time_stamp;
    process->page_table.rows.at(page).last_accessed_at =artificial_time_stamp;
    current_frame++;
  }
  else{
    int page_index_to_replace=-1;
    if(algorithm == ReplacementStrategy::FIFO){
      page_index_to_replace =process->page_table.get_oldest_page();
    }
    else if(algorithm == ReplacementStrategy::LRU){
      page_index_to_replace = process->page_table.get_least_recently_used_page();
    }
    else{
      cout<<"PROBLEM WITH REPLACEMENT POLICY"<<endl;
    }
    //cout<<page_index_to_replace<<" "<<process->page_table.rows.at(page_index_to_replace).frame<< endl;
    process->page_table.rows.at(page_index_to_replace).present = false; //this one is going out of the memory
    process->page_table.rows.at(page).frame = process->page_table.rows.at(page_index_to_replace).frame; //new ones frame number is old one's frame number
    process->page_table.rows.at(page).present = true;
    process->page_table.rows.at(page).loaded_at = artificial_time_stamp;
    process->page_table.rows.at(page).last_accessed_at = artificial_time_stamp;
  }
}

void Simulation::set_verbose_max_frames(bool verbose, int frames_per_process){
  this->verbose = verbose;
  this->frames_per_process = frames_per_process;
}

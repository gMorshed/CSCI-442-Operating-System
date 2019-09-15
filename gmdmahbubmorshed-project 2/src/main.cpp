/**
 * This file contains the main() function that drives the simulation. You'll
 * need to add logic to this file to create a Simulation instance and invoke its
 * run() method.
* Author: Gazi Mahbub Morshed 
*/

#include <cstdlib>
#include "flag_parser/flag_parser.h"
#include "virtual_address/virtual_address.h"
#include "process/process.h"
#include "simulation/simulation.h"
#include<iostream>
#include<fstream>
using namespace std;


/**
 * The main entry point to the simulation.
 */
 
 void handle_process(int num_process, ifstream &sim_file, Simulation* simulation){
  for(int i=0;i<num_process;i++){
     int p_ID=0;
     string process_image_name="";
     sim_file>>p_ID>>process_image_name;
     ifstream process_image_file(process_image_name);
     Process * process = Process::read_from_input(process_image_file);
     simulation->processes.emplace(p_ID, process);
     //cout<<"Process "<<p_ID<<": "<<process->num_bytes<<" bytes"<<endl;
   }
 }
 
int main(int argc, char** argv) {
 FlagOptions flags;
 Simulation *simulation = new Simulation();
 if(!parse_flags(argc,argv,flags)){
    cout<<"Wrong command line input"<<endl;
    abort();
 }
 ifstream sim_file (flags.filename);
 int num_process=0;
  sim_file>>num_process;
  handle_process(num_process,sim_file,simulation);
  if(!sim_file){
   cerr<<"Error opening simulation file"<<endl;
   abort();
  }
  while(sim_file){
    int p_ID=-1;
    string address="";
    sim_file>>p_ID>>address;
    if(p_ID == -1){ //it's weird the say ifstram works,,so if the int didn't return anything, my initialize stays the same, so that's a problem and we I break out if that happens
      break;
    }
    VirtualAddress virtual_address = VirtualAddress::from_string(p_ID,address);
    simulation->query_of_virtual_address.push_back(virtual_address);
    //cout<<virtual_address<<endl;
  }
  simulation->verbose = flags.verbose;
  simulation->frames_per_process = flags.max_frames;
  simulation->algorithm = flags.strategy;
  simulation->run();
  return EXIT_SUCCESS;
}

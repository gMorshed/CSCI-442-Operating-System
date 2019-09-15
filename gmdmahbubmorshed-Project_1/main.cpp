/**
 *
 * author :Gazi Mahbub Morshed
 * Operating System's
 * Project 1: Scheduling. 
 * So far I only have FCFS algorithm working. So, algorithm flag won't work
*/
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "process.h"
#include "thread.h"
#include "simulation.h"
#include "scheduler.h"
#include "scheduler_FCFS.h"
#include "scheduler_RR.h"
#include "scheduler_PP.h"
#include "scheduler_CUSTOM.h"
#include<vector>
#include <typeinfo>
#include<string>
using namespace std;

void print_help(){
    cout<<"HELLO, Welcome to OS scheduling:"<<endl;
    cout<<"The accepted format for the command line is :"<<endl;
    cout<<"./simulator [flags] inputfile.txt(input file can be any name)"<<endl;
    cout<<"Here are the flags this program supports : "<<endl;
    cout<<"-t, --per-thread"<<endl<<"Output additional per-thread statistics for arrival time, service time, etc."<<endl;
    cout<<"-v, --verbose"<<endl<<"Output information about every state-changing event and scheduling decision."<<endl;
    cout<<"-a, --algorithm"<<endl<<"The scheduling algorithm that can be supported are: \"FCFS\",\"RR\",\"PRIORITY\",\"CUSTOM\" "<<endl;
    cout<<"The algorithm name has to be exactly the same as above"<<endl;
    abort();
}

void flag_handler(int argc, char **argv, bool &per__thread, bool &doing_verbos, bool & need_help, string &fileName, string & name_of_algorithm){
    while(1){
      static struct option long_options[] = {
      {"per_thread",     no_argument,       0, 't'},
      {"verbose",  no_argument,       0, 'v'},
      {"algorithm", required_argument, NULL, 'a'},
      {"help",  no_argument,       0, 'h'},
      {0, 0, 0, 0}
    };
        int option_index = 0;
        int c = getopt_long (argc, argv, "tvh", long_options, &option_index);
        if (c == -1)
        break;
            switch (c) {
        case 't':
            per__thread =true;
            break;
        case 'v':
            doing_verbos =true;
            break;
        case 'a':
            name_of_algorithm = string(optarg);
            break;
        case 'h':
            need_help =true;
            break;
        case '?':
          /* getopt_long already printed an error message. */
          break;

        default:
          abort ();
        }
    }
    if( (optind +1 < argc) || (optind >= argc) ){ //the flag that was able to be parsed are optind count,,,but if there are errors in command line,  abort()
        abort ();
    }
    
    fileName = string(argv[optind]);
}


int main(int argc, char* argv[]){ 
    string filename;
    bool per__thread=false, doing_verbos=false, need_help=false;
    string name_of_algorithm;
    flag_handler(argc,argv, per__thread,doing_verbos,need_help,filename, name_of_algorithm);
    if(need_help){
        print_help();
    }
    Scheduler *schl = new Scheduler();
    //select an algorithm
    if(name_of_algorithm == "FCFS"|| name_of_algorithm == ""){
        Scheduler *temp = new scheduler_fcfs();
        schl =temp;
    }
    else if(name_of_algorithm == "RR"){
       Scheduler *temp = new scheduler_rr();
        schl =temp;   
    }
    else if (name_of_algorithm =="PRIORITY"){
        Scheduler *temp = new scheduler_pp();
        schl =temp;
    }
    else if(name_of_algorithm =="CUSTOM"){
        Scheduler *temp = new scheduler_custom();
        schl =temp;
    }
    else    {//invalid algorithm name set
        cout<<"INVALID ALGORITHM NAME, for help use -h"<<endl;
        abort();
    }
    
    Simulation *sim= new Simulation(schl, doing_verbos, name_of_algorithm,schl->get_time_slice());
    sim->read_in(filename);
    sim->simulation_run();
    sim->print_per_thread_info(per__thread);
    sim->print_system_analysis();


    return 0;
    
}
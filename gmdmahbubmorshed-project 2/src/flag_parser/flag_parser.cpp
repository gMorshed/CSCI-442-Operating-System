/**
 * This file contains implementations for methods in the flag_parser.h file.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "flag_parser/flag_parser.h"
#include <iostream>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include<string>
using namespace std;


void print_usage() {
  cout <<
      "Usage: mem-sim [options] filename\n"
      "\n"
      "Options:\n"
      "  -v, --verbose\n"
      "      Output information about every memory access.\n"
      "\n"
      "  -s, --strategy (FIFO | LRU)\n"
      "      The replacement strategy to use. One of FIFO or LRU.\n"
      "\n"
      "  -f, --max-frames <positive integer>\n"
      "      The maximum number of frames a process may be allocated.\n"
      "\n"
      "  -h --help\n"
      "      Display a help message about these flags and exit\n"
      "\n";
}


bool parse_flags(int argc, char** argv, FlagOptions& flags) {
    
    const char* short_opts ="s:vf:h";
    const option long_opts[] = {
            {"strategy", required_argument, nullptr, 's'},
            {"verbose", no_argument, nullptr, 'v'},
            {"max-frames", required_argument, nullptr, 'f'},
            {"help", no_argument, nullptr, 'h'},
            {nullptr, no_argument, nullptr, 0}
    };
    
    
    
    
    
    
    while (true)
    {
        const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);

        if (opt == -1) break;
        switch (opt) {
        case 's':
        {
            string strategy_name=string(optarg);
            if(strategy_name == "FIFO")
                flags.strategy = ReplacementStrategy::FIFO;
            else if(strategy_name == "LRU")
                flags.strategy = ReplacementStrategy::LRU;
            else
                return false;
            break;
        }
        case 'v':
             flags.verbose =true;
            break;
        case 'f':{
             int num = atoi(optarg);
            if(num<=0){
                return false;
            }
            else{
                flags.max_frames = num;
            }
            break;
        }
        case 'h':
            print_usage();
            abort();
        default:
            return false;
            break;
        }
        
    }
     while(argv[optind] != nullptr){
         flags.filename = argv[optind];
         optind = optind +1;
     }
     
     if(flags.filename.empty()){
         return false;
     }
    
    return true;
}

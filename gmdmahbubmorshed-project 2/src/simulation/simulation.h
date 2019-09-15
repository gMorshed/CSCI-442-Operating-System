/**
 * This file contains the definition of the Simulation class.
 *
 * You're free to modify this class however you see fit. Add new methods to help
 * keep your code modular.
 */

#pragma once
#include "process/process.h"
#include "virtual_address/virtual_address.h"
#include "flag_parser/flag_parser.h"
#include <cstdlib>
#include "boost/format.hpp"
using boost::format;
using boost::io::group;
#include<map>
#include<vector>
using namespace std;

/**
 * Class responsible for running the memory simulation.
 */
class Simulation {
// PUBLIC CONSTANTS
public:

  /**
   * The maximum number of frames in the simulated system (512).
   */
  static const size_t NUM_FRAMES = 1 << 9;
  map<int, Process*> processes; //stores all the process and their ID;
  vector<VirtualAddress> query_of_virtual_address;
  bool verbose=false;
  unsigned int frames_per_process =-1;
  ReplacementStrategy algorithm;
// PUBLIC API METHODS
public:

  /**
   * Runs the simulation.
   */
  void run();
  void set_verbose_max_frames(bool verbose, int frames_per_process);

// PRIVATE METHODS
private:

  /**
   * Performs a memory access for the given virtual address, translating it to
   * a physical address and loading the page into memory if needed. Returns the
   * byte at the given address.
   */
  char perform_memory_access(const VirtualAddress& address);

  /**
   * Handles a page fault, attempting to load the given page for the given
   * process into memory.
   */
  void handle_page_fault(Process* process, size_t page);

// INSTANCE VARIABLES
private:
    unsigned int current_frame=0;
    unsigned int artificial_time_stamp=0;
};

/**
 *
 * author :Gazi Mahbub Morshed
 * Operating System's
 * Project 1: Scheduling. 
*/

#pragma once
#include "newVariables.h"
struct Burst {
  int running_time_CPU;
  int running_time_IO;
  int time_slice_used=0; //this will help me identify how many times a thread has been preempted so that I can add that back in when I calculate the service time.
  bool last_burst;
  int thread_id;
  int process_id;
  Burst (int C, int t_id,bool lb,int I=0){ //last burst doesn't have any I/O value, so by default it's zero
      running_time_CPU=C;
      running_time_IO = I;
      thread_id = t_id;
      last_burst = lb;
  }
};

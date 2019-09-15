 Author: Gazi Mahbub Morshed
 List of files: 
 Files in the src/ directory
 flag_parser : parses the command line flags appropiately.
 frame : takes in what a process, page number and it's content and make a frame for it. 
 page : Reads in process image and populate pages for a process.
 page_table: Makes a page table for each process and stored pages availibity and other information that is necessary for simulation.
 Physical_address: Represents a physical address in memory with the frame and offset number
 Process : Stores page, page table and all other process related information
 simulation: simulates memory accesses of process taking in a virtual address and print necesaary statistics for the simulation.
 Virutal address: address that does not live in the memory and is represented by page and offset.
 main : takes the command line arguments, reads in the neccessary files, populates data structure for the simulation and run the simulation.
 sim_4_belady_anom: the input simulation file that is used to show belady's anomoly.
 
 Any unusual feature in the program: No unusual behavior as I am aware of.
 Hours spent: 20 hours.
 
 Belady's anomaly: Usually when max-frame number for each process is increased, fault rate goes down as the memory can now store more pages 
 for a process which results in less page faults. But belady’s anomaly occurs when increasing the max-frame for a process results in more 
 page faults. Belady’s anomaly occurs for FIFO algorithm but not for LRU or Optimal. 

Command line to demonstrate the anomaly:
./mem-sim --strategy FIFO --max-frames 3 inputs/sim_4_belady_anom
./mem-sim --strategy FIFO --max-frames 4 inputs/sim_4_belady_anom 

We find 9 page faults with 3 max-frame and 10 page faults with 4 max-frame. Thus number of page faults go up as max-frame went up.

Why the anomaly occurs: So, in my input file that shows the belady’s anomoly (sim_4_belady_anom), I have 12 virtual address which are access in
the order of 1,2,3,4,1,2,5,1,2,3,4,5. When the max frame is 4, we see no page fault at access number 4,5. But with max-frame 3, no page fault at
access 4,5. Thus, the rest of the access with max-frame 4 results in page faults whereas, some of the access after 4 and 5 results in memory 
access rather than all page faults. The reason this occurs in FIFO replacement policy is because the priority to a page for 
replacement becomes dependent of the number of page frames. But for other replacement policy like LRU, least_used_page is independent 
of the number of frames. That’s why belady’s anomaly occurs in FIFO replacement policy.
